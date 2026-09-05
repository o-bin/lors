// ==========================================
// Lors Compiler v6 - Statement Semantic Checking
// Layer: Semantic Analysis
// ==========================================

algorithm type_check_stmt(stmt_id : whole) -> void
begin
    verify (stmt_id < 0 or stmt_id >= ast_total_nodes) then
        result;
    conclude

    datum kind : whole = ast_get_kind(stmt_id);

    // 1. Datum Declaration
    verify (kind == AST_DATUM_DECL or kind == AST_GLOBAL_DATUM) then
        datum vname : series = ast_get_s_val(stmt_id);
        datum vtag : whole = ast_get_type_tag(stmt_id);
        datum vtname : series = ast_get_type_name(stmt_id);
        sym_add_var(vname, vtag, vtname);
        verify (ast_get_child_count(stmt_id) > 0) then
            datum init_node : whole = ast_get_child(stmt_id, 0);
            datum init_tag : whole = infer_expr_type(init_node);
            verify (init_tag == TYPE_UNKNOWN and vtag != TYPE_UNKNOWN) then
                ast_set_type(init_node, vtag, vtname);
            conclude
        conclude
        result;
    conclude

    // 2. Assignments
    verify (kind == AST_ASSIGN) then
        datum lhs_node : whole = ast_get_child(stmt_id, 0);
        datum rhs_node : whole = ast_get_child(stmt_id, 1);
        datum lhs_tag : whole = infer_expr_type(lhs_node);
        datum rhs_tag : whole = infer_expr_type(rhs_node);
        verify (rhs_tag == TYPE_UNKNOWN and lhs_tag != TYPE_UNKNOWN) then
            ast_set_type(rhs_node, lhs_tag, ast_get_type_name(lhs_node));
        conclude
        result;
    conclude
    verify (kind == AST_MEMBER_ASSIGN or kind == AST_INDEX_ASSIGN) then
        infer_expr_type(ast_get_child(stmt_id, 0));
        infer_expr_type(ast_get_child(stmt_id, 1));
        result;
    conclude

    // 3. Verify (if/else)
    verify (kind == AST_VERIFY) then
        infer_expr_type(ast_get_child(stmt_id, 0)); // condition
        type_check_stmt(ast_get_child(stmt_id, 1));  // then block
        verify (ast_get_child_count(stmt_id) > 2) then
            type_check_stmt(ast_get_child(stmt_id, 2)); // else block
        conclude
        result;
    conclude

    // 4. Cycle (while)
    verify (kind == AST_CYCLE) then
        infer_expr_type(ast_get_child(stmt_id, 0)); // condition
        type_check_stmt(ast_get_child(stmt_id, 1));  // body block
        result;
    conclude

    // 5. Reveal & Result & ExprStmt
    verify (kind == AST_REVEAL or kind == AST_EXPR_STMT) then
        infer_expr_type(ast_get_child(stmt_id, 0));
        result;
    conclude
    verify (kind == AST_RESULT) then
        verify (ast_get_child_count(stmt_id) > 0) then
            infer_expr_type(ast_get_child(stmt_id, 0));
        conclude
        result;
    conclude

    // 6. Block
    verify (kind == AST_BLOCK) then
        sym_enter_scope();
        datum cnt : whole = ast_get_child_count(stmt_id);
        datum i : whole = 0;
        cycle (i < cnt) do
            type_check_stmt(ast_get_child(stmt_id, i));
            i = i + 1;
        conclude
        sym_exit_scope();
        result;
    conclude
end
