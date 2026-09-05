// ==========================================
// Lors Compiler v6 - External Runtime Declarations & Formats
// ==========================================

algorithm cg_emit_runtime_declarations() -> void
begin
    cg_emit_line("; --- Global Format Constants ---");
    cg_emit_line("@.fmt_i64 = private unnamed_addr constant [6 x i8] c\"%lld\\0A\\00\", align 1");
    cg_emit_line("@.fmt_f64 = private unnamed_addr constant [4 x i8] c\"%g\\0A\\00\", align 1");
    cg_emit_line("@.fmt_str = private unnamed_addr constant [4 x i8] c\"%s\\0A\\00\", align 1");
    cg_emit_line("@.fmt_true = private unnamed_addr constant [6 x i8] c\"true\\0A\\00\", align 1");
    cg_emit_line("@.fmt_false = private unnamed_addr constant [7 x i8] c\"false\\0A\\00\", align 1");
    cg_emit_line("@.fmt_i64_raw = private unnamed_addr constant [5 x i8] c\"%lld\\00\", align 1");
    cg_emit_line("@.fmt_f64_raw = private unnamed_addr constant [3 x i8] c\"%g\\00\", align 1");
    cg_emit_line("@.str_mode_r = private unnamed_addr constant [2 x i8] c\"r\\00\", align 1");
    cg_emit_line("@.str_mode_w = private unnamed_addr constant [2 x i8] c\"w\\00\", align 1");
    cg_emit_line("@.str_empty = private unnamed_addr constant [1 x i8] c\"\\00\", align 1");
    cg_emit_line("");
    cg_emit_line("; --- CLI State ---");
    cg_emit_line("@__argc = common global i32 0, align 4");
    cg_emit_line("@__argv = common global ptr null, align 8");
    cg_emit_line("@stdin = external global ptr, align 8");
    cg_emit_line("");
    cg_emit_line("; --- Standard C Library Declarations ---");
    cg_emit_line("declare i32 @printf(ptr, ...)");
    cg_emit_line("declare i32 @snprintf(ptr, i64, ptr, ...)");
    cg_emit_line("declare i32 @puts(ptr)");
    cg_emit_line("declare ptr @fgets(ptr, i32, ptr)");
    cg_emit_line("declare ptr @malloc(i64)");
    cg_emit_line("declare ptr @realloc(ptr, i64)");
    cg_emit_line("declare void @free(ptr)");
    cg_emit_line("declare i64 @strlen(ptr)");
    cg_emit_line("declare i32 @strcmp(ptr, ptr)");
    cg_emit_line("declare ptr @strcpy(ptr, ptr)");
    cg_emit_line("declare ptr @strcat(ptr, ptr)");
    cg_emit_line("declare ptr @strdup(ptr)");
    cg_emit_line("declare double @atof(ptr)");
    cg_emit_line("declare i64 @atoll(ptr)");
    cg_emit_line("declare double @sin(double)");
    cg_emit_line("declare double @cos(double)");
    cg_emit_line("declare double @tan(double)");
    cg_emit_line("declare double @sqrt(double)");
    cg_emit_line("declare double @pow(double, double)");
    cg_emit_line("declare double @fabs(double)");
    cg_emit_line("declare i32 @system(ptr)");
    cg_emit_line("declare ptr @getenv(ptr)");
    cg_emit_line("declare void @exit(i32)");
    cg_emit_line("declare ptr @fopen(ptr, ptr)");
    cg_emit_line("declare i64 @fread(ptr, i64, i64, ptr)");
    cg_emit_line("declare i64 @fwrite(ptr, i64, i64, ptr)");
    cg_emit_line("declare i32 @fseek(ptr, i64, i32)");
    cg_emit_line("declare i64 @ftell(ptr)");
    cg_emit_line("declare i32 @fclose(ptr)");
    cg_emit_line("declare i32 @remove(ptr)");
    cg_emit_line("declare i32 @access(ptr, i32)");
    cg_emit_line("");
end
