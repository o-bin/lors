// ==========================================
// Lors Compiler v6 - String-Backed Fast Lists
// ==========================================

algorithm str_to_i64(s : series) -> whole
begin
    datum slen : whole = length(s);
    verify (slen == 0) then result 0; conclude
    datum is_neg : state = false;
    datum start_i : whole = 0;
    datum first_c : whole = char_at(s, 0);
    verify (first_c == 45) then // '-'
        is_neg = true;
        start_i = 1;
    conclude
    datum num : whole = 0;
    datum i : whole = start_i;
    cycle (i < slen) do
        datum c : whole = char_at(s, i);
        verify (c >= 48 and c <= 57) then
            num = num * 10 + (c - 48);
        conclude
        i = i + 1;
    conclude
    verify (is_neg) then result 0 - num; conclude
    result num;
end

algorithm int_list_add(list : series, val : whole) -> series
begin
    result list + to_string(val) + ",";
end

algorithm int_list_get(list : series, target_idx : whole) -> whole
begin
    datum llen : whole = length(list);
    datum cur_idx : whole = 0;
    datum start_pos : whole = 0;
    datum i : whole = 0;
    cycle (i < llen) do
        datum c : whole = char_at(list, i);
        verify (c == 44) then // ','
            verify (cur_idx == target_idx) then
                datum chunk : series = substring(list, start_pos, i - start_pos);
                result str_to_i64(chunk);
            conclude
            cur_idx = cur_idx + 1;
            start_pos = i + 1;
        conclude
        i = i + 1;
    conclude
    result 0;
end

algorithm str_list_add(list : series, val : series) -> series
begin
    datum vlen : whole = length(val);
    result list + to_string(vlen) + ":" + val + ";";
end

algorithm str_list_get(list : series, target_idx : whole) -> series
begin
    datum llen : whole = length(list);
    datum cur_idx : whole = 0;
    datum i : whole = 0;
    cycle (i < llen) do
        datum colon_pos : whole = -1;
        datum j : whole = i;
        cycle (j < llen and colon_pos == -1) do
            verify (char_at(list, j) == 58) then // ':'
                colon_pos = j;
            conclude
            j = j + 1;
        conclude
        verify (colon_pos == -1) then result ""; conclude

        datum len_str : series = substring(list, i, colon_pos - i);
        datum vlen : whole = str_to_i64(len_str);
        datum val_start : whole = colon_pos + 1;

        verify (cur_idx == target_idx) then
            datum val : series = substring(list, val_start, vlen);
            result val;
        conclude

        cur_idx = cur_idx + 1;
        i = val_start + vlen + 1; // +1 for ';'
    conclude
    result "";
end

algorithm int_list_set(list : series, target_idx : whole, val : whole) -> series
begin
    datum llen : whole = length(list);
    datum cur_idx : whole = 0;
    datum start_pos : whole = 0;
    datum i : whole = 0;
    cycle (i < llen) do
        datum c : whole = char_at(list, i);
        verify (c == 44) then // ','
            verify (cur_idx == target_idx) then
                datum before : series = substring(list, 0, start_pos);
                datum after : series = substring(list, i + 1, llen - (i + 1));
                result before + to_string(val) + "," + after;
            conclude
            cur_idx = cur_idx + 1;
            start_pos = i + 1;
        conclude
        i = i + 1;
    conclude
    result list;
end

algorithm str_list_set(list : series, target_idx : whole, val : series) -> series
begin
    datum llen : whole = length(list);
    datum cur_idx : whole = 0;
    datum i : whole = 0;
    cycle (i < llen) do
        datum colon_pos : whole = -1;
        datum j : whole = i;
        cycle (j < llen and colon_pos == -1) do
            verify (char_at(list, j) == 58) then // ':'
                colon_pos = j;
            conclude
            j = j + 1;
        conclude
        verify (colon_pos == -1) then result list; conclude

        datum len_str : series = substring(list, i, colon_pos - i);
        datum vlen : whole = str_to_i64(len_str);
        datum val_end : whole = colon_pos + 1 + vlen + 1; // +1 for ';'

        verify (cur_idx == target_idx) then
            datum before : series = substring(list, 0, i);
            datum after : series = substring(list, val_end, llen - val_end);
            datum new_item : series = to_string(length(val)) + ":" + val + ";";
            result before + new_item + after;
        conclude

        cur_idx = cur_idx + 1;
        i = val_end;
    conclude
    result list;
end
