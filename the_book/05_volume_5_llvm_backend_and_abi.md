# Volume V: LLVM Backend, SSA Generation & Native ABI

## Chapter 13: Mapping Lors to LLVM IR: Types, Casts, and Instructions

### 13.1 The LLVM IR Code Generation Architecture

The code generation subsystem (`src/codegen/`) translates high-level Abstract Syntax Tree nodes directly into clean, portable, and valid LLVM Intermediate Representation (IR).

```
Typed AST Nodes
       |
       v
[llvm_module.inc] (Module ID, Data Layout, Triple)
       |
       +---> [llvm_decl_struct.inc]   (Struct definitions)
       |
       +---> [llvm_runtime_decls.inc] (C Lib Declarations: printf, malloc, strlen, etc.)
       |
       +---> [llvm_decl_func.inc]     (Global variables, define / declare algorithms)
       |
       +---> [llvm_runtime_helpers.inc, llvm_runtime_fs.inc, llvm_runtime_seq.inc]
       |
       +---> [llvm_stmt_*.inc]        (Statements: assign, decl, dispatch, flow, io)
       |
       +---> [llvm_expr_*.inc]        (Expressions: array, binary, builtin, calls, construct, dispatch, primary, struct)
       |
       +---> [llvm_entrypoint.inc]    (C @main runtime entrypoint wrapper for genesis())
       |
       +---> [llvm_strings.inc]       (Constant string pool emitter)
       |
       v
LLVM IR String Output (.ll file)
```

---

### 13.2 Type Mapping & Representation

The function `llvm_get_type(tag, tname)` in `src/codegen/llvm_types.inc` establishes the exact mapping between Lors language types and LLVM IR data types:

| Lors Type | Type Tag Constant | LLVM IR Type | x86_64 Register Representation |
| :--- | :---: | :--- | :--- |
| `whole` | `TYPE_WHOLE` (1) | `i64` | 64-bit integer registers (`%rax`, `%rdi`, `%rsi`, etc.) |
| `precise` | `TYPE_PRECISE` (2) | `double` | 64-bit SSE2 floating-point registers (`%xmm0` - `%xmm7`) |
| `series` | `TYPE_SERIES` (3) | `ptr` | 64-bit pointer to null-terminated `i8` array |
| `state` | `TYPE_STATE` (4) | `i1` | 1-bit boolean flag (zero-extended to `i8` on stack) |
| `void` | `TYPE_VOID` (5) | `void` | No return value / no register |
| `sequence<T>` | `TYPE_SEQUENCE` (6) | `ptr` | Pointer to internal sequence buffer structure |
| `<Struct>` | `TYPE_STRUCT` (7) | `ptr` | Pointer to `%struct.<Struct>` record |

---

## Chapter 14: Control Flow Translation: Conditionals, Loops, and Terminal Blocks

### 14.1 Conditionals (`verify ... then ... otherwise ... conclude`)

In `src/codegen/llvm_stmt_flow.inc`, conditional statements are translated into explicit basic block branching:

```llvm
; Source: verify (x > 5) then ... otherwise ... conclude
  %cond = icmp sgt i64 %x, 5
  br i1 %cond, label %then_0, label %else_1

then_0:
  ; Then-block body
  br label %cont_2

else_1:
  ; Else-block body
  br label %cont_2

cont_2:
  ; Merged continuation basic block
```

### 14.2 Loops (`cycle ... do ... conclude`)

Loops are translated into deterministic header-body-exit block sequences:

```llvm
; Source: cycle (i < 10) do ... conclude
  br label %loop_cond_0

loop_cond_0:
  %test = icmp slt i64 %i, 10
  br i1 %test, label %loop_body_1, label %loop_end_2

loop_body_1:
  ; Loop body instructions
  br label %loop_cond_0 ; Back-edge

loop_end_2:
  ; Loop exit continuation block
```

---

## Chapter 15: Struct Layouts, Field GEPs, and Constructor Codegen

### 15.1 Struct Layout Generation (`src/codegen/llvm_decl_struct.inc`)

When a `structure Point { x : precise, y : precise }` is compiled, `cg_emit_struct_definition` emits the LLVM IR struct type definition:

```llvm
%struct.Point = type { double, double }
```

### 15.2 Struct Constructor (`src/codegen/llvm_expr_construct.inc`)

