// ==========================================
// Lors Compiler v6 - Postfix Expression Parser
// ==========================================

algorithm parse_postfix_expr() -> whole
begin
    datum expr : whole = parse_primary_expr();
    verify (expr == -1) then
        result -1;
    conclude

    datum continue_loop : state = true;
    cycle (continue_loop) do
        datum cur : whole = parse_peek_type();
        datum line : whole = parse_peek_line();

        // 1. Member access: expr.field
        verify (cur == TOK_DOT) then
            parse_advance(); // Consume '.'
            datum field_ok : state = parse_expect(TOK_IDENT, "Expected field name after '.'");
            datum field_name : series = token_get_val(parse_pos - 1);
            datum member_node : whole = ast_create_node(AST_MEMBER, field_name, 0, line);
            ast_add_child(member_node, expr);
            expr = member_node;
        otherwise
            // 2. Index access: expr[index_expr]
            verify (cur == TOK_LBRACK) then
                parse_advance(); // Consume '['
                datum idx_expr : whole = parse_expression();
                parse_expect(TOK_RBRACK, "Expected ']' after index expression");
                datum index_node : whole = ast_create_node(AST_INDEX, "", 0, line);
                ast_add_child(index_node, expr);
                ast_add_child(index_node, idx_expr);
                expr = index_node;
            otherwise
                continue_loop = false;
            conclude
        conclude
    conclude

    result expr;
end
