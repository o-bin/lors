// ==========================================
// Lors Compiler v6 - Parser State & Utilities
// Layer: Parser
// ==========================================

datum parse_pos : whole = 0;

algorithm parser_init() -> void
begin
    parse_pos = 0;
end

algorithm parse_peek_type() -> whole
begin
    result token_get_type(parse_pos);
end

algorithm parse_peek_val() -> series
begin
    result token_get_val(parse_pos);
end

algorithm parse_peek_line() -> whole
begin
    result token_get_line(parse_pos);
end

algorithm parse_peek_col() -> whole
begin
    result token_get_col(parse_pos);
end

algorithm parse_advance() -> void
begin
    verify (parse_pos < tok_count) then
        parse_pos = parse_pos + 1;
    conclude
end

algorithm parse_match(expected_type : whole) -> state
begin
    datum cur : whole = parse_peek_type();
    verify (cur == expected_type) then
        parse_advance();
        result true;
    conclude
    result false;
end

algorithm parse_expect(expected_type : whole, err_msg : series) -> state
begin
    datum cur : whole = parse_peek_type();
    verify (cur == expected_type) then
        parse_advance();
        result true;
    conclude
    datum l : whole = parse_peek_line();
    datum c : whole = parse_peek_col();
    error_report(err_msg + " (got: '" + parse_peek_val() + "')", l, c);
    result false;
end
