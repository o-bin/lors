// ==========================================
// Lors Compiler v6 - Reveal & Result Codegen
// ==========================================

algorithm cg_stmt_reveal(node_id : whole) -> void
begin
    datum child : whole = ast_get_child(node_id, 0);
    datum val : series = cg_generate_expression(child);
    datum tag : whole = cg_get_node_type_tag(child);

    verify (tag == TYPE_PRECISE) then
        cg_emit_indent_line("call i32 (ptr, ...) @printf(ptr @.fmt_f64, double " + val + ")");
        result;
    conclude

    verify (tag == TYPE_SERIES) then
        cg_emit_indent_line("call i32 (ptr, ...) @printf(ptr @.fmt_str, ptr " + val + ")");
        result;
    conclude

    verify (tag == TYPE_STATE) then
        datum t_fmt : series = cg_new_temp();
        cg_emit_indent_line(t_fmt + " = select i1 " + val + ", ptr @.fmt_true, ptr @.fmt_false");
        cg_emit_indent_line("call i32 (ptr, ...) @printf(ptr " + t_fmt + ")");
        result;
    conclude

    // Whole integer or other
    cg_emit_indent_line("call i32 (ptr, ...) @printf(ptr @.fmt_i64, i64 " + val + ")");
end

algorithm cg_stmt_result(node_id : whole) -> void
begin
    verify (ast_get_child_count(node_id) > 0) then
        datum child : whole = ast_get_child(node_id, 0);
        datum val : series = cg_generate_expression(child);
        datum tag : whole = cg_get_node_type_tag(child);
        datum ltype : series = cg_current_func_ret_ltype;
        verify (length(ltype) == 0 or ltype == "void") then
            datum tname : series = ast_get_type_name(child);
            ltype = llvm_get_type(tag, tname);
        conclude

        verify (ltype == "double" and tag != TYPE_PRECISE) then
            datum t_fp : series = cg_new_temp();
            cg_emit_indent_line(t_fp + " = sitofp i64 " + val + " to double");
            val = t_fp;
        conclude

        cg_emit_indent_line("ret " + ltype + " " + val);
    otherwise
        cg_emit_indent_line("ret void");
    conclude
end
