// ==========================================
// Lors Compiler v6 - Function & Builtin Calls
// Layer: Code Generation
// ==========================================

algorithm cg_expr_call(node_id : whole) -> series
begin
    // 1. Struct Constructor
    verify (ast_get_n_val(node_id) == 1) then
        result cg_expr_struct_constructor(node_id);
    conclude

    datum fname : series = ast_get_s_val(node_id);
    datum cnt : whole = ast_get_child_count(node_id);

    datum a0 : series = "";
    datum a1 : series = "";
    datum a2 : series = "";
    verify (cnt > 0) then a0 = cg_generate_expression(ast_get_child(node_id, 0)); conclude
    verify (cnt > 1) then a1 = cg_generate_expression(ast_get_child(node_id, 1)); conclude
    verify (cnt > 2) then a2 = cg_generate_expression(ast_get_child(node_id, 2)); conclude

    datum t : series = cg_new_temp();

    // 2. String & I/O Builtins
    verify (fname == "length") then
        datum len_c0 : whole = ast_get_child(node_id, 0);
        datum len_tag : whole = cg_get_node_type_tag(len_c0);
        verify (len_tag == TYPE_SEQUENCE or str_starts_with(cg_get_var_struct_name(ast_get_s_val(len_c0)), "sequence<")) then
            cg_emit_indent_line(t + " = call i64 @__lors_seq_len(ptr " + a0 + ")");
        otherwise
            cg_emit_indent_line(t + " = call i64 @strlen(ptr " + a0 + ")");
        conclude
        result t;
    conclude
    verify (fname == "substring") then
        cg_emit_indent_line(t + " = call ptr @__lors_substring(ptr " + a0 + ", i64 " + a1 + ", i64 " + a2 + ")");
        result t;
    conclude
    verify (fname == "to_string") then
        datum str_c0 : whole = ast_get_child(node_id, 0);
        datum str_tag : whole = cg_get_node_type_tag(str_c0);
        verify (str_tag == TYPE_PRECISE) then
            cg_emit_indent_line(t + " = call ptr @__lors_to_string_f64(double " + a0 + ")");
        otherwise
            cg_emit_indent_line(t + " = call ptr @__lors_to_string_i64(i64 " + a0 + ")");
        conclude
        result t;
    conclude
    verify (fname == "to_precise") then cg_emit_indent_line(t + " = call double @atof(ptr " + a0 + ")"); result t; conclude
    verify (fname == "to_integer") then cg_emit_indent_line(t + " = call i64 @atoll(ptr " + a0 + ")"); result t; conclude
    verify (fname == "to_upper") then cg_emit_indent_line(t + " = call ptr @__lors_to_upper(ptr " + a0 + ")"); result t; conclude
    verify (fname == "to_lower") then cg_emit_indent_line(t + " = call ptr @__lors_to_lower(ptr " + a0 + ")"); result t; conclude
    verify (fname == "reverse") then cg_emit_indent_line(t + " = call ptr @__lors_reverse(ptr " + a0 + ")"); result t; conclude
    verify (fname == "inquire") then cg_emit_indent_line(t + " = call ptr @__lors_inquire()"); result t; conclude
    verify (fname == "split_lines") then cg_emit_indent_line(t + " = call ptr @__lors_split_lines(ptr " + a0 + ")"); result t; conclude

    verify (fname == "char_at") then
        datum t_gep : series = cg_new_temp();
        datum t_byte : series = cg_new_temp();
        cg_emit_indent_line(t_gep + " = getelementptr i8, ptr " + a0 + ", i64 " + a1);
        cg_emit_indent_line(t_byte + " = load i8, ptr " + t_gep);
        cg_emit_indent_line(t + " = zext i8 " + t_byte + " to i64");
        result t;
    conclude

    // 3. File System Builtins
    verify (fname == "file_read") then cg_emit_indent_line(t + " = call ptr @__lors_file_read(ptr " + a0 + ")"); result t; conclude
    verify (fname == "file_write") then cg_emit_indent_line("call void @__lors_file_write(ptr " + a0 + ", ptr " + a1 + ")"); result "0"; conclude
    verify (fname == "file_remove") then cg_emit_indent_line("call i32 @remove(ptr " + a0 + ")"); result "0"; conclude
    verify (fname == "file_exists") then
        datum t_acc : series = cg_new_temp();
        cg_emit_indent_line(t_acc + " = call i32 @access(ptr " + a0 + ", i32 0)");
        cg_emit_indent_line(t + " = icmp eq i32 " + t_acc + ", 0");
        result t;
    conclude

    // 4. Math, Char, OS Builtins
    verify (fname == "sine" or fname == "cosine" or fname == "tan" or fname == "root" or fname == "power" or fname == "math_pi" or fname == "abs_val" or fname == "abs" or fname == "absolute") then
        result cg_expr_builtin_math(fname, a0, a1);
    conclude
    verify (fname == "is_upper" or fname == "is_lower" or fname == "is_digit" or fname == "is_alnum") then
        result cg_expr_builtin_char_checks(fname, a0);
    conclude
    verify (fname == "execute_system" or fname == "env_get" or fname == "arg_count" or fname == "arg_value" or fname == "exit_program") then
        result cg_expr_builtin_os(fname, a0, a1);
    conclude

    // 5. User Function Call & External Auto-Declaration
    datum ret_tag : whole = ast_get_type_tag(node_id);
    datum ret_tname : series = ast_get_type_name(node_id);
    datum ret_ltype : series = llvm_get_type(ret_tag, ret_tname);

    datum args_str : series = "";
    datum types_only : series = "";
    datum k : whole = 0;
    cycle (k < cnt) do
        datum ch : whole = ast_get_child(node_id, k);
        datum ch_tag : whole = ast_get_type_tag(ch);
        datum ch_tname : series = ast_get_type_name(ch);
        datum ch_ltype : series = llvm_get_type(ch_tag, ch_tname);
        verify (ast_get_kind(ch) == AST_IDENT) then
            ch_ltype = cg_get_var_type(ast_get_s_val(ch));
        conclude
        datum ch_val : series = "";
        verify (k == 0) then ch_val = a0; conclude
        verify (k == 1) then ch_val = a1; conclude
        verify (k == 2) then ch_val = a2; conclude
        verify (k > 2) then ch_val = cg_generate_expression(ch); conclude

        verify (k > 0) then
            args_str = args_str + ", ";
            types_only = types_only + ", ";
        conclude
        args_str = args_str + ch_ltype + " " + ch_val;
        types_only = types_only + ch_ltype;
        k = k + 1;
    conclude

    verify (str_contains(cg_defined_functions, ";" + fname + ";") == false and str_contains(cg_declared_functions, ";" + fname + ";") == false) then
        verify (str_contains(cg_external_decls, "@" + fname + "(") == false) then
            datum decl_str : series = "declare " + ret_ltype + " @" + fname + "(" + types_only + ")";
            cg_external_decls = cg_external_decls + decl_str + "\n";
            cg_declared_functions = cg_declared_functions + fname + ";";
        conclude
    conclude

    verify (ret_ltype == "void") then
        cg_emit_indent_line("call void @" + fname + "(" + args_str + ")");
        result "0";
    otherwise
        cg_emit_indent_line(t + " = call " + ret_ltype + " @" + fname + "(" + args_str + ")");
        result t;
    conclude
    result "0";
end
