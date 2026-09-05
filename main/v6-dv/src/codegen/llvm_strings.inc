// ==========================================
// Lors Compiler v6 - String Pool & Constant Emitting
// Layer: Code Generation
// ==========================================

datum cg_str_texts_data : series;
datum cg_str_labels_data : series;
datum cg_str_byte_lens_data : series;
datum cg_str_count : whole = 0;

algorithm cg_str_pool_init() -> void
begin
    cg_str_texts_data = "";
    cg_str_labels_data = "";
    cg_str_byte_lens_data = "";
    cg_str_count = 0;
end

algorithm cg_escape_llvm_string(s : series) -> series
begin
    datum slen : whole = length(s);
    datum res : series = "";
    datum i : whole = 0;
    cycle (i < slen) do
        datum c : whole = char_at(s, i);
        verify (c == 92) then // '\'
            res = res + "\\5C";
        otherwise
            verify (c == 34) then // '"'
                res = res + "\\22";
            otherwise
                verify (c == 10) then // '\n'
                    res = res + "\\0A";
                otherwise
                    verify (c == 9) then // '\t'
                        res = res + "\\09";
                    otherwise
                        verify (c == 13) then // '\r'
                            res = res + "\\0D";
                        otherwise
                            res = res + substring(s, i, 1);
                        conclude
                    conclude
                conclude
            conclude
        conclude
        i = i + 1;
    conclude
    res = res + "\\00";
    result res;
end

algorithm cg_intern_string(raw_str : series) -> series
begin
    datum i : whole = 0;
    cycle (i < cg_str_count) do
        datum t : series = str_list_get(cg_str_texts_data, i);
        verify (t == raw_str) then
            result str_list_get(cg_str_labels_data, i);
        conclude
        i = i + 1;
    conclude

    datum label : series = "@.str." + to_string(cg_str_count);
    datum byte_len : whole = length(raw_str) + 1;

    cg_str_texts_data = str_list_add(cg_str_texts_data, raw_str);
    cg_str_labels_data = str_list_add(cg_str_labels_data, label);
    cg_str_byte_lens_data = int_list_add(cg_str_byte_lens_data, byte_len);
    cg_str_count = cg_str_count + 1;
    result label;
end

algorithm cg_emit_string_pool() -> void
begin
    datum i : whole = 0;
    cycle (i < cg_str_count) do
        datum lbl : series = str_list_get(cg_str_labels_data, i);
        datum txt : series = str_list_get(cg_str_texts_data, i);
        datum blen : whole = int_list_get(cg_str_byte_lens_data, i);
        datum esc : series = cg_escape_llvm_string(txt);
        cg_emit_line(lbl + " = private unnamed_addr constant [" + to_string(blen) + " x i8] c\"" + esc + "\", align 1");
        i = i + 1;
    conclude
    cg_emit_line("");
end
