// ==========================================
// Lors Compiler v6 - Sequence / Array Codegen
// ==========================================

algorithm cg_cast_elem_to_i64(val : series, tag : whole) -> series
begin
    datum t : series = "";
    verify (tag == TYPE_PRECISE) then
        t = cg_new_temp();
        cg_emit_indent_line(t + " = bitcast double " + val + " to i64");
        result t;
    conclude
    verify (tag == TYPE_SERIES or tag == TYPE_STRUCT or tag == TYPE_SEQUENCE) then
        t = cg_new_temp();
        cg_emit_indent_line(t + " = ptrtoint ptr " + val + " to i64");
        result t;
    conclude
    verify (tag == TYPE_STATE) then
        t = cg_new_temp();
        cg_emit_indent_line(t + " = zext i1 " + val + " to i64");
        result t;
    conclude
    result val;
end

algorithm cg_expr_array_lit(node_id : whole) -> series
begin
    datum cnt : whole = ast_get_child_count(node_id);
    datum t_seq : series = cg_new_temp();
    cg_emit_indent_line(t_seq + " = call ptr @__lors_seq_create(i64 " + to_string(cnt) + ")");

    datum i : whole = 0;
    cycle (i < cnt) do
        datum ch : whole = ast_get_child(node_id, i);
        datum ch_val : series = cg_generate_expression(ch);
        datum ch_tag : whole = cg_get_node_type_tag(ch);
        datum i64_val : series = cg_cast_elem_to_i64(ch_val, ch_tag);
        cg_emit_indent_line("call ptr @__lors_seq_append(ptr " + t_seq + ", i64 " + i64_val + ")");
        i = i + 1;
    conclude

    result t_seq;
end

algorithm cg_expr_index(node_id : whole) -> series
begin
    datum arr_node : whole = ast_get_child(node_id, 0);
    datum idx_node : whole = ast_get_child(node_id, 1);
    datum arr_val : series = cg_generate_expression(arr_node);
    datum idx_val : series = cg_generate_expression(idx_node);

    datum t_raw : series = cg_new_temp();
    cg_emit_indent_line(t_raw + " = call i64 @__lors_seq_get(ptr " + arr_val + ", i64 " + idx_val + ")");

    datum elem_tag : whole = cg_get_node_type_tag(node_id);
    verify (elem_tag == TYPE_PRECISE) then
        datum t_fp : series = cg_new_temp();
        cg_emit_indent_line(t_fp + " = bitcast i64 " + t_raw + " to double");
        result t_fp;
    conclude
    verify (elem_tag == TYPE_SERIES or elem_tag == TYPE_STRUCT or elem_tag == TYPE_SEQUENCE) then
        datum t_ptr : series = cg_new_temp();
        cg_emit_indent_line(t_ptr + " = inttoptr i64 " + t_raw + " to ptr");
        result t_ptr;
    conclude
    verify (elem_tag == TYPE_STATE) then
        datum t_b : series = cg_new_temp();
        cg_emit_indent_line(t_b + " = trunc i64 " + t_raw + " to i1");
        result t_b;
    conclude

    result t_raw;
end
