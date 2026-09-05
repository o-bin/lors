# Chapter 5: LLVM Backend and Code Generation

## 5.1 The LLVM IR Code Generation Architecture

The code generation subsystem (`src/codegen/`) converts validated AST nodes into standard, optimizable LLVM Intermediate Representation (IR).

```
Typed AST Nodes
       |
       v
[llvm_module.inc] (Module ID, Data Layout, Triple)
       |
       +---> [llvm_decl_struct.inc]   (%struct.<name> = type { ... })
       |
       +---> [llvm_runtime_decls.inc] (printf, malloc, strlen, etc.)
       |
       +---> [llvm_decl_func.inc]     (Global data, function defines/declares)
       |
       +---> [llvm_runtime_helpers.inc, llvm_runtime_fs.inc, llvm_runtime_seq.inc]
       |
       +---> [llvm_stmt_*.inc, llvm_expr_*.inc] (SSA instructions)
       |
       +---> [llvm_entrypoint.inc]    (C @main wrapper for genesis())
       |
       +---> [llvm_strings.inc]       (Constant string pool)
       |
       v
LLVM IR String (.ll file)
```

---

## 5.2 Type Mapping Table

Lors high-level types map to LLVM IR primitive types as follows:

| Lors Type | LLVM IR Type | x86_64 Register / Representation |
| :--- | :--- | :--- |
| `whole` | `i64` | 64-bit general-purpose register (`%rax`, `%rdi`, etc.) |
| `precise` | `double` | 64-bit SSE/AVX register (`%xmm0`, `%xmm1`, etc.) |
| `series` | `ptr` | 64-bit pointer to null-terminated UTF-8 / ASCII string |
| `state` | `i1` | 1-bit boolean flag (zero-extended to `i8` on stack/heap) |
| `void` | `void` | No return register used |
| `sequence<T>` | `ptr` | Pointer to internal sequence descriptor structure |
| `struct S` | `ptr` / `%struct.S*` | Pointer to contiguous heap/stack-allocated memory block |

---

## 5.3 Control Flow and SSA Translation

LLVM IR requires Static Single Assignment (SSA) form. Rather than constructing complex $\phi$ (phi) nodes for mutable variables, the Lors compiler adopts the canonical compiler design pattern:

1. **Stack Slot Allocation**: Every variable and parameter is allocated a local stack slot using `alloca` in the function's entry basic block.
2. **Loads and Stores**:
   - Variable reads emit `load <type>, ptr %var_<name>`.
   - Variable assignments emit `store <type> %val, ptr %var_<name>`.
3. **Clang / LLVM `mem2reg` Optimization**: The LLVM backend optimization pipeline automatically promotes these `alloca` memory locations into hardware registers and optimal SSA $\phi$ nodes.

### Conditional Branching Pattern (`src/codegen/llvm_stmt_flow.inc`)
For `verify (cond) then ... otherwise ... conclude`:
```llvm
  ; 1. Evaluate condition
  %cond_val = ... ; i1
  br i1 %cond_val, label %then_0, label %else_1

then_0:
  ; Then block statements...
  br label %cont_2

else_1:
  ; Else block statements...
  br label %cont_2

cont_2:
  ; Merged continuation block
```

### Deterministic Loop Pattern (`src/codegen/llvm_stmt_flow.inc`)
For `cycle (cond) do ... conclude`:
```llvm
  br label %loop_cond_0

loop_cond_0:
  ; Evaluate condition
  %loop_test = ... ; i1
  br i1 %loop_test, label %loop_body_1, label %loop_end_2

loop_body_1:
  ; Loop body statements...
  br label %loop_cond_0

loop_end_2:
  ; Continuation block
```

---

## 5.4 Global Variable Linkage Rules

In multi-object modular compilation, global variables must be emitted with correct linkage types in LLVM IR:

1. **`internal global`**:
   - Used for compiler constants (`TOK_*`, `AST_*`, `TYPE_*`).
   - Private to the compilation unit. Prevents duplicate symbol collisions when linking 68 objects.
2. **`common global`**:
   - Used for shared uninitialized variables (`@global_flag_debug`, `@global_parse_pos`).
   - Merges identical symbol definitions across all translation units into a single canonical address at link time.
3. **`global`**:
   - Used for initialized module-specific data segments.
4. **`external global`**:
   - Emitted when a module accesses a global variable defined in another translation unit.
