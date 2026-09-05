// ==========================================
// Lors Compiler v6 - LLVM IR Emitter
// ==========================================

datum cg_code : series;

algorithm cg_init() -> void
begin
    cg_code = "";
end

algorithm cg_emit(text : series) -> void
begin
    cg_code = cg_code + text;
end

algorithm cg_emit_line(line : series) -> void
begin
    cg_code = cg_code + line + "\n";
end

algorithm cg_emit_indent_line(line : series) -> void
begin
    cg_code = cg_code + "  " + line + "\n";
end

algorithm cg_get_code() -> series
begin
    result cg_code;
end
