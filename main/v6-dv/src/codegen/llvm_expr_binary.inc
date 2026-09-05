// ==========================================
// Lors Compiler v6 - Binary Expression Codegen
// Layer: Code Generation
// ==========================================

algorithm cg_get_node_type_tag(node_id : whole) -> whole
begin
    verify (node_id < 0 or node_id >= ast_total_nodes) then result TYPE_UNKNOWN; conclude
    datum tag : whole = ast_get_type_tag(node_id);
    verify (tag == TYPE_PRECISE or tag == TYPE_SERIES or tag == TYPE_STATE) then
        result tag;
    conclude
    datum kind : whole = ast_get_kind(node_id);
    verify (kind == AST_FLOAT) then result TYPE_PRECISE; conclude
    verify (kind == AST_STRING) then result TYPE_SERIES; conclude
    verify (kind == AST_BOOL) then result TYPE_STATE; conclude
    verify (kind == AST_MEMBER) then
        datum base_node : whole = ast_get_child(node_id, 0);
        datum sname : series = cg_get_var_struct_name(ast_get_s_val(base_node));
        verify (length(sname) == 0) then sname = ast_get_type_name(base_node); conclude
        verify (length(sname) == 0) then sname = sym_get_var_type_name(ast_get_s_val(base_node)); conclude
        datum fname : series = ast_get_s_val(node_id);
        result struct_get_field_type(sname, fname);
    conclude
    verify (kind == AST_IDENT) then
        datum ltype : series = cg_get_var_type(ast_get_s_val(node_id));
        verify (ltype == "double") then result TYPE_PRECISE; conclude
        verify (ltype == "i64") then result TYPE_WHOLE; conclude
        verify (ltype == "ptr") then result TYPE_SERIES; conclude
        verify (ltype == "i1") then result TYPE_STATE; conclude
    conclude
    verify (kind == AST_INDEX) then
        datum arr_node : whole = ast_get_child(node_id, 0);
        datum arr_tname : series = cg_get_var_struct_name(ast_get_s_val(arr_node));
        verify (length(arr_tname) == 0) then arr_tname = ast_get_type_name(arr_node); conclude
        datum elem_tname : series = extract_sequence_elem_type(arr_tname);
        verify (elem_tname == "precise") then result TYPE_PRECISE; conclude
        verify (elem_tname == "series") then result TYPE_SERIES; conclude
        verify (elem_tname == "state") then result TYPE_STATE; conclude
        verify (struct_lookup(elem_tname) != -1) then result TYPE_STRUCT; conclude
        result TYPE_WHOLE;
    conclude
    verify (kind == AST_BINOP) then
        datum l_sub : whole = cg_get_node_type_tag(ast_get_child(node_id, 0));
        datum r_sub : whole = cg_get_node_type_tag(ast_get_child(node_id, 1));
        datum op : series = ast_get_s_val(node_id);
        verify (op == "==" or op == "!=" or op == "<" or op == "<=" or op == ">" or op == ">=" or op == "and" or op == "or") then
            result TYPE_STATE;
        conclude
        verify (op == "+" and (l_sub == TYPE_SERIES or r_sub == TYPE_SERIES)) then
            result TYPE_SERIES;
        conclude
        verify (l_sub == TYPE_PRECISE or r_sub == TYPE_PRECISE) then
            result TYPE_PRECISE;
        conclude
        result TYPE_WHOLE;
    conclude
    verify (kind == AST_CALL) then
        datum fn_name : series = ast_get_s_val(node_id);
        verify (ast_get_n_val(node_id) == 1 or struct_lookup(fn_name) != -1) then
            result TYPE_STRUCT;
        conclude
        datum u_tag : whole = fn_lookup_ret_tag(fn_name);
        verify (u_tag != TYPE_UNKNOWN) then
            result u_tag;
        conclude
        datum b_tag : whole = infer_builtin_call_type(fn_name, node_id);
        verify (b_tag != TYPE_UNKNOWN) then
            result b_tag;
        conclude
        result TYPE_UNKNOWN;
    conclude
    result tag;
end

