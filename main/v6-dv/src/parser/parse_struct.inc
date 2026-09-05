// ==========================================
// Lors Compiler v6 - Structure Declaration Parser
// ==========================================

algorithm parse_structure_decl() -> whole
begin
    datum line : whole = parse_peek_line();
    parse_advance(); // Consume 'structure'

    datum name_ok : state = parse_expect(TOK_IDENT, "Expected structure name");
    datum struct_name : series = token_get_val(parse_pos - 1);

    parse_expect(TOK_BEGIN, "Expected 'begin' in structure declaration");

    datum struct_node : whole = ast_create_node(AST_STRUCT_DECL, struct_name, 0, line);
    ast_set_type(struct_node, TYPE_STRUCT, struct_name);

    cycle (parse_peek_type() != TOK_END and parse_peek_type() != TOK_EOF) do
        verify (parse_peek_type() == TOK_DATUM) then
            datum field_decl : whole = parse_datum_decl();
            ast_add_child(struct_node, field_decl);
        otherwise
            datum l : whole = parse_peek_line();
            datum c : whole = parse_peek_col();
            error_report("Expected field declaration inside structure", l, c);
            parse_advance();
        conclude
    conclude

    parse_expect(TOK_END, "Expected 'end' to close structure declaration");
    result struct_node;
end
