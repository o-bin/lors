// ==========================================
// Lors Compiler v6 - Struct Member Access Codegen
// ==========================================

algorithm cg_expr_member_gep(node_id : whole) -> series
begin
    datum base_node : whole = ast_get_child(node_id, 0);
    datum base_val : series = cg_generate_expression(base_node);
    datum sname : series = cg_get_var_struct_name(ast_get_s_val(base_node));
    verify (length(sname) == 0) then
        sname = ast_get_type_name(base_node);
    conclude
    verify (length(sname) == 0) then
        sname = sym_get_var_type_name(ast_get_s_val(base_node));
    conclude
    datum fname : series = ast_get_s_val(node_id);
    datum f_idx : whole = struct_get_field_index(sname, fname);

    datum t_gep : series = cg_new_temp();
    cg_emit_indent_line(t_gep + " = getelementptr i64, ptr " + base_val + ", i64 " + to_string(f_idx));
    result t_gep;
end

algorithm cg_expr_member(node_id : whole) -> series
begin
    datum base_node : whole = ast_get_child(node_id, 0);
    datum sname : series = cg_get_var_struct_name(ast_get_s_val(base_node));
    verify (length(sname) == 0) then
        sname = ast_get_type_name(base_node);
    conclude
    verify (length(sname) == 0) then
        sname = sym_get_var_type_name(ast_get_s_val(base_node));
    conclude
    datum fname : series = ast_get_s_val(node_id);
    datum ftag : whole = struct_get_field_type(sname, fname);
    datum ftname : series = struct_get_field_type_name(sname, fname);
    datum ltype : series = llvm_get_type(ftag, ftname);

    datum t_gep : series = cg_expr_member_gep(node_id);
    datum t_val : series = cg_new_temp();
    cg_emit_indent_line(t_val + " = load " + ltype + ", ptr " + t_gep);
    result t_val;
end
