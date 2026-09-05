algorithm garbage_collect() -> void
begin
    // 1. Reset AST
    datum empty_nodes : sequence<ASTNode>;
    node_heap = empty_nodes;

    // 2. Reset Tokens
    datum empty_tokens : sequence<Token>;
    token_stream = empty_tokens;

    // 3. Reset Lexer & Strings
    lexer_source = "";
    lexer_len = 0;
    lexer_pos = 0;
    lexer_line = 1;
    lexer_col = 1;

    // 4. Reset Parser
    parser_pos = 0;
    parser_len = 0;

    // 5. Reset Symbols & Types
    datum empty_series : sequence<series>;
    datum empty_whole : sequence<whole>;
    sym_names = empty_series;
    sym_types = empty_series;
    sym_scopes = empty_whole;
    current_scope = 0;

    func_names = empty_series;
    func_ret_types = empty_series;

    struct_names = empty_series;
    struct_field_parent = empty_whole;
    struct_field_names = empty_series;
    struct_field_types = empty_series;

    // 6. Reset Codegen
    codegen_output = "";
    global_strings_output = "";
    llvm_tmp_count = 0;
    llvm_label_count = 0;
    string_count = 0;
    current_func_name = "";


    // Safety: Reset global pointer if possible
    // (In C++ backend, vectors are cleared)
end
