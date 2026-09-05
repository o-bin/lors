// ==========================================
// Lors Compiler v6 - Primary & Literal Expression Codegen
// ==========================================

algorithm cg_expr_primary(node_id : whole) -> series
begin
    datum kind : whole = ast_get_kind(node_id);
    datum val : series = ast_get_s_val(node_id);
    datum t : series = "";

    // 1. Integer Literal
    verify (kind == AST_INT) then
        result val;
    conclude

    // 2. Float Literal
    verify (kind == AST_FLOAT) then
        verify (str_contains(val, ".") == false) then
            result val + ".0";
        conclude
        result val;
    conclude

    // 3. String Literal
    verify (kind == AST_STRING) then
        datum label : series = cg_intern_string(val);
        t = cg_new_temp();
        datum byte_len : whole = length(val) + 1;
        datum gep_cmd : series = t + " = getelementptr [" + to_string(byte_len) + " x i8], ptr " + label + ", i64 0, i64 0";
        cg_emit_indent_line(gep_cmd);
        result t;
    conclude

    // 4. Boolean Literal
    verify (kind == AST_BOOL) then
        verify (val == "true") then
            result "1";
        conclude
        result "0";
    conclude

    // 5. Variable Identifier
    verify (kind == AST_IDENT) then
        datum ptr_reg : series = cg_get_var_ptr(val);
        datum ltype : series = cg_get_var_type(val);
        t = cg_new_temp();
        cg_emit_indent_line(t + " = load " + ltype + ", ptr " + ptr_reg);
        result t;
    conclude

    result "0";
end

algorithm cg_expr_unary(node_id : whole) -> series
begin
    datum op : series = ast_get_s_val(node_id);
    datum child : whole = ast_get_child(node_id, 0);
    datum child_val : series = cg_generate_expression(child);
    datum tag : whole = ast_get_type_tag(child);
    datum t : series = cg_new_temp();

    verify (op == "not") then
        cg_emit_indent_line(t + " = xor i1 " + child_val + ", true");
        result t;
    conclude

    verify (op == "-") then
        verify (tag == TYPE_PRECISE) then
            cg_emit_indent_line(t + " = fsub double 0.0, " + child_val);
        otherwise
            cg_emit_indent_line(t + " = sub i64 0, " + child_val);
        conclude
        result t;
    conclude

    result child_val;
end
