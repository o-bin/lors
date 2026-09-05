// ==========================================
// Lors Compiler v6 - Contiguous Memory Buffers
// Layer: Memory Management
// ==========================================

algorithm buf_int_create() -> sequence<whole>
begin
    datum empty : sequence<whole> = [];
    result empty;
end

algorithm buf_int_append(buf : sequence<whole>, val : whole) -> sequence<whole>
begin
    result buf + [val];
end

algorithm buf_int_get(buf : sequence<whole>, idx : whole) -> whole
begin
    datum n : whole = length(buf);
    verify (idx >= 0 and idx < n) then
        result buf[idx];
    conclude
    result 0;
end

algorithm buf_int_set(buf : sequence<whole>, idx : whole, val : whole) -> sequence<whole>
begin
    datum n : whole = length(buf);
    verify (idx >= 0 and idx < n) then
        buf[idx] = val;
    conclude
    result buf;
end

algorithm buf_str_create() -> sequence<series>
begin
    datum empty : sequence<series> = [];
    result empty;
end

algorithm buf_str_append(buf : sequence<series>, val : series) -> sequence<series>
begin
    result buf + [val];
end

algorithm buf_str_get(buf : sequence<series>, idx : whole) -> series
begin
    datum n : whole = length(buf);
    verify (idx >= 0 and idx < n) then
        result buf[idx];
    conclude
    result "";
end

algorithm buf_str_set(buf : sequence<series>, idx : whole, val : series) -> sequence<series>
begin
    datum n : whole = length(buf);
    verify (idx >= 0 and idx < n) then
        buf[idx] = val;
    conclude
    result buf;
end
