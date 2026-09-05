// ==========================================
// Lors Compiler v6 - Expression Type Inference
// Layer: Semantic Analysis
// ==========================================

algorithm extract_sequence_elem_type(seq_type_name : series) -> series
begin
    datum slen : whole = length(seq_type_name);
    verify (slen > 10 and str_starts_with(seq_type_name, "sequence<")) then
        datum elem : series = substring(seq_type_name, 9, slen - 10);
        result elem;
    conclude
    result "whole";
end

algorithm infer_expr_type(node_id : whole) -> whole
begin
    verify (node_id < 0 or node_id >= ast_total_nodes) then
        result TYPE_UNKNOWN;
    conclude

    datum kind : whole = ast_get_kind(node_id);

    // 1. Literals
    verify (kind == AST_INT) then result TYPE_WHOLE; conclude
    verify (kind == AST_FLOAT) then result TYPE_PRECISE; conclude
    verify (kind == AST_STRING) then result TYPE_SERIES; conclude
    verify (kind == AST_BOOL) then result TYPE_STATE; conclude

    // 2. Identifier
    verify (kind == AST_IDENT) then
        datum var_name : series = ast_get_s_val(node_id);
        datum tag : whole = sym_get_var_type(var_name);
        datum tname : series = sym_get_var_type_name(var_name);
        ast_set_type(node_id, tag, tname);
        result tag;
    conclude

    // 3. Member Access (expr.field)
    verify (kind == AST_MEMBER) then
        datum base_node : whole = ast_get_child(node_id, 0);
        infer_expr_type(base_node);
        datum sname : series = ast_get_type_name(base_node);
        datum fname : series = ast_get_s_val(node_id);
        datum ftag : whole = struct_get_field_type(sname, fname);
        datum ftname : series = struct_get_field_type_name(sname, fname);
        ast_set_type(node_id, ftag, ftname);
        result ftag;
    conclude

    // 4. Index Access (arr[i])
    verify (kind == AST_INDEX) then
        datum arr_node : whole = ast_get_child(node_id, 0);
        datum idx_node : whole = ast_get_child(node_id, 1);
        infer_expr_type(arr_node);
        infer_expr_type(idx_node);
        datum seq_tname : series = ast_get_type_name(arr_node);
        datum idx_elem_tname : series = extract_sequence_elem_type(seq_tname);
        datum elem_tag : whole = TYPE_WHOLE;
        verify (idx_elem_tname == "precise") then elem_tag = TYPE_PRECISE; conclude
        verify (idx_elem_tname == "series") then elem_tag = TYPE_SERIES; conclude
        verify (idx_elem_tname == "state") then elem_tag = TYPE_STATE; conclude
        verify (struct_lookup(idx_elem_tname) != -1) then elem_tag = TYPE_STRUCT; conclude
        ast_set_type(node_id, elem_tag, idx_elem_tname);
        result elem_tag;
    conclude

    // 5. Array Literal
    verify (kind == AST_ARRAY_LIT) then
        datum cnt : whole = ast_get_child_count(node_id);
        datum arr_elem_tname : series = "whole";
        verify (cnt > 0) then
            datum first_child : whole = ast_get_child(node_id, 0);
            infer_expr_type(first_child);
            arr_elem_tname = ast_get_type_name(first_child);
            datum k : whole = 1;
            cycle (k < cnt) do
                infer_expr_type(ast_get_child(node_id, k));
                k = k + 1;
            conclude
        conclude
        ast_set_type(node_id, TYPE_SEQUENCE, "sequence<" + arr_elem_tname + ">");
        result TYPE_SEQUENCE;
    conclude

    // 6. Unary Op
    verify (kind == AST_UNOP) then
        datum sub_node : whole = ast_get_child(node_id, 0);
        datum sub_tag : whole = infer_expr_type(sub_node);
        datum un_op : series = ast_get_s_val(node_id);
        verify (un_op == "not") then
            ast_set_type(node_id, TYPE_STATE, "state");
            result TYPE_STATE;
        conclude
        ast_set_type(node_id, sub_tag, ast_get_type_name(sub_node));
        result sub_tag;
    conclude

    // 7. Binary Op
    verify (kind == AST_BINOP) then
        datum l_node : whole = ast_get_child(node_id, 0);
        datum r_node : whole = ast_get_child(node_id, 1);
        datum l_tag : whole = infer_expr_type(l_node);
        datum r_tag : whole = infer_expr_type(r_node);
        datum bin_op : series = ast_get_s_val(node_id);

        verify (bin_op == "==" or bin_op == "!=" or bin_op == "<" or bin_op == "<=" or bin_op == ">" or bin_op == ">=" or bin_op == "and" or bin_op == "or") then
            ast_set_type(node_id, TYPE_STATE, "state");
            result TYPE_STATE;
        conclude
        verify (bin_op == "+" and (l_tag == TYPE_SERIES or r_tag == TYPE_SERIES)) then
            ast_set_type(node_id, TYPE_SERIES, "series");
            result TYPE_SERIES;
        conclude
        verify (l_tag == TYPE_PRECISE or r_tag == TYPE_PRECISE) then
            ast_set_type(node_id, TYPE_PRECISE, "precise");
            result TYPE_PRECISE;
        conclude
        ast_set_type(node_id, TYPE_WHOLE, "whole");
        result TYPE_WHOLE;
    conclude

    // 8. Function Call or Struct Constructor
    verify (kind == AST_CALL) then
        result infer_call_type(node_id);
    conclude

    result TYPE_UNKNOWN;
end
