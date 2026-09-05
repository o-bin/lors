// ==========================================
// Lors Compiler v6 - Control Flow Statements
// ==========================================

algorithm parse_block_until(stop1 : whole, stop2 : whole) -> whole
begin
    datum line : whole = parse_peek_line();
    datum block_node : whole = ast_create_node(AST_BLOCK, "", 0, line);

    datum continue_loop : state = true;
    cycle (continue_loop) do
        datum cur : whole = parse_peek_type();
        verify (cur == TOK_EOF or cur == stop1 or cur == stop2) then
            continue_loop = false;
        otherwise
            datum stmt : whole = parse_statement();
            verify (stmt != -1) then
                ast_add_child(block_node, stmt);
            conclude
        conclude
    conclude

    result block_node;
end

algorithm parse_verify_stmt() -> whole
begin
    datum line : whole = parse_peek_line();
    parse_advance(); // Consume 'verify'

    parse_expect(TOK_LPAREN, "Expected '(' after 'verify'");
    datum cond_expr : whole = parse_expression();
    parse_expect(TOK_RPAREN, "Expected ')' after verify condition");
    parse_expect(TOK_THEN, "Expected 'then' after verify condition");

    datum then_block : whole = parse_block_until(TOK_OTHERWISE, TOK_CONCLUDE);

    datum verify_node : whole = ast_create_node(AST_VERIFY, "", 0, line);
    ast_add_child(verify_node, cond_expr);
    ast_add_child(verify_node, then_block);

    verify (parse_match(TOK_OTHERWISE)) then
        datum else_block : whole = parse_block_until(TOK_CONCLUDE, TOK_EOF);
        ast_add_child(verify_node, else_block);
    conclude

    parse_expect(TOK_CONCLUDE, "Expected 'conclude' to close verify statement");
    result verify_node;
end

algorithm parse_cycle_stmt() -> whole
begin
    datum line : whole = parse_peek_line();
    parse_advance(); // Consume 'cycle'

    parse_expect(TOK_LPAREN, "Expected '(' after 'cycle'");
    datum cond_expr : whole = parse_expression();
    parse_expect(TOK_RPAREN, "Expected ')' after cycle condition");
    parse_expect(TOK_DO, "Expected 'do' after cycle condition");

    datum body_block : whole = parse_block_until(TOK_CONCLUDE, TOK_EOF);
    parse_expect(TOK_CONCLUDE, "Expected 'conclude' to close cycle loop");

    datum cycle_node : whole = ast_create_node(AST_CYCLE, "", 0, line);
    ast_add_child(cycle_node, cond_expr);
    ast_add_child(cycle_node, body_block);
    result cycle_node;
end
