// ==========================================
// Lors Compiler v6 - Lexer State
// ==========================================

datum lex_src : series;
datum lex_len : whole = 0;
datum lex_pos : whole = 0;
datum lex_line : whole = 1;
datum lex_col : whole = 1;

algorithm lexer_state_init(source : series) -> void
begin
    token_clear();
    lex_src = source;
    lex_len = length(source);
    lex_pos = 0;
    lex_line = 1;
    lex_col = 1;
end

algorithm lexer_peek() -> whole
begin
    verify (lex_pos < lex_len) then
        result char_at(lex_src, lex_pos);
    conclude
    result 0;
end

algorithm lexer_peek_next() -> whole
begin
    verify (lex_pos + 1 < lex_len) then
        result char_at(lex_src, lex_pos + 1);
    conclude
    result 0;
end

algorithm lexer_advance() -> whole
begin
    verify (lex_pos >= lex_len) then
        result 0;
    conclude
    datum c : whole = char_at(lex_src, lex_pos);
    lex_pos = lex_pos + 1;
    verify (c == 10) then // '\n'
        lex_line = lex_line + 1;
        lex_col = 1;
    otherwise
        lex_col = lex_col + 1;
    conclude
    result c;
end

algorithm lexer_is_at_end() -> state
begin
    verify (lex_pos >= lex_len) then
        result true;
    conclude
    result false;
end
