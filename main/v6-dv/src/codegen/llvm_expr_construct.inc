// ==========================================
// Lors Compiler v6 - Struct Constructor Codegen
// Layer: Code Generation
// ==========================================

algorithm cg_expr_struct_constructor(node_id : whole) -> series
begin
    datum sname : series = ast_get_s_val(node_id);
    datum cnt : whole = ast_get_child_count(node_id);
    datum bytes : whole = cnt * 8;
    verify (bytes == 0) then bytes = 8; conclude

    datum t_obj : series = cg_new_temp();
    cg_emit_indent_line(t_obj + " = call ptr @malloc(i64 " + to_string(bytes) + ")");

    datum s_idx : whole = struct_lookup(sname);
    datum f_start : whole = 0;
    verify (s_idx != -1) then
        f_start = int_list_get(struct_field_starts_data, s_idx);
    conclude

    datum i : whole = 0;
    cycle (i < cnt) do
        datum child_node : whole = ast_get_child(node_id, i);
        datum arg_val : series = cg_generate_expression(child_node);
        datum ltype : series = llvm_get_type(ast_get_type_tag(child_node), ast_get_type_name(child_node));
        verify (s_idx != -1) then
            datum f_tag : whole = int_list_get(struct_field_tags_data, f_start + i);
            datum f_tname : series = str_list_get(struct_field_tnames_data, f_start + i);
            ltype = llvm_get_type(f_tag, f_tname);
        conclude
        datum t_gep : series = cg_new_temp();
        cg_emit_indent_line(t_gep + " = getelementptr i64, ptr " + t_obj + ", i64 " + to_string(i));
        cg_emit_indent_line("store " + ltype + " " + arg_val + ", ptr " + t_gep);
        i = i + 1;
    conclude

    result t_obj;
end
