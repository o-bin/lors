// ==========================================
// Lors Compiler v6 - Native Arena Allocator
// Layer: Memory Management
// ==========================================

datum arena_capacity : whole = 0;
datum arena_offset : whole = 0;
datum arena_total_allocations : whole = 0;

algorithm arena_align8(offset : whole) -> whole
begin
    datum remainder : whole = (offset + 7) % 8;
    result (offset + 7) - remainder;
end

algorithm arena_init(initial_cap : whole) -> void
begin
    verify (initial_cap <= 0) then
        arena_capacity = 16777216; // 16 MB default initial capacity (2^24 bytes)
    otherwise
        arena_capacity = initial_cap;
    conclude
    arena_offset = 0;
    arena_total_allocations = 0;
end

algorithm arena_alloc(size_bytes : whole) -> whole
begin
    verify (size_bytes <= 0) then
        result arena_offset;
    conclude

    datum aligned_start : whole = arena_align8(arena_offset);
    datum next_offset : whole = aligned_start + size_bytes;

    verify (next_offset > arena_capacity) then
        // Geometric capacity expansion by factor of 2
        datum doubled : whole = arena_capacity * 2;
        verify (doubled > next_offset) then
            arena_capacity = doubled;
        otherwise
            arena_capacity = next_offset * 2;
        conclude
    conclude

    arena_offset = next_offset;
    arena_total_allocations = arena_total_allocations + 1;
    result aligned_start;
end

algorithm arena_reset() -> void
begin
    arena_offset = 0;
    arena_total_allocations = 0;
end

algorithm arena_get_used() -> whole
begin
    result arena_offset;
end

algorithm arena_get_capacity() -> whole
begin
    result arena_capacity;
end
