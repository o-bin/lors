// ==========================================
// Lors Compiler v6 - String Utilities
// ==========================================

algorithm str_starts_with(s : series, prefix : series) -> state
begin
    datum slen : whole = length(s);
    datum plen : whole = length(prefix);
    verify (plen > slen) then
        result false;
    conclude
    datum sub : series = substring(s, 0, plen);
    verify (sub == prefix) then
        result true;
    conclude
    result false;
end

algorithm str_ends_with(s : series, suffix : series) -> state
begin
    datum slen : whole = length(s);
    datum sfx_len : whole = length(suffix);
    verify (sfx_len > slen) then
        result false;
    conclude
    datum sub : series = substring(s, slen - sfx_len, sfx_len);
    verify (sub == suffix) then
        result true;
    conclude
    result false;
end

algorithm str_contains(s : series, needle : series) -> state
begin
    datum slen : whole = length(s);
    datum nlen : whole = length(needle);
    verify (nlen > slen) then
        result false;
    conclude
    verify (nlen == 0) then
        result true;
    conclude
    datum max_i : whole = slen - nlen;
    datum i : whole = 0;
    cycle (i <= max_i) do
        datum sub : series = substring(s, i, nlen);
        verify (sub == needle) then
            result true;
        conclude
        i = i + 1;
    conclude
    result false;
end

algorithm char_is_digit(c : whole) -> state
begin
    verify (c >= 48 and c <= 57) then
        result true;
    conclude
    result false;
end

algorithm char_is_alpha(c : whole) -> state
begin
    verify (c >= 65 and c <= 90) then
        result true;
    conclude
    verify (c >= 97 and c <= 122) then
        result true;
    conclude
    verify (c == 95) then // '_'
        result true;
    conclude
    result false;
end

algorithm char_is_alnum(c : whole) -> state
begin
    datum is_a : state = char_is_alpha(c);
    verify (is_a) then
        result true;
    conclude
    datum is_d : state = char_is_digit(c);
    verify (is_d) then
        result true;
    conclude
    result false;
end

algorithm char_is_whitespace(c : whole) -> state
begin
    verify (c == 32 or c == 9 or c == 10 or c == 13) then
        result true;
    conclude
    result false;
end

algorithm split_lines(content : series) -> sequence<series>
begin
    datum lines : sequence<series> = [];
    datum clen : whole = length(content);
    datum start_idx : whole = 0;
    datum i : whole = 0;
    cycle (i < clen) do
        datum c : whole = char_at(content, i);
        verify (c == 10) then // '\n'
            datum line_str : series = substring(content, start_idx, i - start_idx);
            lines = lines + [line_str];
            start_idx = i + 1;
        conclude
        i = i + 1;
    conclude
    verify (start_idx < clen) then
        datum tail_str : series = substring(content, start_idx, clen - start_idx);
        lines = lines + [tail_str];
    conclude
    result lines;
end
