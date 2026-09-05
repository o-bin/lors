# Volume VI: Multi-Object Compilation & Topological Group Linking

## Chapter 19: The Modular Compilation Pipeline: Standalone `.inc` to `.o`

### 19.1 Transforming Modules into Independent Translation Units

In Stage 6, every `.inc` file in the `src/` directory is designed to be compiled in isolation directly into an ELF object file (`.o`).

```
src/parser/parse_algorithm.inc
            |
            v
[Automatic Header Injection] (constants.inc + declarations.inc)
            |
            v
[Lexer -> Parser -> Semantic Analyzer -> LLVM Codegen]
            |
            v
src/parser/parse_algorithm.ll
            |
            v
[Clang Backend: clang -Wno-override-module -c parse_algorithm.ll -o build_modular_objs/parse_algorithm.o]
            |
            v
build_modular_objs/parse_algorithm.o (ELF 64-bit LSB relocatable object)
```

---

### 19.2 The Build Automation Script (`build_all_modules.sh`)

The script `build_all_modules.sh` automates the compilation of all 68 `.inc` modules:

```bash
#!/bin/bash
set -e

BUILD_DIR="build_modular_objs"
mkdir -p "$BUILD_DIR"

COMPILER="./compiler"
passed=0
failed=0

for f in src/*/*.inc; do
    name=$(basename "$f" .inc)
    echo "[MODULO] $f"
    if $COMPILER "$f" -o; then
        mv "${f%.inc}.o" "$BUILD_DIR/$name.o"
        echo "-> OK"
        passed=$((passed + 1))
    else
        echo "-> FALLO"
        failed=$((failed + 1))
    fi
done

echo "Resumen de compilacion: Exitosos: $passed, Fallidos: $failed"
```

---

## Chapter 20: The Declarations Interface (`declarations.inc`) & Automatic Header Injection

### 20.1 The Interface Specification Pattern

In C/C++, header files (`.h`) contain `extern` variable declarations and function prototypes. In Lors Stage 6, this role is fulfilled by `src/common/declarations.inc`.

`src/common/declarations.inc` (149 lines) provides:
1. **Shared Global State Declarations**:
   ```lors
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
   ```
2. **Algorithm Prototypes Across All 9 Layers**:
   ```lors
   algorithm cli_parse_options() -> void;
   algorithm compile_single_file(input_file : series, dbg : state, del_err : state, save_succ : state, obj_out : state) -> void;
   algorithm run_semantic_analysis(prog_node : whole) -> void;
   algorithm cg_generate_module(prog_node : whole) -> series;
   algorithm parse_program() -> whole;
   algorithm lexer_tokenize() -> void;
   algorithm ast_create_node(kind : whole, s_val : series, n_val : whole, line : whole) -> whole;
   algorithm arena_alloc(size : whole) -> whole;
   algorithm str_contains(s : series, sub : series) -> state;
   ```

---

## Chapter 21: Topological Sorting of 68 Modules and Cyclic Group Linking with Clang/LLD

### 21.1 The Topological Linking Script (`link_all_modules.sh`)

Because the compiler modules have mutual dependencies (e.g., `parser` calls `ast`, `ast` calls `memory`, `codegen` calls `ast` and `semantic`), the linking script arranges the 68 objects in 9 strict topological layers:

