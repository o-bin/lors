# LLVM IR Reference Documentation for Lors Compiler (v6)

This directory contains complete local documentation for LLVM Intermediate Representation (IR), tailored for the architecture and code generation of the Lors v6 self-hosted compiler.

## 1. Official LLVM Web Documentation (Raw Mirrors)
The complete official web documentation from `llvm.org` has been saved in [`original_web/`](original_web/):
- **[LLVM Language Reference Manual (LangRef.html)](original_web/LangRef.html)**: The canonical, exhaustive specification of LLVM IR (~3.0 MB).
- **[Opaque Pointers Migration & Guide (OpaquePointers.html)](original_web/OpaquePointers.html)**: Details on modern `ptr` opaque pointer syntax.
- **[LLVM Programmer's Manual (ProgrammersManual.html)](original_web/ProgrammersManual.html)**: General architectural manual for LLVM tools.
- **Kaleidoscope Tutorials**:
  - [Chapter 3: Code Generation to LLVM IR](original_web/LangImpl03_CodeGen.html)
  - [Chapter 5: Control Flow (If/Then/Else, For loops)](original_web/LangImpl05_ControlFlow.html)
  - [Chapter 7: Mutable Variables & Memory Allocations](original_web/LangImpl07_MutableVars.html)

---

## 2. Structured Reference Guides (Quick Lookup)

1. [Types Specification](types.md)
   - Integer types (`i1`, `i8`, `i32`, `i64`)
   - Floating point (`double`, `float`)
   - Opaque Pointers (`ptr`)
   - Aggregate Types (Structures `%struct.Name`, Arrays `[N x T]`)
   - Function Types and Void

2. [Instruction Set Reference](instructions.md)
   - Terminators: `ret`, `br`, `switch`, `unreachable`
   - Arithmetic: `add`, `sub`, `mul`, `sdiv`, `srem`, `fadd`, `fsub`, `fmul`, `fdiv`
   - Logical & Bitwise: `and`, `or`, `xor`, `shl`, `lshr`, `ashr`
   - Comparisons: `icmp` (`eq`, `ne`, `sgt`, `sge`, `slt`, `sle`), `fcmp` (`oeq`, `one`, `ogt`, `oge`, `olt`, `ole`)
   - Casts & Conversions: `trunc`, `zext`, `sext`, `sitofp`, `fptosi`, `bitcast`, `ptrtoint`, `inttoptr`
   - PHI nodes: `phi`

3. [Memory Model & Addressing](memory.md)
   - Stack Allocation: `alloca`
   - Reading & Writing: `load`, `store`
   - Address Calculation: `getelementptr` (GEP) under opaque pointers
   - Dynamic Memory Management: `malloc`, `free`

4. [Functions, Globals & Linkage](functions_and_globals.md)
   - Global constants: string literals (`@.str = private unnamed_addr constant [N x i8] c"..."`)
   - Global mutable variables
   - Function definitions (`define ... @name(...) { ... }`)
   - External declarations (`declare ... @name(...)`)
   - Linkage types: `private`, `internal`, `linkonce_odr`, `external`

5. [Runtime Support & C Standard Interop](runtime_and_intrinsics.md)
   - Standard I/O: `printf`, `puts`, `snprintf`, `getchar`, `fgets`
   - String manipulation: `strcmp`, `strlen`, `strcpy`, `strcat`
   - Math operations (libm): `sin`, `cos`, `tan`, `sqrt`, `pow`, `fabs`
   - System & OS: `system`, `getenv`, `exit`
