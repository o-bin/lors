# Volume IX: Complete Module Reference Catalog

## Chapter 28: Exhaustive Directory and File Catalog of All 68 Compiler Modules

This chapter provides a complete architectural inventory of all 68 source modules comprising the Stage 6 compiler.

---

### Layer 1: Common Utilities (`src/common/`)

1. **`constants.inc`**: Token types (`TOK_*`), AST node kinds (`AST_*`), and language type tags (`TYPE_*`).
2. **`declarations.inc`**: Central interface prototypes and shared global state declarations.
3. **`str_utils.inc`**: String searching, prefix/suffix matching, substring extraction, character tests (`char_is_digit`, `char_is_alpha`).
4. **`list_utils.inc`**: Serialized dynamic string lists (`str_list_*`) and integer lists (`int_list_*`).
5. **`path_utils.inc`**: Path utilities (`path_dirname`, `path_basename`, `path_join`, `path_is_safe`).
6. **`error_handler.inc`**: Formatted compiler error reporting with line/column diagnostic output.

---

### Layer 2: Memory & Storage (`src/memory/`)

7. **`arena_allocator.inc`**: Monotonic linear memory pool allocator (`arena_alloc`).
8. **`buffer_contiguous.inc`**: Contiguous dynamic array storage (`buffer_append`, `buffer_get`).
9. **`paged_storage.inc`**: Virtual paged storage for strings and integers (`page_str_*`, `page_int_*`).
10. **`string_interner.inc`**: 64-bit FNV-1a hash table for deduplicated string storage (`intern_string`, `get_interned_string`).

---

### Layer 3: Abstract Syntax Tree (`src/ast/`)

11. **`ast_node.inc`**: Node allocation and child linking (`ast_create_node`, `ast_add_child`).
12. **`ast_storage.inc`**: Structure-of-Arrays (SoA) dynamic table arrays for AST node properties.
13. **`ast_helpers.inc`**: Node inspection, traversal, and type tagging utilities (`ast_get_*`, `ast_set_*`).

---

### Layer 4: Preprocessor (`src/preprocessor/`)

14. **`file_reader.inc`**: Direct file system read/write bindings (`read_source_file`).
15. **`include_resolver.inc`**: Recursive `incorporate` resolution with cycle detection registry (`preprocess_file`).

---

### Layer 5: Lexer (`src/lexer/`)

16. **`token_struct.inc`**: Token parallel storage (`tok_types_data`, `tok_vals_data`, `tok_lines_data`, `tok_cols_data`).
17. **`lexer_state.inc`**: Source buffer tracking and cursor advancement (`lexer_peek`, `lexer_advance`).
18. **`lexer_keywords.inc`**: Keyword matching dictionary and token classification.
19. **`lexer_literals.inc`**: Numerical, floating-point, string, and identifier scanning.
20. **`lexer_core.inc`**: Main tokenization loop dispatching character classes (`lexer_tokenize`).

---

### Layer 6: Parser (`src/parser/`)

21. **`parser_state.inc`**: Token lookahead, peek, advance, match, and expect helpers.
22. **`parse_type.inc`**: Type specifier parser for primitives, custom structs, and `sequence<T>`.
23. **`parse_struct.inc`**: Record definitions and field declarations (`parse_struct_decl`).
24. **`parse_algorithm.inc`**: Function signatures, parameters, and return types (`parse_algorithm_decl`).
25. **`parse_stmt_decl.inc`**: Local and global variable declarations (`datum x : type = val;`).
26. **`parse_stmt_assign.inc`**: Variable assignments (`x = val;`).
27. **`parse_stmt_flow.inc`**: Conditional (`verify`) and loop (`cycle`) statements.
28. **`parse_stmt_io.inc`**: Output statements (`reveal`) and return statements (`result`).
29. **`parse_expr_binary.inc`**: Binary expression precedence climbing (`+`, `-`, `*`, `/`, `==`, `and`, `or`).
30. **`parse_expr_unary.inc`**: Unary operators (`not`, `-`).
31. **`parse_postfix.inc`**: Function calls, array indexation, and member access.
32. **`parse_primary.inc`**: Literal numbers, strings, booleans, identifiers, and parenthesized expressions.
33. **`parse_program.inc`**: Top-level compilation unit entry point (`parse_program`).

