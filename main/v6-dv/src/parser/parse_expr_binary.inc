// ==========================================
// Lors Compiler v6 - Binary Expressions & Precedence
// ==========================================

algorithm parse_expr_mul() -> whole
begin
    datum left : whole = parse_unary_expr();
    datum continue_loop : state = true;
    cycle (continue_loop) do
        datum cur : whole = parse_peek_type();
        datum line : whole = parse_peek_line();
        verify (cur == TOK_STAR or cur == TOK_SLASH or cur == TOK_PERCENT) then
            datum op : series = parse_peek_val();
            parse_advance();
            datum right : whole = parse_unary_expr();
            datum bin_node : whole = ast_create_node(AST_BINOP, op, 0, line);
            ast_add_child(bin_node, left);
            ast_add_child(bin_node, right);
            left = bin_node;
        otherwise
            continue_loop = false;
        conclude
    conclude
    result left;
end

algorithm parse_expr_add() -> whole
begin
    datum left : whole = parse_expr_mul();
    datum continue_loop : state = true;
    cycle (continue_loop) do
        datum cur : whole = parse_peek_type();
        datum line : whole = parse_peek_line();
        verify (cur == TOK_PLUS or cur == TOK_MINUS) then
            datum op : series = parse_peek_val();
            parse_advance();
            datum right : whole = parse_expr_mul();
            datum bin_node : whole = ast_create_node(AST_BINOP, op, 0, line);
            ast_add_child(bin_node, left);
            ast_add_child(bin_node, right);
            left = bin_node;
        otherwise
            continue_loop = false;
        conclude
    conclude
    result left;
end

algorithm parse_expr_rel() -> whole
begin
    datum left : whole = parse_expr_add();
    datum continue_loop : state = true;
    cycle (continue_loop) do
        datum cur : whole = parse_peek_type();
        datum line : whole = parse_peek_line();
        verify (cur == TOK_LT or cur == TOK_LTE or cur == TOK_GT or cur == TOK_GTE) then
            datum op : series = parse_peek_val();
            parse_advance();
            datum right : whole = parse_expr_add();
            datum bin_node : whole = ast_create_node(AST_BINOP, op, 0, line);
            ast_add_child(bin_node, left);
            ast_add_child(bin_node, right);
            left = bin_node;
        otherwise
            continue_loop = false;
        conclude
    conclude
    result left;
end

algorithm parse_expr_eq() -> whole
begin
    datum left : whole = parse_expr_rel();
    datum continue_loop : state = true;
    cycle (continue_loop) do
        datum cur : whole = parse_peek_type();
        datum line : whole = parse_peek_line();
        verify (cur == TOK_EQ or cur == TOK_NEQ) then
            datum op : series = parse_peek_val();
            parse_advance();
            datum right : whole = parse_expr_rel();
            datum bin_node : whole = ast_create_node(AST_BINOP, op, 0, line);
            ast_add_child(bin_node, left);
            ast_add_child(bin_node, right);
            left = bin_node;
        otherwise
            continue_loop = false;
        conclude
    conclude
    result left;
end

algorithm parse_expr_and() -> whole
begin
    datum left : whole = parse_expr_eq();
    datum continue_loop : state = true;
    cycle (continue_loop) do
        datum cur : whole = parse_peek_type();
        datum line : whole = parse_peek_line();
        verify (cur == TOK_AND) then
            parse_advance();
            datum right : whole = parse_expr_eq();
            datum bin_node : whole = ast_create_node(AST_BINOP, "and", 0, line);
            ast_add_child(bin_node, left);
            ast_add_child(bin_node, right);
            left = bin_node;
        otherwise
            continue_loop = false;
        conclude
    conclude
    result left;
end

algorithm parse_expr_or() -> whole
begin
    datum left : whole = parse_expr_and();
    datum continue_loop : state = true;
    cycle (continue_loop) do
        datum cur : whole = parse_peek_type();
        datum line : whole = parse_peek_line();
        verify (cur == TOK_OR) then
            parse_advance();
            datum right : whole = parse_expr_and();
            datum bin_node : whole = ast_create_node(AST_BINOP, "or", 0, line);
            ast_add_child(bin_node, left);
            ast_add_child(bin_node, right);
            left = bin_node;
        otherwise
            continue_loop = false;
        conclude
    conclude
    result left;
end

algorithm parse_expression() -> whole
begin
    result parse_expr_or();
end
