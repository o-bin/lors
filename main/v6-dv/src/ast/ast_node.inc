// ==========================================
// Lors Compiler v6 - AST Node Representation
// Layer: Abstract Syntax Tree
// ==========================================

datum ast_kinds_pages : series;
datum ast_s_vals_pages : series;
datum ast_n_vals_pages : series;
datum ast_lines_pages : series;
datum ast_type_tags_pages : series;
datum ast_type_names_pages : series;
datum ast_child_counts_pages : series;
datum ast_children_pages : series;

datum ast_total_nodes : whole = 0;

algorithm ast_init() -> void
begin
    ast_kinds_pages = "";
    ast_s_vals_pages = "";
    ast_n_vals_pages = "";
    ast_lines_pages = "";
    ast_type_tags_pages = "";
    ast_type_names_pages = "";
    ast_child_counts_pages = "";
    ast_children_pages = "";
    ast_total_nodes = 0;
end
