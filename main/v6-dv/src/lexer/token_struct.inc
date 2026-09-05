// ==========================================
// Lors Compiler v6 - Token Storage
// Layer: Lexer (Paged Token Buffers)
// ==========================================

datum tok_types_pages : series;
datum tok_values_pages : series;
datum tok_lines_pages : series;
datum tok_cols_pages : series;
datum tok_count : whole = 0;

algorithm token_clear() -> void
begin
    tok_types_pages = "";
    tok_values_pages = "";
    tok_lines_pages = "";
    tok_cols_pages = "";
    tok_count = 0;
end

algorithm token_add(kind : whole, val : series, line : whole, col : whole) -> void
begin
    tok_types_pages = page_int_set(tok_types_pages, tok_count, kind, tok_count);
    tok_values_pages = page_str_set(tok_values_pages, tok_count, val);
    tok_lines_pages = page_int_set(tok_lines_pages, tok_count, line, tok_count);
    tok_cols_pages = page_int_set(tok_cols_pages, tok_count, col, tok_count);
    tok_count = tok_count + 1;
end

algorithm token_get_type(idx : whole) -> whole
begin
    verify (idx >= 0 and idx < tok_count) then
        result page_int_get(tok_types_pages, idx);
    conclude
    result TOK_EOF;
end

algorithm token_get_val(idx : whole) -> series
begin
    verify (idx >= 0 and idx < tok_count) then
        result page_str_get(tok_values_pages, idx);
    conclude
    result "";
end

algorithm token_get_line(idx : whole) -> whole
begin
    verify (idx >= 0 and idx < tok_count) then
        result page_int_get(tok_lines_pages, idx);
    conclude
    result 0;
end

algorithm token_get_col(idx : whole) -> whole
begin
    verify (idx >= 0 and idx < tok_count) then
        result page_int_get(tok_cols_pages, idx);
    conclude
    result 0;
end
