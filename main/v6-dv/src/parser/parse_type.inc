// ==========================================
// Lors Compiler v6 - Type Parsing
// Layer: Parser
// ==========================================

datum parsed_type_tag : whole = TYPE_UNKNOWN;
datum parsed_type_name : series;

algorithm parse_type_specifier() -> state
begin
    datum cur : whole = parse_peek_type();
    verify (cur == TOK_TYPE_WHOLE) then
        parsed_type_tag = TYPE_WHOLE;
        parsed_type_name = "whole";
        parse_advance();
        result true;
    conclude
    verify (cur == TOK_TYPE_PRECISE) then
        parsed_type_tag = TYPE_PRECISE;
        parsed_type_name = "precise";
        parse_advance();
        result true;
    conclude
    verify (cur == TOK_TYPE_SERIES) then
        parsed_type_tag = TYPE_SERIES;
        parsed_type_name = "series";
        parse_advance();
        result true;
    conclude
    verify (cur == TOK_TYPE_STATE) then
        parsed_type_tag = TYPE_STATE;
        parsed_type_name = "state";
        parse_advance();
        result true;
    conclude
    verify (cur == TOK_TYPE_VOID) then
        parsed_type_tag = TYPE_VOID;
        parsed_type_name = "void";
        parse_advance();
        result true;
    conclude

    // sequence<ElemType>
    verify (cur == TOK_TYPE_SEQUENCE) then
        parse_advance();
        datum ok_lt : state = parse_expect(TOK_LT, "Expected '<' after sequence");
        datum ok_elem : state = parse_type_specifier();
        datum elem_name : series = parsed_type_name;
        datum ok_gt : state = parse_expect(TOK_GT, "Expected '>' after sequence element type");
        parsed_type_tag = TYPE_SEQUENCE;
        parsed_type_name = "sequence<" + elem_name + ">";
        result true;
    conclude

    // Struct type (identifier)
    verify (cur == TOK_IDENT) then
        parsed_type_tag = TYPE_STRUCT;
        parsed_type_name = parse_peek_val();
        parse_advance();
        result true;
    conclude

    datum l : whole = parse_peek_line();
    datum c : whole = parse_peek_col();
    error_report("Expected type specifier", l, c);
    parsed_type_tag = TYPE_UNKNOWN;
    parsed_type_name = "unknown";
    result false;
end
