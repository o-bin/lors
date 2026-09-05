// ==========================================
// Lors Compiler v6 - Structure Registry
// Layer: Semantic Analysis
// ==========================================

datum struct_names_data : series;
datum struct_field_names_data : series;
datum struct_field_tags_data : series;
datum struct_field_tnames_data : series;
datum struct_field_starts_data : series;
datum struct_field_counts_data : series;
datum struct_total_fields : whole = 0;
datum struct_count : whole = 0;

algorithm struct_reg_init() -> void
begin
    struct_names_data = "";
    struct_field_names_data = "";
    struct_field_tags_data = "";
    struct_field_tnames_data = "";
    struct_field_starts_data = "";
    struct_field_counts_data = "";
    struct_total_fields = 0;
    struct_count = 0;
end

algorithm struct_lookup(name : series) -> whole
begin
    datum i : whole = 0;
    cycle (i < struct_count) do
        datum n : series = str_list_get(struct_names_data, i);
        verify (n == name) then
            result i;
        conclude
        i = i + 1;
    conclude
    result -1;
end

algorithm struct_register(name : series) -> void
begin
    verify (struct_lookup(name) != -1) then
        result;
    conclude
    struct_names_data = str_list_add(struct_names_data, name);
    struct_field_starts_data = int_list_add(struct_field_starts_data, struct_total_fields);
    struct_field_counts_data = int_list_add(struct_field_counts_data, 0);
    struct_count = struct_count + 1;
end

algorithm struct_add_field(sname : series, fname : series, tag : whole, tname : series) -> void
begin
    datum s_idx : whole = struct_lookup(sname);
    verify (s_idx == -1) then
        struct_register(sname);
        s_idx = struct_lookup(sname);
    conclude

    struct_field_names_data = str_list_add(struct_field_names_data, fname);
    struct_field_tags_data = int_list_add(struct_field_tags_data, tag);
    struct_field_tnames_data = str_list_add(struct_field_tnames_data, tname);
    struct_total_fields = struct_total_fields + 1;

    datum cur_cnt : whole = int_list_get(struct_field_counts_data, s_idx);
    struct_field_counts_data = int_list_set(struct_field_counts_data, s_idx, cur_cnt + 1);
end

algorithm struct_get_field_index(sname : series, fname : series) -> whole
begin
    datum s_idx : whole = struct_lookup(sname);
    verify (s_idx == -1) then
        result -1;
    conclude
    datum start : whole = int_list_get(struct_field_starts_data, s_idx);
    datum count : whole = int_list_get(struct_field_counts_data, s_idx);
    datum i : whole = 0;
    cycle (i < count) do
        datum fn : series = str_list_get(struct_field_names_data, start + i);
        verify (fn == fname) then
            result i;
        conclude
        i = i + 1;
    conclude
    result -1;
end

algorithm struct_get_field_type(sname : series, fname : series) -> whole
begin
    datum s_idx : whole = struct_lookup(sname);
    verify (s_idx == -1) then result TYPE_UNKNOWN; conclude
    datum f_idx : whole = struct_get_field_index(sname, fname);
    verify (f_idx == -1) then result TYPE_UNKNOWN; conclude
    datum start : whole = int_list_get(struct_field_starts_data, s_idx);
    result int_list_get(struct_field_tags_data, start + f_idx);
end

algorithm struct_get_field_type_name(sname : series, fname : series) -> series
begin
    datum s_idx : whole = struct_lookup(sname);
    verify (s_idx == -1) then result ""; conclude
    datum f_idx : whole = struct_get_field_index(sname, fname);
    verify (f_idx == -1) then result ""; conclude
    datum start : whole = int_list_get(struct_field_starts_data, s_idx);
    result str_list_get(struct_field_tnames_data, start + f_idx);
end
