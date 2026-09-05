// ==========================================
// Lors Compiler v6 - String Interning Arena
// Layer: Memory Management (FNV-1a String Pool)
// ==========================================

datum intern_pool_data : series;
datum intern_hashes_data : series;
datum intern_total_strings : whole = 0;

algorithm fnv1a_hash(s : series) -> whole
begin
    datum slen : whole = length(s);
    datum h : whole = 1469598103;
    datum i : whole = 0;
    cycle (i < slen) do
        datum b : whole = char_at(s, i);
        h = (h * 1099511) + b;
        verify (h < 0) then
            h = 0 - h;
        conclude
        i = i + 1;
    conclude
    result h;
end

algorithm interner_init() -> void
begin
    intern_pool_data = "";
    intern_hashes_data = "";
    intern_total_strings = 0;
end

algorithm intern_lookup(s : series) -> whole
begin
    datum target_hash : whole = fnv1a_hash(s);
    datum i : whole = 0;
    cycle (i < intern_total_strings) do
        datum h : whole = int_list_get(intern_hashes_data, i);
        verify (h == target_hash) then
            datum pool_str : series = str_list_get(intern_pool_data, i);
            verify (pool_str == s) then
                result i;
            conclude
        conclude
        i = i + 1;
    conclude
    result -1;
end

algorithm intern_string(s : series) -> whole
begin
    datum existing_id : whole = intern_lookup(s);
    verify (existing_id != -1) then
        result existing_id;
    conclude

    datum new_id : whole = intern_total_strings;
    datum h : whole = fnv1a_hash(s);

    intern_pool_data = str_list_add(intern_pool_data, s);
    intern_hashes_data = int_list_add(intern_hashes_data, h);
    intern_total_strings = intern_total_strings + 1;

    result new_id;
end

algorithm get_interned_string(id : whole) -> series
begin
    verify (id >= 0 and id < intern_total_strings) then
        result str_list_get(intern_pool_data, id);
    conclude
    result "";
end

algorithm intern_count() -> whole
begin
    result intern_total_strings;
end
