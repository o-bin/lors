// ==========================================
// Lors Compiler v6 - Literals & Identifiers
// Layer: Lexer
// ==========================================

algorithm lexer_read_number(start_line : whole, start_col : whole) -> void
begin
    datum num_str : series = "";
    datum is_float : state = false;

    cycle (char_is_digit(lexer_peek())) do
        num_str = num_str + substring(lex_src, lex_pos, 1);
        lexer_advance();
    conclude

    verify (lexer_peek() == 46 and char_is_digit(lexer_peek_next())) then // '.'
        is_float = true;
        num_str = num_str + ".";
        lexer_advance(); // consume '.'

        cycle (char_is_digit(lexer_peek())) do
            num_str = num_str + substring(lex_src, lex_pos, 1);
            lexer_advance();
        conclude
    conclude

    verify (is_float) then
        token_add(TOK_FLOAT, num_str, start_line, start_col);
    otherwise
        token_add(TOK_INT, num_str, start_line, start_col);
    conclude
end

algorithm lexer_read_string(start_line : whole, start_col : whole) -> void
begin
    lexer_advance(); // Consume opening quote
    datum str_val : series = "";

    cycle (lexer_is_at_end() == false and lexer_peek() != 34) do
        datum c : whole = lexer_peek();
        verify (c == 92) then // '\'
            lexer_advance(); // consume '\'
            datum next_c : whole = lexer_peek();
            verify (next_c == 110) then str_val = str_val + "\n"; conclude // 'n'
            verify (next_c == 116) then str_val = str_val + "\t"; conclude // 't'
            verify (next_c == 34) then str_val = str_val + "\""; conclude  // '"'
            verify (next_c == 92) then str_val = str_val + "\\"; conclude  // '\'
            verify (next_c != 110 and next_c != 116 and next_c != 34 and next_c != 92) then
                str_val = str_val + substring(lex_src, lex_pos, 1);
            conclude
            lexer_advance();
        otherwise
            str_val = str_val + substring(lex_src, lex_pos, 1);
            lexer_advance();
        conclude
    conclude

    verify (lexer_is_at_end()) then
        error_report("Unterminated string literal", start_line, start_col);
    otherwise
        lexer_advance(); // Consume closing quote
        token_add(TOK_STRING, str_val, start_line, start_col);
    conclude
end

algorithm lexer_read_ident(start_line : whole, start_col : whole) -> void
begin
    datum ident_str : series = "";
    cycle (char_is_alnum(lexer_peek())) do
        ident_str = ident_str + substring(lex_src, lex_pos, 1);
        lexer_advance();
    conclude

    datum kind : whole = lexer_match_keyword(ident_str);
    token_add(kind, ident_str, start_line, start_col);
end
