# Volume IV: Semantic Analysis, Type Systems & Scope Resolution

## Chapter 10: Multi-Pass Semantic Architecture & Struct Type Registration

### 10.1 Why Multi-Pass Analysis is Required

In a single-pass compiler, functions and data structures can only reference entities that were declared textually before them. This forces awkward forward-declaration gymnastics and prevents mutual recursion between structures or functions.

To grant programmers maximum expressive power, the Stage 6 semantic analyzer (`src/semantic/semantic_analyzer.inc`) executes **3 separate passes** over the Abstract Syntax Tree before any machine code or LLVM IR is generated:

```
+-----------------------------------------------------------------------------------+
| PASS 1: Structure Type Registration (src/semantic/struct_registry.inc)            |
| - Registers all struct type names.                                                |
| - Calculates field offsets, names, types, and byte sizes.                         |
+-----------------------------------------------------------------------------------+
                                         |
                                         v
+-----------------------------------------------------------------------------------+
| PASS 2: Function Signature Indexing (src/semantic/symbol_table.inc)               |
| - Registers all function names, parameter counts, and return types.               |
| - Handles both forward prototypes and full implementations.                       |
+-----------------------------------------------------------------------------------+
                                         |
                                         v
+-----------------------------------------------------------------------------------+
| PASS 3: Scoped Type Checking and Inference (src/semantic/type_checker_*.inc)      |
| - Pushes and pops lexical scope frames.                                           |
| - Resolves identifier types from local symbols and global declarations.           |
| - Enforces static type safety across expressions, assignments, and calls.         |
| - Tags every AST node with its exact concrete type.                               |
+-----------------------------------------------------------------------------------+
```

---

### 10.2 Structure Layout and Field Registry (`src/semantic/struct_registry.inc`)

When a `structure <Name>` declaration is encountered in Pass 1:
1. `struct_register(sname)` creates a new struct descriptor in the registry.
2. For each field declared in the body:
   ```lors
   algorithm struct_add_field(sname : series, fname : series, ftag : whole, ftname : series) -> void
   ```
   - Records the field's identifier `fname`.
   - Records the field's primitive or struct type tag `ftag`.
   - Records the field's full type name `ftname` (e.g., `"series"`, `"whole"`, `"Point"`).
   - Assigns a sequential 0-based field index ($0, 1, 2, \dots, F-1$).

#### Struct Inspection API:
- `struct_lookup(sname)`: Returns the integer ID of the struct, or `-1` if not found.
- `struct_get_field_count(sname)`: Returns the number of fields in the struct.
- `struct_get_field_type(sname, fname)`: Returns the type tag of the field.
- `struct_get_field_type_name(sname, fname)`: Returns the string type name of the field.
- `struct_get_field_index(sname, fname)`: Returns the 0-based index for LLVM `getelementptr`.

---

## Chapter 11: Lexical Scope Stacks, Shadowing, and Symbol Lookup

### 11.1 Scoped Symbol Table Architecture (`src/semantic/symbol_table.inc`)

Lexical scoping allows inner statement blocks (inside `verify`, `cycle`, or `algorithm`) to declare local variables that shadow variables in outer scopes without affecting the outer variables' values.

The symbol table uses parallel flat arrays with scope depth markers:

```lors
datum sym_names_data : series;
datum sym_tags_data : series;
datum sym_tnames_data : series;
datum sym_scopes_data : series;
datum sym_count : whole = 0;
datum sym_current_scope : whole = 0;
```

---

### 11.2 Scope Entry and Exit Mechanics

```
Scope Level 0 (Global Scope):
  [0] flag_debug : state (Scope 0)
  [1] cli_input_file : series (Scope 0)

Scope Level 1 (Function genesis()):
  sym_enter_scope() -> sym_current_scope = 1
  [2] count : whole (Scope 1)

Scope Level 2 (Nested verify block):
  sym_enter_scope() -> sym_current_scope = 2
  [3] count : series (Scope 2) -> Shadows [2]!

  sym_lookup_var("count") -> Returns [3] (series)

  sym_exit_scope() -> Prunes all entries with Scope == 2
  sym_count shrinks back to 3

Scope Level 1 Restored:
  sym_lookup_var("count") -> Returns [2] (whole)
```

