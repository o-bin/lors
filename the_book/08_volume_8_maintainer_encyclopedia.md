# Volume VIII: The Maintainer's Encyclopedia & AI Agent Transmission

## Chapter 24: The Golden Invariants: Architectural Laws

### 24.1 Non-Negotiable Engineering Laws

When modifying or expanding the Stage 6 compiler, future maintainers (both human engineers and AI models) MUST uphold three inviolable laws:

```
+-----------------------------------------------------------------------------------+
| THE THREE LAWS OF LORS STAGE 6                                                    |
+-----------------------------------------------------------------------------------+
| LAW 1: The 150-Line Physical Limit per Source File                                |
|        No .inc file may exceed 150 physical lines under any circumstances.        |
+-----------------------------------------------------------------------------------+
| LAW 2: Explicit Signature Precedence                                              |
|        fn_lookup_ret_tag() MUST ALWAYS execute before fallback name heuristics.   |
+-----------------------------------------------------------------------------------+
| LAW 3: Exact Global Linkage Typing                                                |
|        Uninitialized = 'common global', Constants = 'internal global'.            |
+-----------------------------------------------------------------------------------+
```

---

## Chapter 25: Case Studies in Debugging: Every Major Bug, Failure Mode, and Resolution

### Case Study 1: The Double Forward Declaration Collision

#### Symptom:
Clang reported during `build_all_modules.sh`:
```
src/driver/compile_pipeline.ll:869:12: error: invalid redefinition of function 'path_is_safe'
  869 | declare i1 @path_is_safe(ptr)
```

#### Investigation:
In `llvm_module.inc`, Step 5 scanned all `AST_ALGORITHM_DECL` nodes and emitted `declare i1 @path_is_safe(ptr)` from `declarations.inc`. Later, in Step 6, `cg_emit_external_globals()` and `cg_expr_calls.inc` emitted `cg_external_decls`, which ALSO contained `declare i1 @path_is_safe(ptr)`.
In LLVM IR, emitting duplicate `declare` statements for the same symbol in a single translation unit is an error.

#### Resolution:
`src/codegen/llvm_env.inc` was updated to introduce `cg_declared_functions : series;`. Both `cg_emit_algorithm` and `cg_expr_calls` now record every declared symbol into `cg_declared_functions` and check `str_contains(cg_declared_functions, ";" + fn_name + ";") == false` before emitting any `declare` statement.

---

### Case Study 2: The LLVM `common` Linkage Zero-Initializer Requirement

#### Symptom:
Clang reported during `make test`:
```
error: invalid LLVM IR input: 'common' global must have a zero initializer!
ptr @global_shared_val
```

#### Investigation:
In `llvm_decl_func.inc`, global variables were unconditionally emitted with `common global` linkage. However, in `test_inc_a.lr`, a global variable was initialized with a string literal:
```lors
datum shared_val : series = "from_a";
```
In LLVM IR specification, `common` linkage is strictly reserved for uninitialized BSS symbols and MUST have a zero initializer (`null`, `0`, `0.0`, `false`). If a variable has an initial value, it must be emitted as regular `global`.

#### Resolution:
In `src/codegen/llvm_decl_func.inc`:
```lors
    datum linkage : series = "common global ";
    verify (str_starts_with(vname, "TOK_") or str_starts_with(vname, "AST_") or str_starts_with(vname, "TYPE_")) then
        linkage = "internal global ";
    otherwise
        verify (has_init) then
            linkage = "global ";
        conclude
    conclude
```

---

### Case Study 3: Multiple Definition of Local Variable in Codegen

#### Symptom:
When compiling `compiler.lr` with `-debug`:
```
compiler.ll:15680:5: error: multiple definition of local value named 'param_node'
 15680 |     %param_node = alloca i64
```

#### Investigation:
In `src/codegen/llvm_decl_func.inc`, `cg_emit_algorithm` contained two distinct loops:
- Loop 1: Counting parameter signatures.
- Loop 2: Allocating stack slots for parameters.
Both loops declared `datum param_node : whole = ast_get_child(...)` in the same algorithm body. In Lors, declaring a variable with the same name twice in the same scope emits two duplicate `alloca %param_node` instructions in LLVM IR.

#### Resolution:
`datum param_node : whole = 0;` was hoisted to the function header and reused across both loops.

---

## Chapter 26: The AI Agent's Playbook: How Future LLMs Must Modify This Compiler

If you are an AI assistant tasked with modifying, refactoring, or fixing this compiler:

1. **Rule of File Modularity**:
   - Never combine `.inc` files to make your edits "easier".
   - If you need to add more than 20 lines to an existing file that is already at 135 lines, create a new sub-module (e.g., `src/parser/parse_expr_ternary.inc`), register its prototype in `src/common/declarations.inc`, add it to `link_all_modules.sh`, and include it in `src/parser/parse_expr_dispatch.inc`.

2. **Rule of Header Synchronization**:
   - Every algorithm function in Lors must have its exact prototype in `src/common/declarations.inc`.
   - If you change a function's parameter count or return type, you MUST update `src/common/declarations.inc` at the exact same moment.

3. **Rule of Verification**:
   - Never finish a task without running:
     ```bash
     ./build_all_modules.sh && ./link_all_modules.sh && make -f Makefile_dev test-all
     ```
   - All 68 modules must compile ($68/68$).
   - All 124 tests must pass ($100\%$).

---

## Chapter 27: Extending the Compiler: Adding Language Features Step-by-Step

Follow this exact sequential recipe to implement a new language feature:

```
[1. Constants]  -> Add TOK_* and AST_* to src/common/constants.inc
       |
[2. Lexer]      -> Add keyword/symbol to src/lexer/lexer_keywords.inc or lexer_core.inc
       |
[3. Parser]     -> Add parsing rule in src/parser/ and construct AST node
       |
[4. Semantic]   -> Validate operand types in src/semantic/type_checker_*.inc
       |
[5. Codegen]    -> Emit LLVM IR in src/codegen/llvm_stmt_*.inc or llvm_expr_*.inc
       |
[6. Header]     -> Add prototypes to src/common/declarations.inc
       |
[7. Bootstrap]  -> Rebuild with Stage 5, build all modules, link compiler_dev, run test-all
```