algorithm cg_expr_binary(node_id : whole) -> series
begin
    datum op : series = ast_get_s_val(node_id);
    datum l_child : whole = ast_get_child(node_id, 0);
    datum r_child : whole = ast_get_child(node_id, 1);

    datum l_tag : whole = cg_get_node_type_tag(l_child);
    datum r_tag : whole = cg_get_node_type_tag(r_child);

    datum l_val : series = cg_generate_expression(l_child);
    datum r_val : series = cg_generate_expression(r_child);

    datum t : series = cg_new_temp();

    // 1. String Concatenation & Comparison
    verify (op == "+" and (l_tag == TYPE_SERIES or r_tag == TYPE_SERIES)) then
        cg_emit_indent_line(t + " = call ptr @__lors_str_concat(ptr " + l_val + ", ptr " + r_val + ")");
        result t;
    conclude
    verify ((op == "==" or op == "!=") and (l_tag == TYPE_SERIES or r_tag == TYPE_SERIES)) then
        datum t_cmp : series = cg_new_temp();
        cg_emit_indent_line(t_cmp + " = call i32 @strcmp(ptr " + l_val + ", ptr " + r_val + ")");
        verify (op == "==") then cg_emit_indent_line(t + " = icmp eq i32 " + t_cmp + ", 0"); otherwise cg_emit_indent_line(t + " = icmp ne i32 " + t_cmp + ", 0"); conclude
        result t;
    conclude

    // 2. Floating-Point Operations
    verify (l_tag == TYPE_PRECISE or r_tag == TYPE_PRECISE) then
        verify (l_tag != TYPE_PRECISE) then datum t_l : series = cg_new_temp(); cg_emit_indent_line(t_l + " = sitofp i64 " + l_val + " to double"); l_val = t_l; conclude
        verify (r_tag != TYPE_PRECISE) then datum t_r : series = cg_new_temp(); cg_emit_indent_line(t_r + " = sitofp i64 " + r_val + " to double"); r_val = t_r; conclude
        verify (op == "+") then cg_emit_indent_line(t + " = fadd double " + l_val + ", " + r_val); result t; conclude
        verify (op == "-") then cg_emit_indent_line(t + " = fsub double " + l_val + ", " + r_val); result t; conclude
        verify (op == "*") then cg_emit_indent_line(t + " = fmul double " + l_val + ", " + r_val); result t; conclude
        verify (op == "/") then cg_emit_indent_line(t + " = fdiv double " + l_val + ", " + r_val); result t; conclude
        verify (op == "==") then cg_emit_indent_line(t + " = fcmp oeq double " + l_val + ", " + r_val); result t; conclude
        verify (op == "!=") then cg_emit_indent_line(t + " = fcmp one double " + l_val + ", " + r_val); result t; conclude
        verify (op == "<") then cg_emit_indent_line(t + " = fcmp olt double " + l_val + ", " + r_val); result t; conclude
        verify (op == "<=") then cg_emit_indent_line(t + " = fcmp ole double " + l_val + ", " + r_val); result t; conclude
        verify (op == ">") then cg_emit_indent_line(t + " = fcmp ogt double " + l_val + ", " + r_val); result t; conclude
        verify (op == ">=") then cg_emit_indent_line(t + " = fcmp oge double " + l_val + ", " + r_val); result t; conclude
    conclude

    // 3. Boolean Operations
    verify (l_tag == TYPE_STATE or r_tag == TYPE_STATE) then
        verify (op == "and") then cg_emit_indent_line(t + " = and i1 " + l_val + ", " + r_val); result t; conclude
        verify (op == "or") then cg_emit_indent_line(t + " = or i1 " + l_val + ", " + r_val); result t; conclude
        verify (op == "==") then cg_emit_indent_line(t + " = icmp eq i1 " + l_val + ", " + r_val); result t; conclude
        verify (op == "!=") then cg_emit_indent_line(t + " = icmp ne i1 " + l_val + ", " + r_val); result t; conclude
    conclude

    // 4. Integer Operations
    verify (op == "+") then cg_emit_indent_line(t + " = add i64 " + l_val + ", " + r_val); result t; conclude
    verify (op == "-") then cg_emit_indent_line(t + " = sub i64 " + l_val + ", " + r_val); result t; conclude
    verify (op == "*") then cg_emit_indent_line(t + " = mul i64 " + l_val + ", " + r_val); result t; conclude
    verify (op == "/") then cg_emit_indent_line(t + " = sdiv i64 " + l_val + ", " + r_val); result t; conclude
    verify (op == "%") then cg_emit_indent_line(t + " = srem i64 " + l_val + ", " + r_val); result t; conclude
    verify (op == "==") then cg_emit_indent_line(t + " = icmp eq i64 " + l_val + ", " + r_val); result t; conclude
    verify (op == "!=") then cg_emit_indent_line(t + " = icmp ne i64 " + l_val + ", " + r_val); result t; conclude
    verify (op == "<") then cg_emit_indent_line(t + " = icmp slt i64 " + l_val + ", " + r_val); result t; conclude
    verify (op == "<=") then cg_emit_indent_line(t + " = icmp sle i64 " + l_val + ", " + r_val); result t; conclude
    verify (op == ">") then cg_emit_indent_line(t + " = icmp sgt i64 " + l_val + ", " + r_val); result t; conclude
    verify (op == ">=") then cg_emit_indent_line(t + " = icmp sge i64 " + l_val + ", " + r_val); result t; conclude

    result "0";
end
