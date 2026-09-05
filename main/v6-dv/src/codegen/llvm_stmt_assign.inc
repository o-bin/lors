// ==========================================
// Lors Compiler v6 - Assignment Statements Codegen
// ==========================================

algorithm cg_stmt_assign_simple(node_id : whole) -> void
begin
    datum var_name : series = ast_get_s_val(node_id);
    datum ptr_reg : series = cg_get_var_ptr(var_name);
    datum ltype : series = cg_get_var_type(var_name);

    datum rhs_node : whole = ast_get_child(node_id, 1);
    datum rhs_val : series = cg_generate_expression(rhs_node);
    datum rhs_tag : whole = cg_get_node_type_tag(rhs_node);

    // String coercion for inquire() / series to numeric
    verify (ltype == "i64" and rhs_tag == TYPE_SERIES) then
        datum t_int : series = cg_new_temp();
        cg_emit_indent_line(t_int + " = call i64 @atoll(ptr " + rhs_val + ")");
        rhs_val = t_int;
    conclude
    verify (ltype == "double" and rhs_tag == TYPE_SERIES) then
        datum t_fp_str : series = cg_new_temp();
        cg_emit_indent_line(t_fp_str + " = call double @atof(ptr " + rhs_val + ")");
        rhs_val = t_fp_str;
    conclude
    verify (ltype == "double" and rhs_tag == TYPE_WHOLE) then
        datum t_fp : series = cg_new_temp();
        cg_emit_indent_line(t_fp + " = sitofp i64 " + rhs_val + " to double");
        rhs_val = t_fp;
    conclude

    cg_emit_indent_line("store " + ltype + " " + rhs_val + ", ptr " + ptr_reg);
end

algorithm cg_stmt_assign_member(node_id : whole) -> void
begin
    datum lhs_node : whole = ast_get_child(node_id, 0);
    datum rhs_node : whole = ast_get_child(node_id, 1);

    datum gep : series = cg_expr_member_gep(lhs_node);
    datum rhs_val : series = cg_generate_expression(rhs_node);

    datum base_node : whole = ast_get_child(lhs_node, 0);
    datum sname : series = ast_get_type_name(base_node);
    verify (length(sname) == 0) then
        sname = cg_get_var_struct_name(ast_get_s_val(base_node));
    conclude
    verify (length(sname) == 0) then
        sname = sym_get_var_type_name(ast_get_s_val(base_node));
    conclude
    datum fname : series = ast_get_s_val(lhs_node);
    datum ftag : whole = struct_get_field_type(sname, fname);
    datum ftname : series = struct_get_field_type_name(sname, fname);
    datum ltype : series = llvm_get_type(ftag, ftname);

    cg_emit_indent_line("store " + ltype + " " + rhs_val + ", ptr " + gep);
end

algorithm cg_stmt_assign_index(node_id : whole) -> void
begin
    datum lhs_node : whole = ast_get_child(node_id, 0); // AST_INDEX
    datum rhs_node : whole = ast_get_child(node_id, 1);

    datum arr_node : whole = ast_get_child(lhs_node, 0);
    datum idx_node : whole = ast_get_child(lhs_node, 1);

    datum arr_val : series = cg_generate_expression(arr_node);
    datum idx_val : series = cg_generate_expression(idx_node);
    datum rhs_val : series = cg_generate_expression(rhs_node);
    datum rhs_tag : whole = cg_get_node_type_tag(rhs_node);

    datum i64_val : series = cg_cast_elem_to_i64(rhs_val, rhs_tag);
    cg_emit_indent_line("call void @__lors_seq_set(ptr " + arr_val + ", i64 " + idx_val + ", i64 " + i64_val + ")");
end

algorithm cg_stmt_assignment_dispatch(node_id : whole) -> void
begin
    datum kind : whole = ast_get_kind(node_id);
    verify (kind == AST_ASSIGN) then cg_stmt_assign_simple(node_id); result; conclude
    verify (kind == AST_MEMBER_ASSIGN) then cg_stmt_assign_member(node_id); result; conclude
    verify (kind == AST_INDEX_ASSIGN) then cg_stmt_assign_index(node_id); result; conclude
end
