// ==========================================
// Lors Compiler v6 - Assignment & Expression Statements
// ==========================================

algorithm parse_assign_or_expr_stmt() -> whole
begin
    datum line : whole = parse_peek_line();
    datum lhs_expr : whole = parse_postfix_expr();

    // Check if it is an assignment
    verify (parse_match(TOK_ASSIGN)) then
        datum rhs_expr : whole = parse_expression();
        parse_expect(TOK_SEMICOLON, "Expected ';' after assignment");

        datum lhs_kind : whole = ast_get_kind(lhs_expr);
        datum assign_node : whole = -1;

        verify (lhs_kind == AST_IDENT) then
            assign_node = ast_create_node(AST_ASSIGN, ast_get_s_val(lhs_expr), 0, line);
            ast_add_child(assign_node, lhs_expr);
            ast_add_child(assign_node, rhs_expr);
            result assign_node;
        conclude

        verify (lhs_kind == AST_MEMBER) then
            assign_node = ast_create_node(AST_MEMBER_ASSIGN, ast_get_s_val(lhs_expr), 0, line);
            ast_add_child(assign_node, lhs_expr);
            ast_add_child(assign_node, rhs_expr);
            result assign_node;
        conclude

        verify (lhs_kind == AST_INDEX) then
            assign_node = ast_create_node(AST_INDEX_ASSIGN, "", 0, line);
            ast_add_child(assign_node, lhs_expr);
            ast_add_child(assign_node, rhs_expr);
            result assign_node;
        conclude

        error_report("Invalid target for assignment", line, parse_peek_col());
        result -1;
    conclude

    // Expression statement (e.g. function call)
    parse_expect(TOK_SEMICOLON, "Expected ';' after expression statement");
    datum expr_stmt : whole = ast_create_node(AST_EXPR_STMT, "", 0, line);
    ast_add_child(expr_stmt, lhs_expr);
    result expr_stmt;
end
