// ==========================================
// Lors Compiler v6 - Core Declarations & Shared State
// Layer: Common
// ==========================================

// --- Shared Global Variables ---
datum flag_debug : state;
datum flag_delete_on_error : state;
datum flag_save_on_success : state;
datum flag_object_output : state;
datum flag_oall : state;
datum flag_iall : state;
datum flag_ns_name : series;
datum cli_input_file : series;
datum lex_src : series;
datum lex_pos : whole;
datum lex_line : whole;
datum lex_col : whole;
datum tok_count : whole;
datum parse_pos : whole;
datum ast_total_nodes : whole;
datum sym_count : whole;
datum sym_current_scope : whole;
datum fn_count : whole;
datum struct_count : whole;
datum cg_code : series;
datum cg_temp_count : whole;
datum cg_label_count : whole;
datum cg_var_count : whole;
datum cg_current_func_ret_ltype : series;

// --- Driver & Pipeline ---
algorithm cli_parse_options() -> void;
algorithm compile_single_file(input_file : series, dbg : state, del_err : state, save_succ : state, obj_out : state) -> void;
algorithm run_backend_compilation(ll_file : series, out_bin : series, is_obj : state, dbg : state, del_err : state, save_succ : state) -> void;
algorithm run_batch_compile_all(dbg : state, del_err : state, save_succ : state) -> void;
algorithm run_batch_link_all(ns_name : series) -> void;

// --- Common Utilities & Error Handler ---
algorithm path_dirname(filepath : series) -> series;
algorithm path_basename(filepath : series) -> series;
algorithm path_is_safe(filepath : series) -> state;
algorithm path_join(dir : series, file : series) -> series;
algorithm str_starts_with(s : series, prefix : series) -> state;
algorithm str_ends_with(s : series, suffix : series) -> state;
algorithm str_contains(s : series, sub : series) -> state;
algorithm char_is_digit(c : whole) -> state;
algorithm char_is_alpha(c : whole) -> state;
algorithm char_is_alnum(c : whole) -> state;
algorithm char_is_space(c : whole) -> state;
algorithm str_list_add(list : series, item : series) -> series;
algorithm str_list_get(list : series, index : whole) -> series;
algorithm str_list_set(list : series, index : whole, item : series) -> series;
algorithm int_list_add(list : series, item : whole) -> series;
algorithm int_list_get(list : series, index : whole) -> whole;
algorithm int_list_set(list : series, index : whole, item : whole) -> series;
algorithm error_report(msg : series, line : whole, col : whole) -> void;

// --- Memory & Storage ---
algorithm arena_alloc_init() -> void;
algorithm arena_alloc(size : whole) -> whole;
algorithm buffer_init() -> void;
algorithm buffer_append(val : whole) -> void;
algorithm buffer_get(idx : whole) -> whole;
algorithm page_init_str(cap : whole) -> series;
algorithm page_str_set(pages : series, idx : whole, val : series) -> series;
algorithm page_str_get(pages : series, idx : whole) -> series;
algorithm page_init_int(cap : whole) -> series;
algorithm page_int_set(pages : series, idx : whole, val : whole) -> series;
algorithm page_int_get(pages : series, idx : whole) -> whole;
algorithm fnv1a_hash(s : series) -> whole;
algorithm intern_string(s : series) -> whole;
algorithm get_interned_string(id : whole) -> series;

// --- Preprocessor & Lexer ---
algorithm inc_init() -> void;
algorithm inc_is_visited(path : series) -> state;
algorithm inc_mark_visited(path : series) -> void;
algorithm preprocess_file(path : series) -> series;
algorithm read_source_file(path : series) -> series;
algorithm lexer_state_init(src : series) -> void;
algorithm lexer_is_at_end() -> state;
algorithm lexer_peek() -> whole;
algorithm lexer_peek_next() -> whole;
algorithm lexer_advance() -> whole;
algorithm lexer_tokenize() -> void;
algorithm token_add(ttype : whole, val : series, line : whole, col : whole) -> void;
algorithm token_get_type(idx : whole) -> whole;
algorithm token_get_val(idx : whole) -> series;
algorithm token_get_line(idx : whole) -> whole;
algorithm token_get_col(idx : whole) -> whole;

