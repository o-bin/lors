// ==========================================
// Lors Compiler v6 - I/O & Return Statements
// ==========================================

algorithm parse_reveal_stmt() -> whole
begin
    datum line : whole = parse_peek_line();
    parse_advance(); // Consume 'reveal'
    parse_expect(TOK_LPAREN, "Expected '(' after 'reveal'");
    datum expr : whole = parse_expression();
    parse_expect(TOK_RPAREN, "Expected ')' after reveal expression");
    parse_expect(TOK_SEMICOLON, "Expected ';' after reveal statement");

    datum reveal_node : whole = ast_create_node(AST_REVEAL, "", 0, line);
    ast_add_child(reveal_node, expr);
    result reveal_node;
end

algorithm parse_result_stmt() -> whole
begin
    datum line : whole = parse_peek_line();
    parse_advance(); // Consume 'result'
    datum result_node : whole = ast_create_node(AST_RESULT, "", 0, line);

    verify (parse_peek_type() != TOK_SEMICOLON) then
        datum expr : whole = parse_expression();
        ast_add_child(result_node, expr);
    conclude

    parse_expect(TOK_SEMICOLON, "Expected ';' after result statement");
    result result_node;
end