#### The Backwards Search Rule:
When `sym_lookup_var(name)` is called, it searches **backwards** from index `sym_count - 1` down to `0`:
```lors
algorithm sym_lookup_var(name : series) -> whole
begin
    datum i : whole = sym_count - 1;
    cycle (i >= 0) do
        datum n : series = str_list_get(sym_names_data, i);
        verify (n == name) then
            result i;
        conclude
        i = i - 1;
    conclude
    result -1;
end
```
Because it searches from the top of the stack downwards, it naturally discovers the most deeply nested shadowed symbol first.

---

## Chapter 12: The Critical Type Inference Engine and Call Resolution Hierarchy

### 12.1 The Case of the Misinferred Return Type (The Historic Bug)

During the development of Stage 6, a subtle and elusive bug emerged that prevented the modular compiler from executing:
- Single-module compilation succeeded ($68/68$ passed).
- Object linking succeeded (`compiler_dev` generated).
- However, when executing `./compiler_dev examples/hello.lr`, the compiler terminated without writing output.

#### The Root Cause Investigation:
In `compile_pipeline.inc`, the compiler called:
```lors
ast_init();
lexer_tokenize();
```
In `declarations.inc`, these functions were declared as returning `void`:
```lors
algorithm ast_init() -> void;
algorithm lexer_tokenize() -> void;
```
However, in `type_checker_calls.inc`, the function type inference engine evaluated:
```lors
// DANGEROUS OLD IMPLEMENTATION:
datum b_tag : whole = infer_builtin_call_type(fname, node_id);
verify (b_tag != TYPE_UNKNOWN) then
    result b_tag;
conclude
```
Inside `infer_builtin_call_type`:
```lors
verify (str_starts_with(fname, "ast_") or str_starts_with(fname, "lexer_")) then
    ast_set_type(node_id, TYPE_WHOLE, "whole");
    result TYPE_WHOLE;
conclude
```
Because the name-prefix heuristics ran **before** checking the symbol table:
1. The compiler saw `ast_init`, matched the `"ast_"` prefix, and inferred that `ast_init` returned `TYPE_WHOLE` (`i64`).
2. In `compile_pipeline.ll`, it emitted `%t72 = call i64 @ast_init()`.
3. But in `ast_storage.ll`, `ast_init` was defined as `define void @ast_init()`.
4. When Clang compiled and linked these objects on x86_64:
   - Calling a `void` function as `i64` reads the uninitialized `%rax` return register.
   - The ABI mismatch corrupted the stack pointer alignment of the caller (`compile_single_file`), causing the subsequent string pointer argument `input_file` to be read from a misaligned stack offset.
   - `path_is_safe` received a corrupted pointer and exited silently.

---

### 12.2 The Canonical Call Resolution Hierarchy

To permanently resolve this hazard, Stage 6 established the **Canonical 3-Tier Call Resolution Hierarchy** in `src/semantic/type_checker_calls.inc`:

```lors
algorithm infer_call_type(node_id : whole) -> whole
begin
    datum fname : series = ast_get_s_val(node_id);
    datum arg_cnt : whole = ast_get_child_count(node_id);
    datum a_i : whole = 0;
    cycle (a_i < arg_cnt) do
        infer_expr_type(ast_get_child(node_id, a_i));
        a_i = a_i + 1;
    conclude

    // TIER 1: Struct Constructor Check
    verify (struct_lookup(fname) != -1) then
        ast_set_type(node_id, TYPE_STRUCT, fname);
        ast_set_n_val(node_id, 1);
        result TYPE_STRUCT;
    conclude

    // TIER 2: User-Defined Functions & Header Declarations
    // MUST PREVENT HEURISTIC SHADOWING!
    datum user_tag : whole = fn_lookup_ret_tag(fname);
    verify (user_tag != TYPE_UNKNOWN) then
        datum user_tname : series = fn_lookup_ret_name(fname);
        ast_set_type(node_id, user_tag, user_tname);
        result user_tag;
    conclude

    // TIER 3: Built-in Primitives and Fallback Heuristics
    datum b_tag : whole = infer_builtin_call_type(fname, node_id);
    verify (b_tag != TYPE_UNKNOWN) then
        result b_tag;
    conclude

    ast_set_type(node_id, TYPE_UNKNOWN, "unknown");
    result TYPE_UNKNOWN;
end
```

#### The Invariant Rule:
**Explicit user declarations and header signatures in `declarations.inc` ALWAYS supersede name-prefix heuristics.**
