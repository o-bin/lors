// ==========================================
// Lors Compiler v6 - Builtin Function Codegen
// ==========================================

algorithm cg_expr_builtin_math(fname : series, arg0 : series, arg1 : series) -> series
begin
    datum t : series = cg_new_temp();
    verify (fname == "sine") then cg_emit_indent_line(t + " = call double @sin(double " + arg0 + ")"); result t; conclude
    verify (fname == "cosine") then cg_emit_indent_line(t + " = call double @cos(double " + arg0 + ")"); result t; conclude
    verify (fname == "tan") then cg_emit_indent_line(t + " = call double @tan(double " + arg0 + ")"); result t; conclude
    verify (fname == "root") then cg_emit_indent_line(t + " = call double @sqrt(double " + arg0 + ")"); result t; conclude
    verify (fname == "power") then cg_emit_indent_line(t + " = call double @pow(double " + arg0 + ", double " + arg1 + ")"); result t; conclude
    verify (fname == "math_pi") then result "0x400921fb54442d18"; conclude // 3.141592653589793
    verify (fname == "abs_val" or fname == "abs" or fname == "absolute") then
        cg_emit_indent_line(t + " = call double @fabs(double " + arg0 + ")");
        result t;
    conclude
    result "0";
end

algorithm cg_expr_builtin_char_checks(fname : series, arg0 : series) -> series
begin
    datum t : series = cg_new_temp();
    datum t1 : series = "";
    datum t2 : series = "";

    verify (fname == "is_upper") then
        t1 = cg_new_temp();
        t2 = cg_new_temp();
        cg_emit_indent_line(t1 + " = icmp sge i64 " + arg0 + ", 65");
        cg_emit_indent_line(t2 + " = icmp sle i64 " + arg0 + ", 90");
        cg_emit_indent_line(t + " = and i1 " + t1 + ", " + t2);
        result t;
    conclude
    verify (fname == "is_lower") then
        t1 = cg_new_temp();
        t2 = cg_new_temp();
        cg_emit_indent_line(t1 + " = icmp sge i64 " + arg0 + ", 97");
        cg_emit_indent_line(t2 + " = icmp sle i64 " + arg0 + ", 122");
        cg_emit_indent_line(t + " = and i1 " + t1 + ", " + t2);
        result t;
    conclude
    verify (fname == "is_digit") then
        t1 = cg_new_temp();
        t2 = cg_new_temp();
        cg_emit_indent_line(t1 + " = icmp sge i64 " + arg0 + ", 48");
        cg_emit_indent_line(t2 + " = icmp sle i64 " + arg0 + ", 57");
        cg_emit_indent_line(t + " = and i1 " + t1 + ", " + t2);
        result t;
    conclude
    verify (fname == "is_alnum") then
        datum t_u : series = cg_expr_builtin_char_checks("is_upper", arg0);
        datum t_l : series = cg_expr_builtin_char_checks("is_lower", arg0);
        datum t_d : series = cg_expr_builtin_char_checks("is_digit", arg0);
        datum t_ul : series = cg_new_temp();
        cg_emit_indent_line(t_ul + " = or i1 " + t_u + ", " + t_l);
        cg_emit_indent_line(t + " = or i1 " + t_ul + ", " + t_d);
        result t;
    conclude
    result "0";
end

algorithm cg_expr_builtin_os(fname : series, arg0 : series, arg1 : series) -> series
begin
    datum t : series = cg_new_temp();
    verify (fname == "execute_system") then
        datum t_ret : series = cg_new_temp();
        cg_emit_indent_line(t_ret + " = call i32 @system(ptr " + arg0 + ")");
        cg_emit_indent_line(t + " = sext i32 " + t_ret + " to i64");
        result t;
    conclude
    verify (fname == "env_get") then
        datum t_env : series = cg_new_temp();
        cg_emit_indent_line(t_env + " = call ptr @getenv(ptr " + arg0 + ")");
        datum t_null : series = cg_new_temp();
        cg_emit_indent_line(t_null + " = icmp eq ptr " + t_env + ", null");
        cg_emit_indent_line(t + " = select i1 " + t_null + ", ptr @.str_empty, ptr " + t_env);
        result t;
    conclude
    verify (fname == "arg_count") then
        datum t_c : series = cg_new_temp();
        cg_emit_indent_line(t_c + " = load i32, ptr @__argc");
        cg_emit_indent_line(t + " = sext i32 " + t_c + " to i64");
        result t;
    conclude
    verify (fname == "arg_value") then
        datum t_argv : series = cg_new_temp();
        datum t_slot : series = cg_new_temp();
        cg_emit_indent_line(t_argv + " = load ptr, ptr @__argv");
        cg_emit_indent_line(t_slot + " = getelementptr ptr, ptr " + t_argv + ", i64 " + arg0);
        cg_emit_indent_line(t + " = load ptr, ptr " + t_slot);
        result t;
    conclude
    verify (fname == "exit_program") then
        datum t_trunc : series = cg_new_temp();
        cg_emit_indent_line(t_trunc + " = trunc i64 " + arg0 + " to i32");
        cg_emit_indent_line("call void @exit(i32 " + t_trunc + ")");
        result "0";
    conclude
    result "0";
end
