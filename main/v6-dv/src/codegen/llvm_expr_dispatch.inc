// ==========================================
// Lors Compiler v6 - Expression Codegen Dispatcher
// ==========================================

algorithm cg_generate_expression(node_id : whole) -> series
begin
    verify (node_id < 0 or node_id >= ast_total_nodes) then
        result "0";
    conclude

    datum kind : whole = ast_get_kind(node_id);

    verify (kind == AST_INT or kind == AST_FLOAT or kind == AST_STRING or kind == AST_BOOL or kind == AST_IDENT) then
        result cg_expr_primary(node_id);
    conclude

    verify (kind == AST_BINOP) then
        result cg_expr_binary(node_id);
    conclude

    verify (kind == AST_UNOP) then
        result cg_expr_unary(node_id);
    conclude

    verify (kind == AST_CALL) then
        result cg_expr_call(node_id);
    conclude

    verify (kind == AST_MEMBER) then
        result cg_expr_member(node_id);
    conclude

    verify (kind == AST_INDEX) then
        result cg_expr_index(node_id);
    conclude

    verify (kind == AST_ARRAY_LIT) then
        result cg_expr_array_lit(node_id);
    conclude

    result "0";
end
