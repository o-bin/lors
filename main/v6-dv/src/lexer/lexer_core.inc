// ==========================================
// Lors Compiler v6 - Lexer Core
// Layer: Lexer
// ==========================================

algorithm lexer_tokenize() -> void
begin
    cycle (lexer_is_at_end() == false) do
        datum cur_c : whole = lexer_peek();
        datum s_line : whole = lex_line;
        datum s_col : whole = lex_col;

        // 1. Whitespace
        verify (char_is_whitespace(cur_c)) then
            lexer_advance();
        otherwise
            // 2. Comments (//)
            verify (cur_c == 47 and lexer_peek_next() == 47) then // '//'
                cycle (lexer_is_at_end() == false and lexer_peek() != 10) do
                    lexer_advance();
                conclude
            otherwise
                // 3. String literal
                verify (cur_c == 34) then // '"'
                    lexer_read_string(s_line, s_col);
                otherwise
                    // 4. Numbers
                    verify (char_is_digit(cur_c)) then
                        lexer_read_number(s_line, s_col);
                    otherwise
                        // 5. Identifiers / Keywords
                        verify (char_is_alpha(cur_c)) then
                            lexer_read_ident(s_line, s_col);
                        otherwise
                            // 6. Symbols & Operators
                            lexer_advance();
                            verify (cur_c == 40) then token_add(TOK_LPAREN, "(", s_line, s_col); conclude
                            verify (cur_c == 41) then token_add(TOK_RPAREN, ")", s_line, s_col); conclude
                            verify (cur_c == 91) then token_add(TOK_LBRACK, "[", s_line, s_col); conclude
                            verify (cur_c == 93) then token_add(TOK_RBRACK, "]", s_line, s_col); conclude
                            verify (cur_c == 123) then token_add(TOK_LBRACE, "{", s_line, s_col); conclude
                            verify (cur_c == 125) then token_add(TOK_RBRACE, "}", s_line, s_col); conclude
                            verify (cur_c == 58) then token_add(TOK_COLON, ":", s_line, s_col); conclude
                            verify (cur_c == 59) then token_add(TOK_SEMICOLON, ";", s_line, s_col); conclude
                            verify (cur_c == 44) then token_add(TOK_COMMA, ",", s_line, s_col); conclude
                            verify (cur_c == 46) then token_add(TOK_DOT, ".", s_line, s_col); conclude
                            verify (cur_c == 43) then token_add(TOK_PLUS, "+", s_line, s_col); conclude
                            verify (cur_c == 42) then token_add(TOK_STAR, "*", s_line, s_col); conclude
                            verify (cur_c == 47) then token_add(TOK_SLASH, "/", s_line, s_col); conclude
                            verify (cur_c == 37) then token_add(TOK_PERCENT, "%", s_line, s_col); conclude

                            verify (cur_c == 45) then // '-'
                                verify (lexer_peek() == 62) then // '->'
                                    lexer_advance();
                                    token_add(TOK_ARROW, "->", s_line, s_col);
                                otherwise
                                    token_add(TOK_MINUS, "-", s_line, s_col);
                                conclude
                            conclude

                            verify (cur_c == 61) then // '='
                                verify (lexer_peek() == 61) then // '=='
                                    lexer_advance();
                                    token_add(TOK_EQ, "==", s_line, s_col);
                                otherwise
                                    token_add(TOK_ASSIGN, "=", s_line, s_line);
                                conclude
                            conclude

                            verify (cur_c == 33) then // '!'
                                verify (lexer_peek() == 61) then // '!='
                                    lexer_advance();
                                    token_add(TOK_NEQ, "!=", s_line, s_col);
                                otherwise
                                    error_report("Unexpected character: !", s_line, s_col);
                                conclude
                            conclude

                            verify (cur_c == 60) then // '<'
                                verify (lexer_peek() == 61) then // '<='
                                    lexer_advance();
                                    token_add(TOK_LTE, "<=", s_line, s_col);
                                otherwise
                                    token_add(TOK_LT, "<", s_line, s_col);
                                conclude
                            conclude

                            verify (cur_c == 62) then // '>'
                                verify (lexer_peek() == 61) then // '>='
                                    lexer_advance();
                                    token_add(TOK_GTE, ">=", s_line, s_col);
                                otherwise
                                    token_add(TOK_GT, ">", s_line, s_col);
                                conclude
                            conclude
                        conclude
                    conclude
                conclude
            conclude
        conclude
    conclude

    token_add(TOK_EOF, "", lex_line, lex_col);
end
