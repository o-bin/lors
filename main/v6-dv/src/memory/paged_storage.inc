// ==========================================
// Lors Compiler v6 - Paged Memory Storage
// Layer: Memory Management (Paged Virtual Arrays)
// Page size: 64 elements per block
// ==========================================

algorithm page_init_int_chunk() -> series
begin
    datum res : series = "";
    datum i : whole = 0;
    cycle (i < 64) do
        res = int_list_add(res, 0);
        i = i + 1;
    conclude
    result res;
end

algorithm page_init_str_chunk() -> series
begin
    datum res : series = "";
    datum i : whole = 0;
    cycle (i < 64) do
        res = str_list_add(res, "");
        i = i + 1;
    conclude
    result res;
end

algorithm page_int_get(master_pages : series, target_idx : whole) -> whole
begin
    datum p_idx : whole = target_idx / 64;
    datum s_idx : whole = target_idx % 64;
    datum chunk : series = str_list_get(master_pages, p_idx);
    verify (length(chunk) == 0) then result 0; conclude
    result int_list_get(chunk, s_idx);
end

algorithm page_int_set(master_pages : series, target_idx : whole, val : whole, total_items : whole) -> series
begin
    datum p_idx : whole = target_idx / 64;
    datum s_idx : whole = target_idx % 64;

    datum chunk : series = str_list_get(master_pages, p_idx);
    datum updated_master : series = master_pages;
    verify (length(chunk) == 0) then
        chunk = page_init_int_chunk();
        updated_master = str_list_add(master_pages, chunk);
    conclude

    datum new_chunk : series = int_list_set(chunk, s_idx, val);
    result str_list_set(updated_master, p_idx, new_chunk);
end

algorithm page_str_get(master_pages : series, target_idx : whole) -> series
begin
    datum p_idx : whole = target_idx / 64;
    datum s_idx : whole = target_idx % 64;
    datum chunk : series = str_list_get(master_pages, p_idx);
    verify (length(chunk) == 0) then result ""; conclude
    result str_list_get(chunk, s_idx);
end

algorithm page_str_set(master_pages : series, target_idx : whole, val : series) -> series
begin
    datum p_idx : whole = target_idx / 64;
    datum s_idx : whole = target_idx % 64;

    datum chunk : series = str_list_get(master_pages, p_idx);
    datum updated_master : series = master_pages;
    verify (length(chunk) == 0) then
        chunk = page_init_str_chunk();
        updated_master = str_list_add(master_pages, chunk);
    conclude

    datum new_chunk : series = str_list_set(chunk, s_idx, val);
    result str_list_set(updated_master, p_idx, new_chunk);
end
