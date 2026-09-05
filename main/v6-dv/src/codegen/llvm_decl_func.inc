// ==========================================
// Lors Compiler v6 - Algorithm & Global Codegen
// Layer: Code Generation
// ==========================================

algorithm cg_emit_global_datum(node_id : whole) -> void
begin
    datum vname : series = ast_get_s_val(node_id);
    datum tag : whole = ast_get_type_tag(node_id);
    datum tname : series = ast_get_type_name(node_id);
    datum ltype : series = llvm_get_type(tag, tname);

    datum has_init : state = false;
    datum init_val_str : series = "0";
    verify (tag == TYPE_PRECISE) then init_val_str = "0.0"; conclude
    verify (tag == TYPE_SERIES or tag == TYPE_STRUCT or tag == TYPE_SEQUENCE) then init_val_str = "null"; conclude
    verify (tag == TYPE_STATE) then init_val_str = "false"; conclude

    verify (ast_get_child_count(node_id) > 0) then
        has_init = true;
        datum init_child : whole = ast_get_child(node_id, 0);
        datum ckind : whole = ast_get_kind(init_child);
        verify (ckind == AST_INT or ckind == AST_FLOAT) then
            init_val_str = ast_get_s_val(init_child);
        conclude
        verify (ckind == AST_BOOL) then
            verify (ast_get_s_val(init_child) == "true") then init_val_str = "true"; conclude
            verify (ast_get_s_val(init_child) == "false") then init_val_str = "false"; conclude
        conclude
    conclude

    datum linkage : series = "common global ";
    verify (str_starts_with(vname, "TOK_") or str_starts_with(vname, "AST_") or str_starts_with(vname, "TYPE_")) then
        linkage = "internal global ";
    otherwise
        verify (has_init) then
            linkage = "global ";
        conclude
    conclude

    cg_emit_line("@global_" + vname + " = " + linkage + ltype + " " + init_val_str + ", align 8");
end

algorithm cg_emit_external_globals() -> void
begin
    datum glen : whole = length(cg_external_globals);
    datum i : whole = 1;
    datum start : whole = 1;
    cycle (i < glen) do
        datum c : whole = char_at(cg_external_globals, i);
        verify (c == 59) then // ';'
            datum gname : series = substring(cg_external_globals, start, i - start);
            verify (length(gname) > 0 and str_contains(cg_defined_globals, ";" + gname + ";") == false) then
                datum gltype : series = cg_get_var_type(gname);
                cg_emit_line("@global_" + gname + " = external global " + gltype + ", align 8");
            conclude
            start = i + 1;
        conclude
        i = i + 1;
    conclude
end

algorithm cg_emit_algorithm(node_id : whole) -> void
begin
    datum fn_name : series = ast_get_s_val(node_id);
    datum ret_tag : whole = ast_get_type_tag(node_id);
    datum ret_tname : series = ast_get_type_name(node_id);
    datum ret_ltype : series = llvm_get_type(ret_tag, ret_tname);
    datum total_children : whole = ast_get_child_count(node_id);
    datum is_external : state = (ast_get_n_val(node_id) == 1);
    datum param_node : whole = 0;

    datum p_cnt : whole = total_children;
    verify (is_external == false and total_children > 0) then p_cnt = total_children - 1; conclude

    datum params_sig : series = "";
    datum p : whole = 0;
    cycle (p < p_cnt) do
        param_node = ast_get_child(node_id, p);
        datum pname : series = ast_get_s_val(param_node);
        datum ptag : whole = ast_get_type_tag(param_node);
        datum ptname : series = ast_get_type_name(param_node);
        datum pltype : series = llvm_get_type(ptag, ptname);
        verify (p > 0) then params_sig = params_sig + ", "; conclude
        verify (is_external) then
            params_sig = params_sig + pltype;
        otherwise
            params_sig = params_sig + pltype + " %param_" + pname;
        conclude
        p = p + 1;
    conclude

    verify (is_external) then
        verify (str_contains(cg_declared_functions, ";" + fn_name + ";") == false and str_contains(cg_defined_functions, ";" + fn_name + ";") == false) then
            cg_emit_line("declare " + ret_ltype + " @" + fn_name + "(" + params_sig + ")");
            cg_declared_functions = cg_declared_functions + fn_name + ";";
        conclude
        result;
    conclude

    cg_env_reset_function();
    cg_current_func_ret_ltype = ret_ltype;
    cg_emit_line("define " + ret_ltype + " @" + fn_name + "(" + params_sig + ") {");
    cg_emit_line("entry:");

    // Allocate stack slots for parameters
    p = 0;
    cycle (p < p_cnt) do
        param_node = ast_get_child(node_id, p);
        datum pname2 : series = ast_get_s_val(param_node);
        datum ptag2 : whole = ast_get_type_tag(param_node);
        datum ptname2 : series = ast_get_type_name(param_node);
        datum pltype2 : series = llvm_get_type(ptag2, ptname2);
        datum ptr_reg : series = "%var_" + pname2;
        cg_emit_indent_line(ptr_reg + " = alloca " + pltype2);
        cg_emit_indent_line("store " + pltype2 + " %param_" + pname2 + ", ptr " + ptr_reg);
        cg_register_var(pname2, ptr_reg, pltype2, ptname2);
        p = p + 1;
    conclude

    // Emit function body statements
    datum body_node : whole = ast_get_child(node_id, total_children - 1);
    datum stmt_cnt : whole = ast_get_child_count(body_node);
    datum s : whole = 0;
    cycle (s < stmt_cnt) do
        cg_generate_statement(ast_get_child(body_node, s));
        s = s + 1;
    conclude

    // Safe terminal return
    verify (ret_ltype == "void") then
        cg_emit_indent_line("ret void");
    otherwise
        verify (ret_ltype == "double") then
            cg_emit_indent_line("ret double 0.0");
        otherwise
            verify (ret_ltype == "ptr") then
                cg_emit_indent_line("ret ptr null");
            otherwise
                cg_emit_indent_line("ret " + ret_ltype + " 0");
            conclude
        conclude
    conclude

    cg_emit_line("}");
    cg_emit_line("");
end
