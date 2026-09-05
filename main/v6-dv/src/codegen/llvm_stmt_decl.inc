// ==========================================
// Lors Compiler v6 - Datum Declaration Codegen
// ==========================================

algorithm cg_stmt_datum(node_id : whole) -> void
begin
    datum vname : series = ast_get_s_val(node_id);
    datum tag : whole = ast_get_type_tag(node_id);
    datum tname : series = ast_get_type_name(node_id);
    datum ltype : series = llvm_get_type(tag, tname);

    datum ptr_reg : series = "%var_" + vname;
    cg_emit_indent_line(ptr_reg + " = alloca " + ltype);
    cg_register_var(vname, ptr_reg, ltype, tname);

    datum has_init : state = false;
    verify (ast_get_child_count(node_id) > 0) then
        datum init_child : whole = ast_get_child(node_id, 0);
        datum init_val : series = cg_generate_expression(init_child);
        datum init_tag : whole = cg_get_node_type_tag(init_child);

        // String coercion for inquire() / series to numeric
        verify (tag == TYPE_WHOLE and init_tag == TYPE_SERIES) then
            datum t_int : series = cg_new_temp();
            cg_emit_indent_line(t_int + " = call i64 @atoll(ptr " + init_val + ")");
            init_val = t_int;
        conclude
        verify (tag == TYPE_PRECISE and init_tag == TYPE_SERIES) then
            datum t_fp_str : series = cg_new_temp();
            cg_emit_indent_line(t_fp_str + " = call double @atof(ptr " + init_val + ")");
            init_val = t_fp_str;
        conclude
        // Promote int literal/var to float if target is precise
        verify (tag == TYPE_PRECISE and init_tag == TYPE_WHOLE) then
            datum t_fp : series = cg_new_temp();
            cg_emit_indent_line(t_fp + " = sitofp i64 " + init_val + " to double");
            init_val = t_fp;
        conclude

        cg_emit_indent_line("store " + ltype + " " + init_val + ", ptr " + ptr_reg);
        has_init = true;
    conclude

    verify (has_init == false) then
        verify (tag == TYPE_PRECISE) then
            cg_emit_indent_line("store double 0.0, ptr " + ptr_reg);
        otherwise
            verify (tag == TYPE_SERIES or tag == TYPE_STRUCT or tag == TYPE_SEQUENCE) then
                cg_emit_indent_line("store ptr null, ptr " + ptr_reg);
            otherwise
                cg_emit_indent_line("store " + ltype + " 0, ptr " + ptr_reg);
            conclude
        conclude
    conclude
end
