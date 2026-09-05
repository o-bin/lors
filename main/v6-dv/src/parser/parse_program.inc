// ==========================================
// Lors Compiler v6 - Program & Statement Parser
// ==========================================

algorithm parse_statement() -> whole
begin
    datum cur : whole = parse_peek_type();

    verify (cur == TOK_DATUM) then
        result parse_datum_decl();
    conclude
    verify (cur == TOK_VERIFY) then
        result parse_verify_stmt();
    conclude
    verify (cur == TOK_CYCLE) then
        result parse_cycle_stmt();
    conclude
    verify (cur == TOK_REVEAL) then
        result parse_reveal_stmt();
    conclude
    verify (cur == TOK_RESULT) then
        result parse_result_stmt();
    conclude

    result parse_assign_or_expr_stmt();
end

algorithm parse_program() -> whole
begin
    datum line : whole = parse_peek_line();
    datum prog_node : whole = ast_create_node(AST_PROGRAM, "", 0, line);

    cycle (parse_peek_type() != TOK_EOF) do
        datum cur : whole = parse_peek_type();

        verify (cur == TOK_STRUCTURE) then
            datum struct_node : whole = parse_structure_decl();
            ast_add_child(prog_node, struct_node);
        otherwise
            verify (cur == TOK_ALGORITHM) then
                datum fn_node : whole = parse_algorithm_decl();
                ast_add_child(prog_node, fn_node);
            otherwise
                verify (cur == TOK_DATUM) then
                    datum global_node : whole = parse_datum_decl();
                    ast_set_kind(global_node, AST_GLOBAL_DATUM);
                    ast_set_n_val(global_node, 1); // 1 = global datum
                    ast_add_child(prog_node, global_node);
                otherwise
                    datum l : whole = parse_peek_line();
                    datum c : whole = parse_peek_col();
                    datum val : series = parse_peek_val();
                    error_report("Unexpected top-level item: '" + val + "'", l, c);
                    parse_advance();
                conclude
            conclude
        conclude
    conclude

    result prog_node;
end
