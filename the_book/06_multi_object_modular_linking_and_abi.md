# Chapter 6: Multi-Object Modular Linking and ABI

## 6.1 The Challenge of Native Multi-Object Linking

In traditional C compilation, header files (`.h`) provide forward declarations so the compiler knows the exact calling convention for external symbols before emitting machine code.

When compiling 68 separate `.inc` files in Lors directly to `.o` files:
1. Each module is compiled in isolation.
2. If Module A calls `foo(x, y)` in Module B without knowing `foo`'s true signature, the code generator defaults parameter types or guesses them based on expressions.
3. On x86_64 architectures (System V ABI):
   - 64-bit integers and pointers use `%rdi`, `%rsi`, `%rdx`, `%rcx`, `%r8`, `%r9`.
   - Floating-point doubles use `%xmm0` through `%xmm7`.
   - Booleans (`i1`) are passed as low 8 bits.
4. Any mismatch in argument count, width, or return type between caller (`declare`) and callee (`define`) results in **register misalignment, stack corruption, or silent failures**.

---

## 6.2 The Declarations Solution (`src/common/declarations.inc`)

To solve this, the Stage 6 architecture introduces `src/common/declarations.inc`.

### Automatic Header Injection
During single-file compilation in `compile_pipeline.inc`:
```lors
    verify (str_ends_with(input_file, ".inc")) then
        verify (str_ends_with(input_file, "constants.inc") == false) then
            processed_code = preprocess_file("src/common/constants.inc") + "\n";
        conclude
        verify (str_ends_with(input_file, "declarations.inc") == false) then
            processed_code = processed_code + preprocess_file("src/common/declarations.inc") + "\n";
        conclude
    conclude
    processed_code = processed_code + preprocess_file(input_file);
```

### Clean Forward Declarations
1. Every module gains visibility of all 68 function signatures across all 9 architectural layers.
2. In `llvm_module.inc`, `cg_emit_algorithm` inspects each declaration:
   - If the function is implemented in the current file: it emits `define <ret> @name(...) { ... }`.
   - If the function is not implemented in this file: it emits `declare <ret> @name(...)` exactly once.
3. As a result, caller and callee signatures match with $100\%$ precision in LLVM IR.

---

## 6.3 Topological Group Linking (`link_all_modules.sh`)

When 68 object files have mutual and cyclic dependencies, standard one-pass linkers may fail with unresolved symbol errors if files are specified out of order.

### Topological Layering
The link script organizes the 68 objects into 9 topological tiers:

1. **Tier 1: Driver**: `main_driver.o`, `cli_options.o`, `compile_pipeline.o`, `batch_compiler.o`.
2. **Tier 2: Codegen**: All 24 `llvm_*.o` objects.
3. **Tier 3: Semantic**: `semantic_analyzer.o`, `symbol_table.o`, `struct_registry.o`, `type_checker_*.o`.
4. **Tier 4: Parser**: `parser_state.o`, `parse_program.o`, `parse_algorithm.o`, `parse_stmt_*.o`, `parse_expr_*.o`.
5. **Tier 5: Lexer**: `lexer_core.o`, `lexer_keywords.o`, `lexer_literals.o`, `lexer_state.o`, `token_struct.o`.
6. **Tier 6: Preprocessor**: `include_resolver.o`, `file_reader.o`.
7. **Tier 7: AST**: `ast_node.o`, `ast_storage.o`, `ast_helpers.o`.
8. **Tier 8: Memory**: `arena_allocator.o`, `buffer_contiguous.o`, `paged_storage.o`, `string_interner.o`.
9. **Tier 9: Common**: `constants.o`, `declarations.o`, `str_utils.o`, `list_utils.o`, `path_utils.o`, `error_handler.o`.

### Cyclic Group Resolution
The linker command wraps all modules inside GNU ld / LLVM lld symbol resolution groups:

```bash
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
  -lm -o compiler_dev
```

`-Wl,--start-group` causes the linker to repeatedly iterate over the object files until all cross-module references and cyclic symbols are fully resolved.
