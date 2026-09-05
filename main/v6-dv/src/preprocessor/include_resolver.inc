// ==========================================
// Lors Compiler v6 - Include Resolver
// Layer: Preprocessor
// ==========================================

datum inc_visited_str : series;

algorithm inc_init() -> void
begin
    inc_visited_str = ";";
end

algorithm inc_is_visited(filepath : series) -> state
begin
    datum target : series = ";" + filepath + ";";
    result str_contains(inc_visited_str, target);
end

algorithm inc_extract_target(line : series) -> series
begin
    datum llen : whole = length(line);
    datum i : whole = 0;
    // Skip whitespace
    cycle (i < llen) do
        datum c : whole = char_at(line, i);
        verify (c == 32 or c == 9) then
            i = i + 1;
        otherwise
            datum remaining : series = substring(line, i, llen - i);
            verify (str_starts_with(remaining, "incorporate")) then
                datum q1 : whole = -1;
                datum q2 : whole = -1;
                datum j : whole = i + 11;
                cycle (j < llen) do
                    datum cj : whole = char_at(line, j);
                    verify (cj == 34) then // '"'
                        verify (q1 == -1) then
                            q1 = j;
                        otherwise
                            q2 = j;
                            j = llen;
                        conclude
                    conclude
                    j = j + 1;
                conclude
                verify (q1 != -1 and q2 != -1 and q2 > q1 + 1) then
                    datum target : series = substring(line, q1 + 1, q2 - (q1 + 1));
                    result target;
                conclude
            conclude
            result "";
        conclude
    conclude
    result "";
end

algorithm preprocess_file(filepath : series) -> series
begin
    verify (inc_is_visited(filepath)) then
        result "";
    conclude
    inc_visited_str = inc_visited_str + filepath + ";";

    datum raw_code : series = read_source_file(filepath);
    datum dir : series = path_dirname(filepath);
    datum clen : whole = length(raw_code);

    datum output_code : series = "";
    datum line_start : whole = 0;
    datum i : whole = 0;

    cycle (i < clen) do
        datum c : whole = char_at(raw_code, i);
        verify (c == 10) then // '\n'
            datum current_line : series = substring(raw_code, line_start, i - line_start);
            datum inc_target : series = inc_extract_target(current_line);
            verify (length(inc_target) > 0) then
                datum target_path : series = path_join(dir, inc_target);
                datum inc_code : series = preprocess_file(target_path);
                output_code = output_code + inc_code + "\n";
            otherwise
                output_code = output_code + current_line + "\n";
            conclude
            line_start = i + 1;
        conclude
        i = i + 1;
    conclude

    verify (line_start < clen) then
        datum tail_line : series = substring(raw_code, line_start, clen - line_start);
        datum inc_target2 : series = inc_extract_target(tail_line);
        verify (length(inc_target2) > 0) then
            datum target_path2 : series = path_join(dir, inc_target2);
            datum inc_code2 : series = preprocess_file(target_path2);
            output_code = output_code + inc_code2 + "\n";
        otherwise
            output_code = output_code + tail_line + "\n";
        conclude
    conclude

    result output_code;
end