// --- AST ---
algorithm ast_init() -> void;
algorithm ast_create_node(kind : whole, s_val : series, n_val : whole, line : whole) -> whole;
algorithm ast_add_child(parent : whole, child : whole) -> void;
algorithm ast_get_kind(node_id : whole) -> whole;
algorithm ast_get_s_val(node_id : whole) -> series;
algorithm ast_get_n_val(node_id : whole) -> whole;
algorithm ast_get_type_tag(node_id : whole) -> whole;
algorithm ast_get_type_name(node_id : whole) -> series;
algorithm ast_get_child_count(node_id : whole) -> whole;
algorithm ast_get_child(node_id : whole, idx : whole) -> whole;
algorithm ast_set_type(node_id : whole, tag : whole, tname : series) -> void;
algorithm ast_set_n_val(node_id : whole, val : whole) -> void;
algorithm ast_set_s_val(node_id : whole, val : series) -> void;

// --- Parser ---
algorithm parser_init() -> void;
algorithm parse_peek_type() -> whole;
algorithm parse_peek_val() -> series;
algorithm parse_peek_line() -> whole;
algorithm parse_peek_col() -> whole;
algorithm parse_advance() -> void;
algorithm parse_match(expected_type : whole) -> state;
algorithm parse_expect(expected_type : whole, err_msg : series) -> state;
algorithm parse_type_specifier() -> state;
algorithm parse_program() -> whole;
algorithm parse_algorithm_decl() -> whole;
algorithm parse_statement() -> whole;
algorithm parse_expression() -> whole;
algorithm parse_struct_decl() -> whole;

// --- Semantic ---
algorithm run_semantic_analysis(prog_node : whole) -> void;
algorithm struct_reg_init() -> void;
algorithm struct_register(name : series) -> void;
algorithm struct_add_field(sname : series, fname : series, ftag : whole, ftname : series) -> void;
algorithm struct_lookup(name : series) -> whole;
algorithm struct_get_field_count(sname : series) -> whole;
algorithm struct_get_field_index(sname : series, fname : series) -> whole;
algorithm struct_get_field_type(sname : series, fname : series) -> whole;
algorithm struct_get_field_type_name(sname : series, fname : series) -> series;
algorithm sym_init() -> void;
algorithm sym_enter_scope() -> void;
algorithm sym_exit_scope() -> void;
algorithm sym_add_var(name : series, tag : whole, tname : series) -> void;
algorithm sym_lookup_var(name : series) -> whole;
algorithm sym_get_var_type(name : series) -> whole;
algorithm sym_get_var_type_name(name : series) -> series;
algorithm fn_register(name : series, rtag : whole, rtname : series, p_cnt : whole) -> void;
algorithm fn_lookup_ret_tag(name : series) -> whole;
algorithm fn_lookup_ret_name(name : series) -> series;
algorithm fn_lookup_param_count(name : series) -> whole;
algorithm infer_expr_type(node_id : whole) -> whole;
algorithm infer_call_type(node_id : whole) -> whole;
algorithm infer_builtin_call_type(fname : series, node_id : whole) -> whole;
algorithm type_check_stmt(node_id : whole) -> void;

// --- Codegen ---
algorithm cg_init() -> void;
algorithm cg_str_pool_init() -> void;
algorithm cg_env_module_init() -> void;
algorithm cg_emit(text : series) -> void;
algorithm cg_emit_line(line : series) -> void;
algorithm cg_emit_indent_line(line : series) -> void;
algorithm cg_get_code() -> series;
algorithm cg_new_temp() -> series;
algorithm cg_new_label(prefix : series) -> series;
algorithm cg_get_var_ptr(name : series) -> series;
algorithm cg_get_var_type(name : series) -> series;
algorithm cg_get_var_struct_name(name : series) -> series;
algorithm cg_register_var(name : series, ptr_reg : series, llvm_type : series, tname : series) -> void;
algorithm llvm_get_type(tag : whole, tname : series) -> series;
algorithm cg_generate_module(prog_node : whole) -> series;
algorithm cg_generate_statement(node_id : whole) -> void;
algorithm cg_generate_expression(node_id : whole) -> series;
algorithm cg_get_node_type_tag(node_id : whole) -> whole;
algorithm cg_expr_call(node_id : whole) -> series;
algorithm cg_expr_binary(node_id : whole) -> series;
algorithm cg_expr_unary(node_id : whole) -> series;
algorithm cg_expr_primary(node_id : whole) -> series;
