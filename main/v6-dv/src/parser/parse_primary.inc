// ==========================================
// Lors Compiler v6 - Primary Expression Parser
// ==========================================

algorithm parse_primary_expr() -> whole
begin
    datum cur : whole = parse_peek_type();
    datum val : series = parse_peek_val();
    datum line : whole = parse_peek_line();
    datum res_node : whole = 0;

    // 1. Integer Literal
    verify (cur == TOK_INT) then
        parse_advance();
        res_node = ast_create_node(AST_INT, val, 0, line);
        ast_set_type(res_node, TYPE_WHOLE, "whole");
        result res_node;
    conclude

    // 2. Float Literal
    verify (cur == TOK_FLOAT) then
        parse_advance();
        res_node = ast_create_node(AST_FLOAT, val, 0, line);
        ast_set_type(res_node, TYPE_PRECISE, "precise");
        result res_node;
    conclude

    // 3. String Literal
    verify (cur == TOK_STRING) then
        parse_advance();
        res_node = ast_create_node(AST_STRING, val, 0, line);
        ast_set_type(res_node, TYPE_SERIES, "series");
        result res_node;
    conclude

    // 4. Boolean Literal
    verify (cur == TOK_BOOL) then
        parse_advance();
        datum bval : whole = 0;
        verify (val == "true") then bval = 1; conclude
        res_node = ast_create_node(AST_BOOL, val, bval, line);
        ast_set_type(res_node, TYPE_STATE, "state");
        result res_node;
    conclude

    // 5. Parenthesized Expression
    verify (cur == TOK_LPAREN) then
        parse_advance(); // Consume '('
        datum expr_node : whole = parse_expression();
        parse_expect(TOK_RPAREN, "Expected ')' after expression");
        result expr_node;
    conclude

    // 6. Array Literal [e1, e2, ...]
    verify (cur == TOK_LBRACK) then
        parse_advance(); // Consume '['
        datum arr_node : whole = ast_create_node(AST_ARRAY_LIT, "", 0, line);
        verify (parse_peek_type() != TOK_RBRACK) then
            datum elem0 : whole = parse_expression();
            ast_add_child(arr_node, elem0);
            cycle (parse_match(TOK_COMMA)) do
                datum next_elem : whole = parse_expression();
                ast_add_child(arr_node, next_elem);
            conclude
        conclude
        parse_expect(TOK_RBRACK, "Expected ']' after array elements");
        result arr_node;
    conclude

    // 7. Identifier or Call (Func or Struct Constructor)
    verify (cur == TOK_IDENT) then
        parse_advance();
        verify (parse_peek_type() == TOK_LPAREN) then
            parse_advance(); // Consume '('
            datum call_node : whole = ast_create_node(AST_CALL, val, 0, line);
            verify (parse_peek_type() != TOK_RPAREN) then
                datum arg0 : whole = parse_expression();
                ast_add_child(call_node, arg0);
                cycle (parse_match(TOK_COMMA)) do
                    datum next_arg : whole = parse_expression();
                    ast_add_child(call_node, next_arg);
                conclude
            conclude
            parse_expect(TOK_RPAREN, "Expected ')' after arguments");
            result call_node;
        otherwise
            datum ident_node : whole = ast_create_node(AST_IDENT, val, 0, line);
            result ident_node;
        conclude
    conclude

    datum col : whole = parse_peek_col();
    error_report("Unexpected token in expression: '" + val + "'", line, col);
    parse_advance();
    result -1;
end
