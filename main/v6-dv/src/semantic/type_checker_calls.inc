// ==========================================
// Lors Compiler v6 - Function & Builtin Type Inference
// Layer: Semantic Analysis
// ==========================================

algorithm infer_builtin_call_type(fname : series, node_id : whole) -> whole
begin
    // 1. Built-in Integer Functions
    verify (fname == "length" or fname == "char_at" or fname == "execute_system" or fname == "arg_count" or fname == "to_integer") then
        ast_set_type(node_id, TYPE_WHOLE, "whole");
        result TYPE_WHOLE;
    conclude

    // 2. Built-in String Functions
    verify (fname == "substring" or fname == "to_string" or fname == "inquire" or fname == "to_upper" or fname == "to_lower" or fname == "reverse" or fname == "file_read" or fname == "env_get" or fname == "arg_value") then
        ast_set_type(node_id, TYPE_SERIES, "series");
        result TYPE_SERIES;
    conclude

    // 3. Built-in Float Functions
    verify (fname == "to_precise" or fname == "sine" or fname == "cosine" or fname == "tan" or fname == "root" or fname == "power" or fname == "math_pi" or fname == "abs_val" or fname == "abs" or fname == "absolute") then
        ast_set_type(node_id, TYPE_PRECISE, "precise");
        result TYPE_PRECISE;
    conclude

    // 4. Built-in Boolean Functions
    verify (fname == "is_upper" or fname == "is_lower" or fname == "is_digit" or fname == "is_alnum" or fname == "file_exists" or fname == "path_is_safe") then
        ast_set_type(node_id, TYPE_STATE, "state");
        result TYPE_STATE;
    conclude
    verify (str_starts_with(fname, "str_starts_") or str_starts_with(fname, "str_ends_") or str_starts_with(fname, "str_contains") or str_starts_with(fname, "char_is_") or str_starts_with(fname, "path_is_") or str_starts_with(fname, "inc_is_") or str_starts_with(fname, "parse_match") or str_starts_with(fname, "parse_expect") or fname == "parse_type_specifier" or str_starts_with(fname, "is_") or fname == "lexer_is_at_end") then
        ast_set_type(node_id, TYPE_STATE, "state");
        result TYPE_STATE;
    conclude

    // 5. Built-in Sequence Functions
    verify (fname == "split_lines") then
        ast_set_type(node_id, TYPE_SEQUENCE, "sequence<series>");
        result TYPE_SEQUENCE;
    conclude

    // 6. Cross-Module String Return Functions (Fallback Heuristics)
    verify (str_starts_with(fname, "cg_") or str_starts_with(fname, "llvm_")) then
        ast_set_type(node_id, TYPE_SERIES, "series");
        result TYPE_SERIES;
    conclude
    verify (fname == "token_get_val" or fname == "parse_peek_val" or fname == "ast_get_s_val" or fname == "ast_get_type_name") then
        ast_set_type(node_id, TYPE_SERIES, "series");
        result TYPE_SERIES;
    conclude
    verify (fname == "sym_get_var_type_name" or fname == "struct_get_field_type_name" or fname == "fn_lookup_ret_name" or fname == "extract_sequence_elem_type") then
        ast_set_type(node_id, TYPE_SERIES, "series");
        result TYPE_SERIES;
    conclude
    verify (fname == "preprocess_file" or fname == "read_source_file" or fname == "get_interned_string" or fname == "path_dirname" or fname == "path_basename" or fname == "path_join") then
        ast_set_type(node_id, TYPE_SERIES, "series");
        result TYPE_SERIES;
    conclude
    verify (str_starts_with(fname, "str_list_") or str_starts_with(fname, "int_list_add") or str_starts_with(fname, "int_list_set") or str_starts_with(fname, "page_str_") or str_starts_with(fname, "page_init_") or str_starts_with(fname, "page_int_set")) then
        ast_set_type(node_id, TYPE_SERIES, "series");
        result TYPE_SERIES;
    conclude

    // 7. Cross-Module Whole/Integer Functions (Fallback Heuristics)
    verify (str_starts_with(fname, "page_int_get") or str_starts_with(fname, "int_list_get") or str_starts_with(fname, "ast_") or str_starts_with(fname, "sym_") or str_starts_with(fname, "fn_") or str_starts_with(fname, "struct_") or str_starts_with(fname, "token_") or str_starts_with(fname, "lexer_") or str_starts_with(fname, "parse_") or str_starts_with(fname, "arena_") or str_starts_with(fname, "intern_") or fname == "fnv1a_hash") then
        ast_set_type(node_id, TYPE_WHOLE, "whole");
        result TYPE_WHOLE;
    conclude

    result TYPE_UNKNOWN;
end

algorithm infer_call_type(node_id : whole) -> whole
begin
    datum fname : series = ast_get_s_val(node_id);
    datum arg_cnt : whole = ast_get_child_count(node_id);
    datum a_i : whole = 0;
    cycle (a_i < arg_cnt) do
        infer_expr_type(ast_get_child(node_id, a_i));
        a_i = a_i + 1;
    conclude

    // 1. Struct constructor check
    verify (struct_lookup(fname) != -1) then
        ast_set_type(node_id, TYPE_STRUCT, fname);
        ast_set_n_val(node_id, 1);
        result TYPE_STRUCT;
    conclude

    // 2. User-defined function & Declarations from headers
    datum user_tag : whole = fn_lookup_ret_tag(fname);
    verify (user_tag != TYPE_UNKNOWN) then
        datum user_tname : series = fn_lookup_ret_name(fname);
        ast_set_type(node_id, user_tag, user_tname);
        result user_tag;
    conclude

    // 3. Builtin functions & Fallback cross-module heuristics
    datum b_tag : whole = infer_builtin_call_type(fname, node_id);
    verify (b_tag != TYPE_UNKNOWN) then
        result b_tag;
    conclude

    ast_set_type(node_id, TYPE_UNKNOWN, "unknown");
    result TYPE_UNKNOWN;
end
