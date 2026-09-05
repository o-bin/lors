// ==========================================
// Lors Compiler v6 - Symbol Table Management
// Layer: Semantic Analysis
// ==========================================

algorithm sym_init() -> void
begin
    sym_names_data = "";
    sym_type_tags_data = "";
    sym_type_names_data = "";
    sym_scopes_data = "";
    sym_count = 0;
    sym_current_scope = 0;

    fn_names_data = "";
    fn_ret_tags_data = "";
    fn_ret_names_data = "";
    fn_param_counts_data = "";
    fn_count = 0;
end

algorithm sym_enter_scope() -> void
begin
    sym_current_scope = sym_current_scope + 1;
end

algorithm sym_exit_scope() -> void
begin
    datum i : whole = sym_count - 1;
    cycle (i >= 0) do
        datum sc : whole = int_list_get(sym_scopes_data, i);
        verify (sc == sym_current_scope) then
            sym_count = sym_count - 1;
            i = i - 1;
        otherwise
            i = -1;
        conclude
    conclude
    sym_current_scope = sym_current_scope - 1;
end

algorithm sym_add_var(name : series, tag : whole, tname : series) -> void
begin
    sym_names_data = str_list_add(sym_names_data, name);
    sym_type_tags_data = int_list_add(sym_type_tags_data, tag);
    sym_type_names_data = str_list_add(sym_type_names_data, tname);
    sym_scopes_data = int_list_add(sym_scopes_data, sym_current_scope);
    sym_count = sym_count + 1;
end

algorithm sym_lookup_var(name : series) -> whole
begin
    datum i : whole = sym_count - 1;
    cycle (i >= 0) do
        datum n : series = str_list_get(sym_names_data, i);
        verify (n == name) then
            result i;
        conclude
        i = i - 1;
    conclude
    result -1;
end

algorithm sym_get_var_type(name : series) -> whole
begin
    datum idx : whole = sym_lookup_var(name);
    verify (idx != -1) then
        result int_list_get(sym_type_tags_data, idx);
    conclude
    result TYPE_UNKNOWN;
end

algorithm sym_get_var_type_name(name : series) -> series
begin
    datum idx : whole = sym_lookup_var(name);
    verify (idx != -1) then
        result str_list_get(sym_type_names_data, idx);
    conclude
    result "";
end

algorithm fn_register(name : series, ret_tag : whole, ret_name : series, pcount : whole) -> void
begin
    fn_names_data = str_list_add(fn_names_data, name);
    fn_ret_tags_data = int_list_add(fn_ret_tags_data, ret_tag);
    fn_ret_names_data = str_list_add(fn_ret_names_data, ret_name);
    fn_param_counts_data = int_list_add(fn_param_counts_data, pcount);
    fn_count = fn_count + 1;
end

algorithm fn_lookup_ret_tag(name : series) -> whole
begin
    datum i : whole = fn_count - 1;
    cycle (i >= 0) do
        datum n : series = str_list_get(fn_names_data, i);
        verify (n == name) then
            result int_list_get(fn_ret_tags_data, i);
        conclude
        i = i - 1;
    conclude
    result TYPE_UNKNOWN;
end

algorithm fn_lookup_ret_name(name : series) -> series
begin
    datum i : whole = fn_count - 1;
    cycle (i >= 0) do
        datum n : series = str_list_get(fn_names_data, i);
        verify (n == name) then
            result str_list_get(fn_ret_names_data, i);
        conclude
        i = i - 1;
    conclude
    result "";
end
