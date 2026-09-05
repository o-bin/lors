// ==========================================
// Lors Compiler v6 - Module Assembly & Code Generation
// Layer: Code Generation
// ==========================================

algorithm cg_generate_module(prog_node : whole) -> series
begin
    cg_init();
    cg_str_pool_init();
    cg_env_module_init();

    cg_emit_line("; ModuleID = 'lors_program'");
    cg_emit_line("source_filename = \"lors_program.lr\"");
    cg_emit_line("target datalayout = \"e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128\"");
    cg_emit_line("target triple = \"x86_64-unknown-linux-gnu\"");
    cg_emit_line("");

    datum top_cnt : whole = ast_get_child_count(prog_node);
    datum has_genesis : state = false;
    datum node : whole = 0;

    // 0. Register all defined functions and globals in this module
    datum k_fn : whole = 0;
    cycle (k_fn < top_cnt) do
        node = ast_get_child(prog_node, k_fn);
        verify (ast_get_kind(node) == AST_ALGORITHM_DECL) then
            datum f_name : series = ast_get_s_val(node);
            datum is_ext : state = (ast_get_n_val(node) == 1);
            verify (is_ext == false) then
                cg_defined_functions = cg_defined_functions + f_name + ";";
            conclude
            verify (f_name == "genesis") then
                has_genesis = true;
            conclude
        conclude
        verify (ast_get_kind(node) == AST_GLOBAL_DATUM) then
            datum g_name : series = ast_get_s_val(node);
            cg_defined_globals = cg_defined_globals + g_name + ";";
        conclude
        k_fn = k_fn + 1;
    conclude

    // 1. Emit Struct Definitions (deduplicated)
    datum emitted_structs : series = ";";
    datum i : whole = 0;
    cycle (i < top_cnt) do
        node = ast_get_child(prog_node, i);
        verify (ast_get_kind(node) == AST_STRUCT_DECL) then
            datum sname : series = ast_get_s_val(node);
            verify (str_contains(emitted_structs, ";" + sname + ";") == false) then
                cg_emit_struct_definition(node);
                emitted_structs = emitted_structs + sname + ";";
            conclude
        conclude
        i = i + 1;
    conclude
    cg_emit_line("");

    // 2. Emit Runtime Declarations
    cg_emit_runtime_declarations();

    // 3. Emit Global Variables (deduplicated)
    datum emitted_globals : series = ";";
    i = 0;
    cycle (i < top_cnt) do
        node = ast_get_child(prog_node, i);
        verify (ast_get_kind(node) == AST_GLOBAL_DATUM) then
            datum gname : series = ast_get_s_val(node);
            verify (str_contains(emitted_globals, ";" + gname + ";") == false) then
                cg_emit_global_datum(node);
                emitted_globals = emitted_globals + gname + ";";
            conclude
        conclude
        i = i + 1;
    conclude
    cg_emit_line("");

    // 4. Emit Runtime Helpers
    cg_emit_runtime_helpers();
    cg_emit_fs_and_str_helpers();
    cg_emit_sequence_helpers();

    // 5. Emit Algorithm Definitions & External Declarations
    datum emitted_decls : series = ";";
    i = 0;
    cycle (i < top_cnt) do
        node = ast_get_child(prog_node, i);
        verify (ast_get_kind(node) == AST_ALGORITHM_DECL) then
            datum is_ext2 : state = (ast_get_n_val(node) == 1);
            datum fname2 : series = ast_get_s_val(node);
            verify (is_ext2) then
                verify (str_contains(cg_defined_functions, ";" + fname2 + ";") == false and str_contains(emitted_decls, ";" + fname2 + ";") == false) then
                    cg_emit_algorithm(node);
                    emitted_decls = emitted_decls + fname2 + ";";
                conclude
            otherwise
                cg_emit_algorithm(node);
            conclude
        conclude
        i = i + 1;
    conclude

    // 6. Emit External Forward Declarations & Globals
    cg_emit_external_globals();
    verify (length(cg_external_decls) > 0) then
        cg_emit_line("; --- External Forward Declarations ---");
        cg_emit_line(cg_external_decls);
    conclude

    // 7. Emit Main Entrypoint
    cg_emit_main_entrypoint(has_genesis);

    // 8. Emit String Constant Pool
    cg_emit_string_pool();

    result cg_get_code();
end
