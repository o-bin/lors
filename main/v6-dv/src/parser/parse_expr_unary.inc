// ==========================================
// Lors Compiler v6 - Unary Expression Parser
// ==========================================

algorithm parse_unary_expr() -> whole
begin
    datum cur : whole = parse_peek_type();
    datum line : whole = parse_peek_line();
    datum sub_expr : whole = 0;
    datum unop_node : whole = 0;

    // 1. Logical NOT
    verify (cur == TOK_NOT) then
        parse_advance();
        sub_expr = parse_unary_expr();
        unop_node = ast_create_node(AST_UNOP, "not", 0, line);
        ast_add_child(unop_node, sub_expr);
        result unop_node;
    conclude

    // 2. Unary MINUS
    verify (cur == TOK_MINUS) then
        parse_advance();
        sub_expr = parse_unary_expr();
        unop_node = ast_create_node(AST_UNOP, "-", 0, line);
        ast_add_child(unop_node, sub_expr);
        result unop_node;
    conclude

    result parse_postfix_expr();
end