```bash
#!/bin/bash
set -e

BUILD_DIR="build_modular_objs"
OUT_BIN="compiler_dev"

# Layer 1: Driver
LAYER_DRIVER=(
    "$BUILD_DIR/main_driver.o"
    "$BUILD_DIR/cli_options.o"
    "$BUILD_DIR/compile_pipeline.o"
    "$BUILD_DIR/batch_compiler.o"
)

# Layer 2: Codegen
LAYER_CODEGEN=(
    "$BUILD_DIR/llvm_module.o"
    "$BUILD_DIR/llvm_emitter.o"
    "$BUILD_DIR/llvm_env.o"
    "$BUILD_DIR/llvm_strings.o"
    "$BUILD_DIR/llvm_types.o"
    "$BUILD_DIR/llvm_decl_struct.o"
    "$BUILD_DIR/llvm_decl_func.o"
    "$BUILD_DIR/llvm_stmt_dispatch.o"
    "$BUILD_DIR/llvm_stmt_assign.o"
    "$BUILD_DIR/llvm_stmt_decl.o"
    "$BUILD_DIR/llvm_stmt_flow.o"
    "$BUILD_DIR/llvm_stmt_io.o"
    "$BUILD_DIR/llvm_expr_dispatch.o"
    "$BUILD_DIR/llvm_expr_binary.o"
    "$BUILD_DIR/llvm_expr_unary.o"
    "$BUILD_DIR/llvm_expr_primary.o"
    "$BUILD_DIR/llvm_expr_calls.o"
    "$BUILD_DIR/llvm_expr_construct.o"
    "$BUILD_DIR/llvm_expr_array.o"
    "$BUILD_DIR/llvm_expr_struct.o"
    "$BUILD_DIR/llvm_expr_builtin.o"
    "$BUILD_DIR/llvm_runtime_decls.o"
    "$BUILD_DIR/llvm_runtime_helpers.o"
    "$BUILD_DIR/llvm_runtime_fs.o"
    "$BUILD_DIR/llvm_runtime_seq.o"
    "$BUILD_DIR/llvm_entrypoint.o"
)

# Layer 3: Semantic Analysis
LAYER_SEMANTIC=(
    "$BUILD_DIR/semantic_analyzer.o"
    "$BUILD_DIR/symbol_table.o"
    "$BUILD_DIR/symbol_struct.o"
    "$BUILD_DIR/struct_registry.o"
    "$BUILD_DIR/type_checker_expr.o"
    "$BUILD_DIR/type_checker_stmt.o"
    "$BUILD_DIR/type_checker_calls.o"
)

# Layer 4: Parser
LAYER_PARSER=(
    "$BUILD_DIR/parse_program.o"
    "$BUILD_DIR/parser_state.o"
    "$BUILD_DIR/parse_algorithm.o"
    "$BUILD_DIR/parse_struct.o"
    "$BUILD_DIR/parse_type.o"
    "$BUILD_DIR/parse_stmt_decl.o"
    "$BUILD_DIR/parse_stmt_assign.o"
    "$BUILD_DIR/parse_stmt_flow.o"
    "$BUILD_DIR/parse_stmt_io.o"
    "$BUILD_DIR/parse_expr_binary.o"
    "$BUILD_DIR/parse_expr_unary.o"
    "$BUILD_DIR/parse_postfix.o"
    "$BUILD_DIR/parse_primary.o"
)

# Layer 5: Lexer
LAYER_LEXER=(
    "$BUILD_DIR/lexer_core.o"
    "$BUILD_DIR/lexer_keywords.o"
    "$BUILD_DIR/lexer_literals.o"
    "$BUILD_DIR/lexer_state.o"
    "$BUILD_DIR/token_struct.o"
)

# Layer 6: Preprocessor
LAYER_PREPROCESSOR=(
    "$BUILD_DIR/include_resolver.o"
    "$BUILD_DIR/file_reader.o"
)

# Layer 7: AST
LAYER_AST=(
    "$BUILD_DIR/ast_node.o"
    "$BUILD_DIR/ast_storage.o"
    "$BUILD_DIR/ast_helpers.o"
)

# Layer 8: Memory
LAYER_MEMORY=(
    "$BUILD_DIR/arena_allocator.o"
    "$BUILD_DIR/buffer_contiguous.o"
    "$BUILD_DIR/paged_storage.o"
    "$BUILD_DIR/string_interner.o"
)

# Layer 9: Common Utilities
LAYER_COMMON=(
    "$BUILD_DIR/constants.o"
    "$BUILD_DIR/declarations.o"
    "$BUILD_DIR/str_utils.o"
    "$BUILD_DIR/list_utils.o"
    "$BUILD_DIR/path_utils.o"
    "$BUILD_DIR/error_handler.o"
)

clang -Wno-override-module \
  -Wl,--start-group \
  "${LAYER_DRIVER[@]}" \
  "${LAYER_CODEGEN[@]}" \
  "${LAYER_SEMANTIC[@]}" \
  "${LAYER_PARSER[@]}" \
  "${LAYER_LEXER[@]}" \
  "${LAYER_PREPROCESSOR[@]}" \
  "${LAYER_AST[@]}" \
  "${LAYER_MEMORY[@]}" \
  "${LAYER_COMMON[@]}" \
  -Wl,--end-group \
  -lm -o "$OUT_BIN"
```

### 21.2 Why `-Wl,--start-group` is Essential
Standard linkers discard unresolved symbol requests if the defining object was already scanned earlier in the command line.
The GNU ld / LLVM lld flag `-Wl,--start-group ... -Wl,--end-group` instructs the linker to **loop continuously** through the archive and object list until every cyclic reference between AST, Lexer, Parser, Codegen, and Semantic layers is completely resolved.