When `Point(1.0, 2.0)` is instantiated:
1. `malloc` allocates the required bytes:
   $$\text{Bytes} = \text{FieldCount} \times 8$$
2. `getelementptr` computes the byte offset for each field:
   ```llvm
   %p = call ptr @malloc(i64 16)
   %gep0 = getelementptr inbounds %struct.Point, ptr %p, i32 0, i32 0
   store double 1.0, ptr %gep0
   %gep1 = getelementptr inbounds %struct.Point, ptr %p, i32 0, i32 1
   store double 2.0, ptr %gep1
   ```
3. Returns the heap pointer `%p`.

---

## Chapter 16: System V x86_64 ABI, Calling Conventions, and Stack Alignments

### 16.1 System V Calling Convention Details

On x86_64 Linux, Clang and LLVM follow the System V ABI:
- First 6 integer/pointer arguments: `%rdi`, `%rsi`, `%rdx`, `%rcx`, `%r8`, `%r9`.
- First 8 floating-point arguments: `%xmm0` through `%xmm7`.
- Additional arguments are passed on the stack.
- Return value: `%rax` for integers/pointers, `%xmm0` for floats.

### 16.2 The Stack Alignment Requirement
The x86_64 ABI requires that the stack pointer `%rsp` be **16-byte aligned** before any `call` instruction.
- If a function prototype is declared with the wrong parameter count or width, the compiler may emit stack pushes or register passes that misalign `%rsp`.
- Misaligned stack pointers cause immediate `SIGSEGV` or `SIGBUS` faults inside standard C library functions (like `printf` or `system`) that use SSE instructions (`movaps`).

---

## Chapter 17: Global Variable Linkage: `internal global`, `common global`, and `global`

### 17.1 The Linker Symbol Problem in Multi-Module Compilers

When 68 separate `.o` files are linked into a single binary, every global variable must declare its exact linkage to avoid two fatal linker errors:
1. `multiple definition of 'symbol'`: Two objects declare the same strong global symbol.
2. `undefined reference to 'symbol'`: An object references a global variable that was not exported.

### 17.2 The Linkage Decision Rules (`src/codegen/llvm_decl_func.inc`)

```
Is Variable a Compiler Constant? (TOK_*, AST_*, TYPE_*)
   |
   +---> YES: Emit 'internal global' (Private to translation unit, zero collisions)
   |
   +---> NO: Does it have an Initial Value? (ast_get_child_count > 0)
            |
            +---> YES: Emit 'global' (Strong definition with initial data)
            |
            +---> NO: Emit 'common global <type> 0, align 8'
                  (ELF Common Symbol: Merges identically across all 68 objects)
```

```llvm
; Example Linkage Emission in Stage 6:
@global_TOK_ALGORITHM = internal global i64 10, align 8
@global_flag_debug = common global i1 false, align 8
@global_shared_str = global ptr @.str.0, align 8
@global_external_var = external global ptr, align 8
```

---

## Chapter 18: Embedded Runtime Helpers: Sequences, String Slicing, and File I/O

The compiler embeds lean C runtime helper implementations directly into the emitted LLVM IR to provide standard language capabilities without requiring an external C runtime library:

1. **`__lors_str_concat(ptr, ptr) -> ptr`**: Allocates a new buffer of size $\text{len}(a) + \text{len}(b) + 1$, copies both strings, and returns the concatenated pointer.
2. **`__lors_substring(ptr, start, len) -> ptr`**: Allocates a buffer of size $\text{len} + 1$, copies the slice, and appends the null terminator `\0`.
3. **`__lors_file_read(ptr) -> ptr`**: Opens a file via `fopen("r")`, seeks to end with `fseek`/`ftell` to determine size, allocates the exact byte buffer, reads via `fread`, appends `\0`, closes the file, and returns the buffer.
4. **`__lors_file_write(ptr, ptr) -> void`**: Opens via `fopen("w")`, writes using `fwrite`, and closes cleanly via `fclose`.
5. **`__lors_seq_create(elem_size, capacity) -> ptr`**: Allocates a sequence header struct:
   ```llvm
   %struct.__lors_seq = type { i64, i64, i64, ptr } ; len, cap, elem_size, data_ptr
   ```
6. **`__lors_seq_push(seq_ptr, elem_ptr) -> void`**: Appends an element, doubling capacity via `realloc` if `len == cap`.
