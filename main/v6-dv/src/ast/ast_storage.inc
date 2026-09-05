// ==========================================
// Lors Compiler v6 - AST Node Allocation & Storage
// Layer: Abstract Syntax Tree
// ==========================================

algorithm ast_create_node(kind : whole, s_val : series, n_val : whole, line : whole) -> whole
begin
    datum id : whole = ast_total_nodes;

    ast_kinds_pages = page_int_set(ast_kinds_pages, id, kind, ast_total_nodes);
    ast_s_vals_pages = page_str_set(ast_s_vals_pages, id, s_val);
    ast_n_vals_pages = page_int_set(ast_n_vals_pages, id, n_val, ast_total_nodes);
    ast_lines_pages = page_int_set(ast_lines_pages, id, line, ast_total_nodes);
    ast_type_tags_pages = page_int_set(ast_type_tags_pages, id, TYPE_UNKNOWN, ast_total_nodes);
    ast_type_names_pages = page_str_set(ast_type_names_pages, id, "");
    ast_child_counts_pages = page_int_set(ast_child_counts_pages, id, 0, ast_total_nodes);
    ast_children_pages = page_str_set(ast_children_pages, id, "");

    ast_total_nodes = ast_total_nodes + 1;
    result id;
end

algorithm ast_add_child(parent_id : whole, child_id : whole) -> void
begin
    verify (parent_id < 0 or parent_id >= ast_total_nodes) then result; conclude

    datum cur_cnt : whole = page_int_get(ast_child_counts_pages, parent_id);
    ast_child_counts_pages = page_int_set(ast_child_counts_pages, parent_id, cur_cnt + 1, ast_total_nodes);

    datum cur_children : series = page_str_get(ast_children_pages, parent_id);
    datum new_children : series = cur_children + to_string(child_id) + ",";
    ast_children_pages = page_str_set(ast_children_pages, parent_id, new_children);
end

algorithm ast_get_child_count(parent_id : whole) -> whole
begin
    verify (parent_id < 0 or parent_id >= ast_total_nodes) then result 0; conclude
    result page_int_get(ast_child_counts_pages, parent_id);
end

algorithm ast_get_child(parent_id : whole, child_idx : whole) -> whole
begin
    verify (parent_id < 0 or parent_id >= ast_total_nodes) then result -1; conclude
    datum cur_children : series = page_str_get(ast_children_pages, parent_id);
    result int_list_get(cur_children, child_idx);
end