---

### Layer 7: Semantic Analysis (`src/semantic/`)

34. **`symbol_table.inc`**: Lexical scope stack, symbol registration, and shadowed lookup (`sym_add_var`, `sym_lookup_var`).
35. **`symbol_struct.inc`**: Structure registration and function symbol lookup helpers.
36. **`struct_registry.inc`**: Struct registry, field types, and member offsets (`struct_register`, `struct_lookup`).
37. **`type_checker_expr.inc`**: Bottom-up expression type checking and inference (`infer_expr_type`).
38. **`type_checker_stmt.inc`**: Statement validation and block type checking (`type_check_stmt`).
39. **`type_checker_calls.inc`**: Function call signature matching and return type resolution (`infer_call_type`).
40. **`semantic_analyzer.inc`**: 3-pass semantic analysis orchestrator (`run_semantic_analysis`).

---

### Layer 8: Code Generation (`src/codegen/`)

41. **`llvm_types.inc`**: Mapping Lors types to LLVM IR type strings (`llvm_get_type`).
42. **`llvm_env.inc`**: Register allocation (`%t0`), labels, and symbol address resolution.
43. **`llvm_strings.inc`**: String constant pool deduplication and character escaping.
44. **`llvm_emitter.inc`**: Code buffer emission and indentation helpers.
45. **`llvm_decl_struct.inc`**: LLVM IR `%struct.<name> = type { ... }` emission.
46. **`llvm_decl_func.inc`**: Global variables, function definitions (`define`), and external forward declarations (`declare`).
47. **`llvm_stmt_dispatch.inc`**: Statement codegen dispatcher (`cg_generate_statement`).
48. **`llvm_stmt_assign.inc`**: Assignment code generation.
49. **`llvm_stmt_decl.inc`**: Variable declaration code generation (`alloca`, `store`).
50. **`llvm_stmt_flow.inc`**: Conditional (`br i1`) and loop basic block generation.
51. **`llvm_stmt_io.inc`**: `reveal` and `result` code generation.
52. **`llvm_expr_dispatch.inc`**: Expression codegen dispatcher (`cg_generate_expression`).
53. **`llvm_expr_primary.inc`**: Literals, variables, and boolean constants.
54. **`llvm_expr_binary.inc`**: Arithmetic, comparison, and logical LLVM SSA instructions.
55. **`llvm_expr_unary.inc`**: Unary negation and NOT instructions.
56. **`llvm_expr_calls.inc`**: Function call code generation and signature auto-declaration.
57. **`llvm_expr_construct.inc`**: Struct heap allocation and field initializers.
58. **`llvm_expr_array.inc`**: Sequence creation and element access code generation.
59. **`llvm_expr_struct.inc`**: Struct member `getelementptr` and load instructions.
60. **`llvm_expr_builtin.inc`**: Builtin math, string, and OS function call generation.
61. **`llvm_runtime_decls.inc`**: Standard C library declarations (`printf`, `malloc`, `strlen`, `system`, etc.).
62. **`llvm_runtime_helpers.inc`**: Embedded string formatting and comparison helpers.
63. **`llvm_runtime_fs.inc`**: Embedded filesystem read/write helpers.
64. **`llvm_runtime_seq.inc`**: Embedded dynamic sequence runtime helpers.
65. **`llvm_entrypoint.inc`**: C `@main` runtime wrapper invoking Lors `genesis()`.
66. **`llvm_module.inc`**: Complete LLVM module emission orchestrator (`cg_generate_module`).

---

### Layer 9: Driver (`src/driver/`)

67. **`cli_options.inc`**: CLI argument parsing (`-o`, `-debug`, `-d`, `-s`, `-oall`, `-iall`).
68. **`compile_pipeline.inc`**: Single-file compilation pipeline and Clang backend invocation (`compile_single_file`).
69. **`batch_compiler.inc`**: Multi-file batch compilation and linking (`run_batch_compile_all`, `run_batch_link_all`).
70. **`main_driver.inc`**: Compiler executable genesis entry point (`genesis`).
