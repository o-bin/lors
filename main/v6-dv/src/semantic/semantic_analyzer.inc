// ==========================================
// Lors Compiler v6 - Semantic Analysis Pipeline
// Layer: Semantic Analysis
// ==========================================

algorithm run_semantic_analysis(prog_node : whole) -> void
begin
    sym_init();
    struct_reg_init();

    datum top_cnt : whole = ast_get_child_count(prog_node);
    datum node : whole = 0;

    // Pass 1: Structures
    datum i : whole = 0;
    cycle (i < top_cnt) do
        node = ast_get_child(prog_node, i);
        verify (ast_get_kind(node) == AST_STRUCT_DECL) then
            datum sname : series = ast_get_s_val(node);
            struct_register(sname);
            datum f_cnt : whole = ast_get_child_count(node);
            datum f : whole = 0;
            cycle (f < f_cnt) do
                datum f_node : whole = ast_get_child(node, f);
                datum fname : series = ast_get_s_val(f_node);
                datum ftag : whole = ast_get_type_tag(f_node);
                datum ftname : series = ast_get_type_name(f_node);
                struct_add_field(sname, fname, ftag, ftname);
                f = f + 1;
            conclude
        conclude
        i = i + 1;
    conclude

    // Pass 2: Algorithm Signatures
    i = 0;
    cycle (i < top_cnt) do
        node = ast_get_child(prog_node, i);
        verify (ast_get_kind(node) == AST_ALGORITHM_DECL) then
            datum fn_name : series = ast_get_s_val(node);
            datum rtag : whole = ast_get_type_tag(node);
            datum rtname : series = ast_get_type_name(node);
            datum sig_p_cnt : whole = ast_get_child_count(node);
            // If body exists, last child is body block
            verify (ast_get_n_val(node) == 0 and sig_p_cnt > 0) then
                sig_p_cnt = sig_p_cnt - 1;
            conclude
            fn_register(fn_name, rtag, rtname, sig_p_cnt);
        conclude
        i = i + 1;
    conclude

    // Pass 3: Check Bodies and Globals
    i = 0;
    cycle (i < top_cnt) do
        node = ast_get_child(prog_node, i);
        verify (ast_get_kind(node) == AST_GLOBAL_DATUM) then
            type_check_stmt(node);
        otherwise
            verify (ast_get_kind(node) == AST_ALGORITHM_DECL) then
                verify (ast_get_n_val(node) == 0) then // If has body
                    sym_enter_scope();
                    datum total_children : whole = ast_get_child_count(node);
                    datum body_p_cnt : whole = total_children - 1;
                    datum p : whole = 0;
                    cycle (p < body_p_cnt) do
                        datum param_node : whole = ast_get_child(node, p);
                        datum pname : series = ast_get_s_val(param_node);
                        datum ptag : whole = ast_get_type_tag(param_node);
                        datum ptname : series = ast_get_type_name(param_node);
                        sym_add_var(pname, ptag, ptname);
                        p = p + 1;
                    conclude
                    datum body_node : whole = ast_get_child(node, total_children - 1);
                    type_check_stmt(body_node);
                    sym_exit_scope();
                conclude
            conclude
        conclude
        i = i + 1;
    conclude
end
