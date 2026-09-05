// ==========================================
// Lors Compiler v6 - Algorithm Declaration Parser
// ==========================================

algorithm parse_algorithm_decl() -> whole
begin
    datum line : whole = parse_peek_line();
    parse_advance(); // Consume 'algorithm'

    datum name_ok : state = parse_expect(TOK_IDENT, "Expected algorithm name");
    datum fn_name : series = token_get_val(parse_pos - 1);

    parse_expect(TOK_LPAREN, "Expected '(' after algorithm name");

    datum fn_node : whole = ast_create_node(AST_ALGORITHM_DECL, fn_name, 0, line);

    // Parse parameters
    verify (parse_peek_type() != TOK_RPAREN) then
        datum p_ok : state = parse_expect(TOK_IDENT, "Expected parameter name");
        datum p_name : series = token_get_val(parse_pos - 1);
        datum p_line : whole = parse_peek_line();

        parse_expect(TOK_COLON, "Expected ':' after parameter name");
        parse_type_specifier();

        datum param_node : whole = ast_create_node(AST_DATUM_DECL, p_name, 0, p_line);
        ast_set_type(param_node, parsed_type_tag, parsed_type_name);
        ast_add_child(fn_node, param_node);

        cycle (parse_match(TOK_COMMA)) do
            datum pn_ok : state = parse_expect(TOK_IDENT, "Expected parameter name");
            datum pn_name : series = token_get_val(parse_pos - 1);
            datum pn_line : whole = parse_peek_line();

            parse_expect(TOK_COLON, "Expected ':' after parameter name");
            parse_type_specifier();

            datum pnext_node : whole = ast_create_node(AST_DATUM_DECL, pn_name, 0, pn_line);
            ast_set_type(pnext_node, parsed_type_tag, parsed_type_name);
            ast_add_child(fn_node, pnext_node);
        conclude
    conclude

    parse_expect(TOK_RPAREN, "Expected ')' after parameter list");

    // Return type -> RetType
    parse_expect(TOK_ARROW, "Expected '->' for algorithm return type");
    parse_type_specifier();
    ast_set_type(fn_node, parsed_type_tag, parsed_type_name);

    // Check if it's an external prototype (ends in ';') or definition (begin ... end)
    verify (parse_match(TOK_SEMICOLON)) then
        ast_set_n_val(fn_node, 1); // 1 = external declaration
        result fn_node;
    conclude

    parse_expect(TOK_BEGIN, "Expected 'begin' for algorithm body");
    datum body_block : whole = parse_block_until(TOK_END, TOK_EOF);
    parse_expect(TOK_END, "Expected 'end' to close algorithm body");

    ast_add_child(fn_node, body_block);
    result fn_node;
end
