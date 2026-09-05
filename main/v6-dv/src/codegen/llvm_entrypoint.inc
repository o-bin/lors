// ==========================================
// Lors Compiler v6 - Main Entrypoint Wrapper
// ==========================================

algorithm cg_emit_main_entrypoint(has_genesis : state) -> void
begin
    verify (has_genesis == false) then
        result;
    conclude

    cg_emit_line("; --- Entrypoint main (invokes Lors genesis) ---");
    cg_emit_line("define i32 @main(i32 %argc, ptr %argv) {");
    cg_emit_line("entry:");
    cg_emit_line("  store i32 %argc, ptr @__argc");
    cg_emit_line("  store ptr %argv, ptr @__argv");
    cg_emit_line("  %ret = call i64 @genesis()");
    cg_emit_line("  %exit_code = trunc i64 %ret to i32");
    cg_emit_line("  ret i32 %exit_code");
    cg_emit_line("}");
    cg_emit_line("");
end
