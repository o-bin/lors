// ==========================================
// Lors Compiler v6 - Statement Codegen Dispatcher
// ==========================================

algorithm cg_generate_statement(node_id : whole) -> void
begin
    verify (node_id < 0 or node_id >= ast_total_nodes) then
        result;
    conclude

    datum kind : whole = ast_get_kind(node_id);

    verify (kind == AST_DATUM_DECL) then
        cg_stmt_datum(node_id);
        result;
    conclude

    verify (kind == AST_ASSIGN or kind == AST_MEMBER_ASSIGN or kind == AST_INDEX_ASSIGN) then
        cg_stmt_assignment_dispatch(node_id);
        result;
    conclude

    verify (kind == AST_VERIFY) then
        cg_stmt_verify(node_id);
        result;
    conclude

    verify (kind == AST_CYCLE) then
        cg_stmt_cycle(node_id);
        result;
    conclude

    verify (kind == AST_REVEAL) then
        cg_stmt_reveal(node_id);
        result;
    conclude

    verify (kind == AST_RESULT) then
        cg_stmt_result(node_id);
        result;
    conclude

    verify (kind == AST_EXPR_STMT) then
        datum child : whole = ast_get_child(node_id, 0);
        cg_generate_expression(child);
        result;
    conclude

    verify (kind == AST_BLOCK) then
        datum cnt : whole = ast_get_child_count(node_id);
        datum i : whole = 0;
        cycle (i < cnt) do
            cg_generate_statement(ast_get_child(node_id, i));
            i = i + 1;
        conclude
        result;
    conclude
end
