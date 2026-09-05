# Chapter 8: Guide for Future Maintainers and AI Agents

## 8.1 Introduction for AI Agents and Human Maintainers

This chapter serves as the explicit operational specification and transmission of know-how for future software engineers and AI language models maintaining, extending, or refactoring the Stage 6 (`v6-dv`) compiler.

When modifying this compiler, you are operating on a self-hosting compiler system. A subtle bug in type inference, global linkage, or register width will not merely cause a test failure: it can break the ability of the compiler to rebuild itself.

---

## 8.2 The Golden Invariants (Never Break These)

### Invariant 1: The 150-Line Limit
- **Rule**: No `.inc` file in `src/` may exceed 150 lines of code.
- **Action when approaching limit**: If a module reaches ~140 lines, split it into two coherent sub-modules (e.g., `parse_stmt_flow.inc` and `parse_stmt_io.inc`).
- **Update headers**: Whenever a new module or function is created, its prototype MUST be added to `src/common/declarations.inc`.

### Invariant 2: Type Inference Priority Order
- **Rule**: In `src/semantic/type_checker_calls.inc`, `fn_lookup_ret_tag(fname)` MUST ALWAYS take precedence over fallback heuristics (`infer_builtin_call_type`).
- **Reason**: If heuristics take precedence, functions starting with prefixes like `ast_` or `lexer_` will be falsely inferred as `TYPE_WHOLE` (`i64`) even if declared as `void`, corrupting x86_64 call frames.

### Invariant 3: Global Variable Linkage Classification
In `src/codegen/llvm_decl_func.inc`, global variables must follow exact linkage rules:
1. Compiler constants (`TOK_*`, `AST_*`, `TYPE_*`): Emitted as `internal global`.
2. Initialized module data: Emitted as `global`.
3. Uninitialized shared state: Emitted as `common global` with a zero-initializer (`0`, `0.0`, `null`, `false`).

---

## 8.3 Step-by-Step Guide for Adding New Language Features

Follow this exact 6-step workflow when introducing new syntax, operators, or builtins:

```
Step 1: Define Constants & Tokens (src/common/constants.inc)
        |
Step 2: Update Lexer Scanning (src/lexer/)
        |
Step 3: Update Parser Grammar (src/parser/)
        |
Step 4: Update Semantic Analysis (src/semantic/)
        |
Step 5: Emit LLVM IR Instructions (src/codegen/)
        |
Step 6: Update Declarations & Verify (src/common/declarations.inc)
```

### Detailed Feature Implementation Workflow

1. **Tokens (`src/common/constants.inc`)**:
   - Add new `TOK_<NAME>` constants and `AST_<NAME>` kinds.
2. **Lexer (`src/lexer/`)**:
   - Register keywords in `lexer_keywords.inc` or character scanner rules in `lexer_core.inc`.
3. **Parser (`src/parser/`)**:
   - Add parsing logic in `parse_stmt_*.inc` or `parse_expr_*.inc`. Construct AST nodes using `ast_create_node` and `ast_add_child`.
4. **Semantic Analyzer (`src/semantic/`)**:
   - In `type_checker_expr.inc` or `type_checker_stmt.inc`, deduce types, validate operands, and assign type tags with `ast_set_type`.
5. **Code Generator (`src/codegen/`)**:
   - In `llvm_expr_*.inc` or `llvm_stmt_*.inc`, emit the corresponding LLVM IR instruction (`alloca`, `load`, `store`, `call`, `br`, `icmp`, `fadd`, etc.).
6. **Compile & Self-Host Cycle**:
   - Recompile `compiler.lr` with Stage 5.
   - Run `./build_all_modules.sh && ./link_all_modules.sh`.
   - Run `make test-all`.

---

## 8.4 Diagnostic and Debugging Handbook

### Symptom 1: Compiler Exits Silently with Code 0 or No Output
- **Cause**: Parameter register mismatch or corrupted string pointer passed to `compile_single_file` or `run_backend_compilation`.
- **Remedy**:
  1. Inspect `src/common/declarations.inc` to verify that caller parameter count and types match callee definitions.
  2. Compile with `-s` flag to preserve `.ll` files (`./compiler <file>.inc -o -s`).
  3. Inspect the emitted `call` instruction in the `.ll` file and compare with the `define` signature in the callee `.ll` file.

### Symptom 2: `error: invalid redefinition of function 'foo'`
- **Cause**: Function `foo` is both declared (`declare`) and defined (`define`) in the same `.ll` module, or declared twice.
- **Remedy**: Ensure `llvm_module.inc` and `llvm_decl_func.inc` check `cg_defined_functions` and `cg_declared_functions` before emitting `declare`.

### Symptom 3: `error: 'common' global must have a zero initializer`
- **Cause**: A variable with an initial value was emitted with `common global` linkage instead of `global`.
- **Remedy**: Check `has_init` condition in `cg_emit_global_datum` in `src/codegen/llvm_decl_func.inc`.

### Symptom 4: Linker reports `multiple definition of 'global_TOK_...'`
- **Cause**: Shared constants were emitted with external linkage instead of `internal global`.
- **Remedy**: Ensure `cg_emit_global_datum` marks all `TOK_*`, `AST_*`, and `TYPE_*` symbols with `internal global`.

---

## 8.5 Maintenance Rule Summary for LLMs

If you are an AI model assigned to work on this repository:
1. **Never create monolithic source files**: Respect the 150-line modular design.
2. **Always synchronize `declarations.inc`**: Any new algorithm or global variable must be declared in `src/common/declarations.inc`.
3. **Always run the full test suite**: Validate both `make test` and `make test-dev` after any modification.
4. **Preserve ABI compatibility**: Never alter primitive type representations without updating both semantic checkers and LLVM codegen tables simultaneously.
