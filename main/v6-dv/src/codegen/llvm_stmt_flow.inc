// ==========================================
// Lors Compiler v6 - Flow Statements Codegen
// ==========================================

algorithm cg_stmt_verify(node_id : whole) -> void
begin
    datum cond_child : whole = ast_get_child(node_id, 0);
    datum cond_val : series = cg_generate_expression(cond_child);

    datum lbl_then : series = cg_new_label("then");
    datum lbl_else : series = cg_new_label("else");
    datum lbl_cont : series = cg_new_label("cont");

    datum has_else : state = false;
    verify (ast_get_child_count(node_id) > 2) then
        has_else = true;
    conclude

    verify (has_else) then
        cg_emit_indent_line("br i1 " + cond_val + ", label %" + lbl_then + ", label %" + lbl_else);
        cg_emit_line(lbl_then + ":");
        cg_generate_statement(ast_get_child(node_id, 1));
        cg_emit_indent_line("br label %" + lbl_cont);

        cg_emit_line(lbl_else + ":");
        cg_generate_statement(ast_get_child(node_id, 2));
        cg_emit_indent_line("br label %" + lbl_cont);
    otherwise
        cg_emit_indent_line("br i1 " + cond_val + ", label %" + lbl_then + ", label %" + lbl_cont);
        cg_emit_line(lbl_then + ":");
        cg_generate_statement(ast_get_child(node_id, 1));
        cg_emit_indent_line("br label %" + lbl_cont);
    conclude

    cg_emit_line(lbl_cont + ":");
end

algorithm cg_stmt_cycle(node_id : whole) -> void
begin
    datum cond_child : whole = ast_get_child(node_id, 0);
    datum body_child : whole = ast_get_child(node_id, 1);

    datum lbl_head : series = cg_new_label("cycle_head");
    datum lbl_body : series = cg_new_label("cycle_body");
    datum lbl_end  : series = cg_new_label("cycle_end");

    cg_emit_indent_line("br label %" + lbl_head);
    cg_emit_line(lbl_head + ":");

    datum cond_val : series = cg_generate_expression(cond_child);
    cg_emit_indent_line("br i1 " + cond_val + ", label %" + lbl_body + ", label %" + lbl_end);

    cg_emit_line(lbl_body + ":");
    cg_generate_statement(body_child);
    cg_emit_indent_line("br label %" + lbl_head);

    cg_emit_line(lbl_end + ":");
end
