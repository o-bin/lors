# Chapter 4: Semantic Analysis and Type Systems

## 4.1 Multi-Pass Semantic Pipeline

The semantic analyzer (`src/semantic/semantic_analyzer.inc`) traverses the Abstract Syntax Tree to enforce static type safety, resolve symbol scopes, compute struct layouts, and assign exact type tags to every expression node before code generation begins.

```
AST Root
   |
   +--> Pass 1: Structure Registration & Field Offsets (src/semantic/struct_registry.inc)
   |
   +--> Pass 2: Algorithm Signatures & Return Types (src/semantic/symbol_table.inc)
   |
   +--> Pass 3: Statement & Expression Type Validation (src/semantic/type_checker_*.inc)
```

### Pass 1: Structure Registration
Before analyzing statements or function bodies, all `structure` declarations in the AST are scanned:
1. `struct_register(sname)` creates a struct record.
2. For each field, `struct_add_field(sname, fname, ftag, ftname)` records its name, type tag, type name string, and 0-based field index.
3. This allows recursive structures and forward references between struct types without ordering constraints.

### Pass 2: Algorithm Signatures
All function declarations (`AST_ALGORITHM_DECL`) are registered in the global function table:
1. Extracts `fn_name`, return type tag (`ret_tag`), return type name (`ret_tname`), and parameter count (`p_cnt`).
2. Calls `fn_register(fn_name, ret_tag, ret_tname, p_cnt)`.
3. Handles both forward declarations (`algorithm foo(...) -> void;` without bodies) and concrete implementations with bodies.

### Pass 3: Scoped Type Checking
The analyzer walks function bodies and global statements:
1. `sym_enter_scope()` pushes a new lexical scope.
2. Formal parameters are registered in the local symbol table with `sym_add_var(pname, ptag, ptname)`.
3. Statements are validated with `type_check_stmt(node)`.
4. `sym_exit_scope()` pops the scope upon leaving the block.

---

## 4.2 Symbol Tables and Lexical Scopes

The symbol table (`src/semantic/symbol_table.inc`) tracks variables across nested block levels using a parallel SoA model:

- `sym_names_data`: Variable identifier strings.
- `sym_tags_data`: Type tag integers (`TYPE_WHOLE`, `TYPE_SERIES`, `TYPE_STRUCT`, etc.).
- `sym_tnames_data`: Type name strings (`"whole"`, `"precise"`, `"Point"`, `"sequence<whole>"`).
- `sym_scopes_data`: Scope level integer at which the symbol was declared.

### Scope Operations
- **`sym_enter_scope()`**: Increments `sym_current_scope`.
- **`sym_exit_scope()`**: Iterates backwards from `sym_count - 1`, pruning all variables belonging to `sym_current_scope`, and decrements `sym_current_scope`.
- **`sym_lookup_var(name)`**: Scans backwards from innermost scope (`sym_count - 1`) to 0, ensuring proper variable shadowing rules.

---

## 4.3 Type Inference Rules and Order of Precedence

The core rule for expression type inference is implemented in `src/semantic/type_checker_calls.inc` and `src/semantic/type_checker_expr.inc`.

### The Function Call Resolution Hierarchy
When analyzing a call `foo(...)`:

```
                       infer_call_type(node_id)
                                  |
            +---------------------+---------------------+
            |                                           |
 1. Is it a Struct Constructor?             2. Is it in Function Table?
    (struct_lookup(fname) != -1)               (fn_lookup_ret_tag(fname) != TYPE_UNKNOWN)
            |                                           |
    Return TYPE_STRUCT                          Return user/header defined type
                                                        |
                                            3. Is it a Builtin or Heuristic?
                                               (infer_builtin_call_type(fname, node_id))
```

### Critical Resolution Invariant
**Rule**: User declarations and header prototypes (`fn_lookup_ret_tag`) MUST ALWAYS take precedence over fallback prefix heuristics.
- If a function is declared as `algorithm ast_init() -> void;`, `fn_lookup_ret_tag("ast_init")` returns `TYPE_VOID`.
- If the compiler checked name prefix heuristics first, `"ast_"` would mistakenly infer `TYPE_WHOLE` (`i64`), causing calling convention mismatches and corrupted stack frames in generated assembly.

---

## 4.4 Structure Layout and Field Type Deduction

When member access `obj.field` (`AST_MEMBER`) is encountered:
1. `infer_expr_type(base_node)` determines the type of `base_node`.
2. The struct name `sname` is retrieved from `ast_get_type_name(base_node)` or `sym_get_var_type_name(base_var)`.
3. `struct_get_field_type(sname, fname)` retrieves the exact field type.
4. `struct_get_field_index(sname, fname)` provides the 0-based field index used by LLVM `getelementptr`.
