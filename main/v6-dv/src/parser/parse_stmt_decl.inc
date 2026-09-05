// ==========================================
// Lors Compiler v6 - Datum Declaration Parser
// ==========================================

algorithm parse_datum_decl() -> whole
begin
    datum line : whole = parse_peek_line();
    parse_advance(); // Consume 'datum'

    datum name_ok : state = parse_expect(TOK_IDENT, "Expected variable name after 'datum'");
    datum var_name : series = token_get_val(parse_pos - 1);

    parse_expect(TOK_COLON, "Expected ':' after variable name");

    datum type_ok : state = parse_type_specifier();
    datum tag : whole = parsed_type_tag;
    datum tname : series = parsed_type_name;

    datum decl_node : whole = ast_create_node(AST_DATUM_DECL, var_name, 0, line);
    ast_set_type(decl_node, tag, tname);

    verify (parse_match(TOK_ASSIGN)) then
        datum init_expr : whole = parse_expression();
        ast_add_child(decl_node, init_expr);
    conclude

    parse_expect(TOK_SEMICOLON, "Expected ';' after datum declaration");
    result decl_node;
end
