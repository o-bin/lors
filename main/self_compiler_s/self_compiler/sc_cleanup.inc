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

    // 5. Reset Codegen
    codegen_output = "";
    indent_level = 0;

    // Safety: Reset global pointer if possible
    // (In C++ backend, vectors are cleared)
end
