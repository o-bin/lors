// ==========================================
// Lors Compiler v6 - Runtime Helper Functions (String & I/O)
// ==========================================

algorithm cg_emit_runtime_helpers() -> void
begin
    cg_emit_line("; --- Helper: __lors_to_string_i64 ---");
    cg_emit_line("define linkonce_odr ptr @__lors_to_string_i64(i64 %n) {");
    cg_emit_line("  %buf = call ptr @malloc(i64 32)");
    cg_emit_line("  call i32 (ptr, i64, ptr, ...) @snprintf(ptr %buf, i64 32, ptr @.fmt_i64_raw, i64 %n)");
    cg_emit_line("  ret ptr %buf");
    cg_emit_line("}");
    cg_emit_line("");

    cg_emit_line("; --- Helper: __lors_to_string_f64 ---");
    cg_emit_line("define linkonce_odr ptr @__lors_to_string_f64(double %d) {");
    cg_emit_line("  %buf = call ptr @malloc(i64 32)");
    cg_emit_line("  call i32 (ptr, i64, ptr, ...) @snprintf(ptr %buf, i64 32, ptr @.fmt_f64_raw, double %d)");
    cg_emit_line("  ret ptr %buf");
    cg_emit_line("}");
    cg_emit_line("");

    cg_emit_line("; --- Helper: __lors_str_concat ---");
    cg_emit_line("define linkonce_odr ptr @__lors_str_concat(ptr %s1, ptr %s2) {");
    cg_emit_line("  %l1 = call i64 @strlen(ptr %s1)");
    cg_emit_line("  %l2 = call i64 @strlen(ptr %s2)");
    cg_emit_line("  %sum = add i64 %l1, %l2");
    cg_emit_line("  %total = add i64 %sum, 1");
    cg_emit_line("  %buf = call ptr @malloc(i64 %total)");
    cg_emit_line("  call ptr @strcpy(ptr %buf, ptr %s1)");
    cg_emit_line("  call ptr @strcat(ptr %buf, ptr %s2)");
    cg_emit_line("  ret ptr %buf");
    cg_emit_line("}");
    cg_emit_line("");

    cg_emit_line("; --- Helper: __lors_substring ---");
    cg_emit_line("define linkonce_odr ptr @__lors_substring(ptr %s, i64 %start, i64 %len) {");
    cg_emit_line("  %total = add i64 %len, 1");
    cg_emit_line("  %buf = call ptr @malloc(i64 %total)");
    cg_emit_line("  %src_ptr = getelementptr i8, ptr %s, i64 %start");
    cg_emit_line("  %i_ptr = alloca i64");
    cg_emit_line("  store i64 0, ptr %i_ptr");
    cg_emit_line("  br label %sub_loop");
    cg_emit_line("sub_loop:");
    cg_emit_line("  %i = load i64, ptr %i_ptr");
    cg_emit_line("  %cmp = icmp slt i64 %i, %len");
    cg_emit_line("  br i1 %cmp, label %sub_body, label %sub_end");
    cg_emit_line("sub_body:");
    cg_emit_line("  %s_elem = getelementptr i8, ptr %src_ptr, i64 %i");
    cg_emit_line("  %ch = load i8, ptr %s_elem");
    cg_emit_line("  %d_elem = getelementptr i8, ptr %buf, i64 %i");
    cg_emit_line("  store i8 %ch, ptr %d_elem");
    cg_emit_line("  %next_i = add i64 %i, 1");
    cg_emit_line("  store i64 %next_i, ptr %i_ptr");
    cg_emit_line("  br label %sub_loop");
    cg_emit_line("sub_end:");
    cg_emit_line("  %null_ptr = getelementptr i8, ptr %buf, i64 %len");
    cg_emit_line("  store i8 0, ptr %null_ptr");
    cg_emit_line("  ret ptr %buf");
    cg_emit_line("}");
    cg_emit_line("");

    cg_emit_line("; --- Helper: __lors_inquire ---");
    cg_emit_line("define linkonce_odr ptr @__lors_inquire() {");
    cg_emit_line("  %buf = call ptr @malloc(i64 1024)");
    cg_emit_line("  %in = load ptr, ptr @stdin");
    cg_emit_line("  %res = call ptr @fgets(ptr %buf, i32 1024, ptr %in)");
    cg_emit_line("  %len = call i64 @strlen(ptr %buf)");
    cg_emit_line("  %has_chars = icmp sgt i64 %len, 0");
    cg_emit_line("  br i1 %has_chars, label %chk_nl, label %inq_ret");
    cg_emit_line("chk_nl:");
    cg_emit_line("  %last_idx = sub i64 %len, 1");
    cg_emit_line("  %last_ptr = getelementptr i8, ptr %buf, i64 %last_idx");
    cg_emit_line("  %last_ch = load i8, ptr %last_ptr");
    cg_emit_line("  %is_nl = icmp eq i8 %last_ch, 10");
    cg_emit_line("  br i1 %is_nl, label %strip_nl, label %inq_ret");
    cg_emit_line("strip_nl:");
    cg_emit_line("  store i8 0, ptr %last_ptr");
    cg_emit_line("  br label %inq_ret");
    cg_emit_line("inq_ret:");
    cg_emit_line("  ret ptr %buf");
    cg_emit_line("}");
    cg_emit_line("");
end
