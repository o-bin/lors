// ==========================================
// Lors Compiler v6 - AST Node Helpers & Accessors
// Layer: Abstract Syntax Tree
// ==========================================

algorithm ast_set_type(node_id : whole, tag : whole, type_name : series) -> void
begin
    verify (node_id < 0 or node_id >= ast_total_nodes) then result; conclude
    ast_type_tags_pages = page_int_set(ast_type_tags_pages, node_id, tag, ast_total_nodes);
    ast_type_names_pages = page_str_set(ast_type_names_pages, node_id, type_name);
end

algorithm ast_get_kind(node_id : whole) -> whole
begin
    verify (node_id < 0 or node_id >= ast_total_nodes) then result AST_INT; conclude
    result page_int_get(ast_kinds_pages, node_id);
end

algorithm ast_set_kind(node_id : whole, kind : whole) -> void
begin
    verify (node_id < 0 or node_id >= ast_total_nodes) then result; conclude
    ast_kinds_pages = page_int_set(ast_kinds_pages, node_id, kind, ast_total_nodes);
end

algorithm ast_get_s_val(node_id : whole) -> series
begin
    verify (node_id < 0 or node_id >= ast_total_nodes) then result ""; conclude
    result page_str_get(ast_s_vals_pages, node_id);
end

algorithm ast_set_s_val(node_id : whole, val : series) -> void
begin
    verify (node_id < 0 or node_id >= ast_total_nodes) then result; conclude
    ast_s_vals_pages = page_str_set(ast_s_vals_pages, node_id, val);
end

algorithm ast_get_n_val(node_id : whole) -> whole
begin
    verify (node_id < 0 or node_id >= ast_total_nodes) then result 0; conclude
    result page_int_get(ast_n_vals_pages, node_id);
end

algorithm ast_set_n_val(node_id : whole, val : whole) -> void
begin
    verify (node_id < 0 or node_id >= ast_total_nodes) then result; conclude
    ast_n_vals_pages = page_int_set(ast_n_vals_pages, node_id, val, ast_total_nodes);
end

algorithm ast_get_line(node_id : whole) -> whole
begin
    verify (node_id < 0 or node_id >= ast_total_nodes) then result 0; conclude
    result page_int_get(ast_lines_pages, node_id);
end

algorithm ast_get_type_tag(node_id : whole) -> whole
begin
    verify (node_id < 0 or node_id >= ast_total_nodes) then result TYPE_UNKNOWN; conclude
    result page_int_get(ast_type_tags_pages, node_id);
end

algorithm ast_get_type_name(node_id : whole) -> series
begin
    verify (node_id < 0 or node_id >= ast_total_nodes) then result ""; conclude
    result page_str_get(ast_type_names_pages, node_id);
end
