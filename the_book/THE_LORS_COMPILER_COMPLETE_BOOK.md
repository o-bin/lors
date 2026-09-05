# The Lors Compiler Architecture and Self-Hosting Guide (Stage 6)
**A Comprehensive Technical Specification and Historical Handbook of the Stage 6 LLVM Self-Hosted Modular Compiler**

---

# Table of Contents
1. [Chapter 1: Introduction and Architecture](#chapter-1-introduction-and-architectural-foundation)
2. [Chapter 2: Memory Management and Data Structures](#chapter-2-memory-management-and-data-structures)
3. [Chapter 3: Frontend: Preprocessor, Lexer, AST and Parser](#chapter-3-frontend-preprocessor-lexer-ast-and-parser)
4. [Chapter 4: Semantic Analysis and Type Systems](#chapter-4-semantic-analysis-and-type-systems)
5. [Chapter 5: LLVM Backend and Code Generation](#chapter-5-llvm-backend-and-code-generation)
6. [Chapter 6: Multi-Object Modular Linking and ABI](#chapter-6-multi-object-modular-linking-and-abi)
7. [Chapter 7: The Infinite Bootstrap and Self-Hosting Loop](#chapter-7-the-infinite-bootstrap-and-self-hosting-loop)
8. [Chapter 8: Guide for Future Maintainers and AI Agents](#chapter-8-guide-for-future-maintainers-and-ai-agents)

---

# Chapter 1: Introduction and Architectural Foundation

## 1.1 The Lors Programming Language

Lors is a statically-typed, imperative programming language designed for deterministic execution, high performance, and explicit architectural transparency. It features a unique syntax tailored for clarity and formal algorithm specification:

- **Syntax Keywords**:
  - `algorithm <name>(<params>) -> <return_type>`: Defines a function or procedure.
  - `datum <name> : <type> = <value>;`: Declares a variable with an explicit type annotation.
  - `verify (<condition>) then ... otherwise ... conclude`: Structured conditional branching.
  - `cycle (<condition>) do ... conclude`: Deterministic loop constructs.
  - `result <value>;`: Returns a value from an algorithm.
  - `reveal(<expression>);`: Formatted output to standard output stream.
  - `structure <name> ... conclude`: User-defined compound data structures.
  - `incorporate "<filepath>";`: Modular file inclusion and preprocessor directive.

- **Primitive and Composite Types**:
  - `whole`: 64-bit signed integer (`i64` in LLVM IR).
  - `precise`: 64-bit IEEE 754 floating-point number (`double` in LLVM IR).
  - `series`: Null-terminated string / byte pointer (`ptr` in LLVM IR).
  - `state`: Boolean boolean truth value (`i1` in LLVM IR, represented as `true` or `false`).
  - `void`: Absence of return value.
  - `sequence<T>`: Dynamic homogenous array of element type `T`.
  - `struct`: User-defined records containing typed fields.

## 1.2 The Evolution: From Stage 5 to Stage 6

The Lors compiler pipeline is organized into distinct evolutionary stages:

```
[Stage 4 (Legacy)] ---> [Stage 5 (Monolithic Self-Hosted)] ---> [Stage 6 (Modular LLVM Self-Hosted)]
```

### The Limitations of Stage 5
Stage 5 was a monolithic self-hosted compiler. It contained the entire compiler implementation within single or loosely connected source files exceeding thousands of lines. While functional, Stage 5 suffered from:
1. Massive symbol collisions during compilation.
2. Inability to compile modules independently to separate `.o` object files.
3. Lack of strict type verification across compilation boundaries.
4. Hard limits on codebase growth due to compiler parsing constraints.

### The Stage 6 Mission
Stage 6 (`v6-dv`) was engineered to solve these architectural limitations by implementing:
1. **Strict 150-Line Limit**: Every single implementation file (`.inc`) must not exceed 150 physical lines of code.
2. **Layered Separation of Concerns**: Partitioning the compiler into 9 discrete, unidirectional layers.
3. **Independent Compilation**: Every `.inc` module must be compilable into a standalone `.o` ELF object file.
4. **Topological Multi-Object Linking**: Linking all 68 object files into a single binary (`compiler_dev`) using cyclic symbol resolution.
5. **Infinite Bootstrap Capability**: Enabling `compiler_dev` to compile Stage 6 itself, producing Generation 1, Generation 2, and beyond without external dependencies.

## 1.3 The Nine Architectural Layers

The Stage 6 compiler codebase is divided into 9 hierarchical layers:

1. **Common Layer (`src/common/`)**:
   - `constants.inc`: Global token tags, AST node kinds, and type identifiers.
   - `declarations.inc`: Central interface prototypes and shared global state declarations.
   - `str_utils.inc`: String searching, prefixes, suffixes, character classification.
   - `list_utils.inc`: Dynamic string and integer list serialization.
   - `path_utils.inc`: Path normalization, directory extraction, security safety checks.
   - `error_handler.inc`: Formatted error reporting with line/column diagnostic output.

2. **Memory Layer (`src/memory/`)**:
   - `arena_allocator.inc`: Monotonic contiguous memory pool allocation.
   - `buffer_contiguous.inc`: Flat byte/integer array storage.
   - `paged_storage.inc`: Chunked 2D string and integer table storage to prevent reallocations.
   - `string_interner.inc`: FNV-1a hash table for deduplicated string storage.

3. **AST Layer (`src/ast/`)**:
   - `ast_node.inc`: Node creation and child linking.
   - `ast_storage.inc`: Structure-of-Arrays (SoA) storage for AST node fields.
   - `ast_helpers.inc`: Node inspection, traversal, and type tagging utilities.

4. **Preprocessor Layer (`src/preprocessor/`)**:
   - `file_reader.inc`: Direct POSIX file read/write bindings.
   - `include_resolver.inc`: Recursive `incorporate` resolution with visited path tracking to prevent circular loops.

5. **Lexer Layer (`src/lexer/`)**:
   - `token_struct.inc`: Token array storage (types, values, line numbers, column numbers).
   - `lexer_state.inc`: Source buffer tracking and cursor advancement.
   - `lexer_keywords.inc`: Keyword matching and token classification.
   - `lexer_literals.inc`: Numerical, string, and identifier scanning.
   - `lexer_core.inc`: Primary scanning loop dispatching character classes.

6. **Parser Layer (`src/parser/`)**:
   - `parser_state.inc`: Token lookahead, peek, advance, match, and expect helpers.
   - `parse_type.inc`: Type specifier parser for primitives, structs, and `sequence<T>`.
   - `parse_struct.inc`: Record definitions and field declarations.
   - `parse_algorithm.inc`: Function signatures, parameters, and return types.
   - `parse_stmt_*.inc`: Statement parsers (declarations, assignments, flow, I/O).
   - `parse_expr_*.inc`: Expression parsers (precedence climbing, binary, unary, postfix, primary).
   - `parse_program.inc`: Top-level compilation unit entry point.

7. **Semantic Analysis Layer (`src/semantic/`)**:
   - `symbol_table.inc`: Lexical scope stack and symbol resolution.
   - `struct_registry.inc`: Struct definitions, field types, and member offsets.
   - `type_checker_expr.inc`: Bottom-up expression type checking and inference.
   - `type_checker_stmt.inc`: Statement type validation.
   - `type_checker_calls.inc`: Function call signature matching and return type resolution.
   - `semantic_analyzer.inc`: Multi-pass semantic analysis pipeline.

8. **Code Generation Layer (`src/codegen/`)**:
   - `llvm_types.inc`: Mapping Lors types to LLVM IR type signatures.
   - `llvm_env.inc`: Register allocation (`%t0`, `%t1`), labels, and symbol addresses.
   - `llvm_strings.inc`: Constant string pool deduplication and character escaping.
   - `llvm_emitter.inc`: String buffer accumulation for the output `.ll` module.
   - `llvm_decl_struct.inc`: LLVM IR `%struct.<name> = type { ... }` emission.
   - `llvm_decl_func.inc`: Function definitions (`define`) and global variables.
   - `llvm_stmt_*.inc`: Statement code generators (control flow, assignments, I/O).
   - `llvm_expr_*.inc`: Expression code generators (arithmetic, comparisons, calls, accessors).
   - `llvm_runtime_*.inc`: Embedded runtime helpers for strings, sequences, and filesystem.
   - `llvm_entrypoint.inc`: C `@main` runtime wrapper invoking Lors `genesis()`.
   - `llvm_module.inc`: Top-level code generation driver producing complete `.ll` modules.

9. **Driver Layer (`src/driver/`)**:
   - `cli_options.inc`: Command-line flag parsing (`-o`, `-debug`, `-d`, `-s`, `-oall`, `-iall`).
   - `compile_pipeline.inc`: Single-file pipeline orchestrating preprocessing, lexing, parsing, semantic checking, LLVM emission, and Clang backend invocation.
   - `batch_compiler.inc`: Multi-file batch compilation and linking.
   - `main_driver.inc`: Application entry point `genesis()`.

## 1.4 The 150-Line Architectural Invariant

A strict design constraint in Stage 6 is that **no file may exceed 150 lines of code**.

### Rationale and Benefits
1. **Cognitive Load Reduction**: Each file handles one distinct, well-defined algorithmic task.
2. **Context Window Optimization**: Small modular files allow AI coding assistants and human developers to read and modify components without context saturation.
3. **True Modularity**: Forces developers to avoid monolithic anti-patterns and maintain clean decoupled interfaces.
4. **Independent Verifiability**: Enables automated linters and build scripts to compile and verify every sub-system in isolation.

---

# Chapter 2: Memory Management and Data Structures

## 2.1 Memory Model in a Self-Hosted Compiler

Building a self-hosted compiler in a language that does not expose explicit raw pointer arithmetic requires structured abstractions. The Lors compiler runtime uses a hybrid memory management model combining:

1. **Stack Allocation (`alloca` in LLVM IR)**: For all local variables, parameters, and temporary calculation slots.
2. **Global Segment Storage**: For compiler state, symbol tables, token streams, and AST nodes.
3. **Monotonic Arenas and Contiguous Buffers**: For dynamic text generation, string interning, and sequence management.

## 2.2 Structure-of-Arrays (SoA) Storage

To maintain extreme cache locality and avoid complex object allocators, the compiler uses **Structure-of-Arrays (SoA)** rather than Array-of-Structures (AoS).

### The AST Storage Model
An AST node in Lors is represented by an integer ID (`whole`). The node's properties are distributed across parallel dynamic arrays managed in `src/ast/ast_storage.inc`:

- `ast_kinds_data`: AST node kind tags (`AST_BINOP`, `AST_IDENT`, `AST_CALL`, etc.).
- `ast_s_vals_data`: String identifiers, operators, and literals.
- `ast_n_vals_data`: Integer values, parameter counts, or flag values.
- `ast_type_tags_data`: Type tags deduced by semantic analysis.
- `ast_type_names_data`: String representations of types.
- `ast_lines_data`: 1-based source code line numbers.
- `ast_children_ptrs_data`: Comma-separated list of child node indices.

## 2.3 List Serialization and Paged Storage

### List Serialization Format (`src/common/list_utils.inc`)
String and integer lists are serialized using structured delimiters:
- **String List**: Elements separated by semicolons (`;`).
- **List Helpers**: `str_list_add`, `str_list_get`, `str_list_set`, `int_list_add`, `int_list_get`, `int_list_set`.

### Paged Table Storage (`src/memory/paged_storage.inc`)
Virtual paging chunks 2D arrays to prevent reallocation overhead:
$$\text{Page Index} = \lfloor \text{Logical Index} / \text{Page Capacity} \rfloor$$
$$\text{Offset in Page} = \text{Logical Index} \pmod{\text{Page Capacity}}$$

## 2.4 String Interning and Hash Tables

The string interner (`src/memory/string_interner.inc`) deduplicates identifiers and literal strings across the compiler using the 64-bit FNV-1a hash function.

---

# Chapter 3: Frontend: Preprocessor, Lexer, AST and Parser

## 3.1 Preprocessor Architecture and Include Resolution

The Lors preprocessor (`src/preprocessor/`) resolves `incorporate "<filepath>";` directives recursively before lexical analysis begins, using a visited set (`inc_visited_str`) to eliminate circular dependencies.

## 3.2 Lexer Architecture and State Machine

The lexer (`src/lexer/`) transforms raw character streams into a contiguous array of tokens stored in parallel arrays (`tok_types_data`, `tok_vals_data`, `tok_lines_data`, `tok_cols_data`).

## 3.3 Parser Architecture: Recursive Descent Engine

The parser (`src/parser/`) constructs the AST using recursive descent with single-token lookahead ($LL(1)$), strictly enforcing operator precedence through dedicated expression sub-parsers.

---

# Chapter 4: Semantic Analysis and Type Systems

## 4.1 Multi-Pass Semantic Pipeline

The semantic analyzer (`src/semantic/semantic_analyzer.inc`) traverses the Abstract Syntax Tree in three passes:
1. **Pass 1: Structure Registration**: Records struct names and field offsets.
2. **Pass 2: Algorithm Signatures**: Records function return types and parameter counts.
3. **Pass 3: Scoped Type Checking**: Validates statement blocks, local variables, and expressions.

## 4.2 Symbol Tables and Lexical Scopes

The symbol table (`src/semantic/symbol_table.inc`) tracks variables across nested block levels using a parallel SoA model with backwards scanning for shadowing resolution.

## 4.3 Type Inference Rules and Order of Precedence

**Critical Invariant**: In `src/semantic/type_checker_calls.inc`, user function declarations and header prototypes (`fn_lookup_ret_tag`) MUST ALWAYS take precedence over fallback prefix heuristics.

---

# Chapter 5: LLVM Backend and Code Generation

## 5.1 The LLVM IR Code Generation Architecture

The code generation subsystem (`src/codegen/`) converts validated AST nodes into standard, optimizable LLVM Intermediate Representation (IR).

## 5.2 Type Mapping Table

| Lors Type | LLVM IR Type | x86_64 Register / Representation |
| :--- | :--- | :--- |
| `whole` | `i64` | 64-bit general-purpose register (`%rax`, `%rdi`, etc.) |
| `precise` | `double` | 64-bit SSE/AVX register (`%xmm0`, `%xmm1`, etc.) |
| `series` | `ptr` | 64-bit pointer to null-terminated UTF-8 / ASCII string |
| `state` | `i1` | 1-bit boolean flag |
| `void` | `void` | No return register used |
| `sequence<T>` | `ptr` | Pointer to internal sequence descriptor structure |
| `struct S` | `ptr` / `%struct.S*` | Pointer to contiguous heap/stack-allocated memory block |

## 5.3 Control Flow and SSA Translation

Mutable variables are allocated stack slots via `alloca`, read via `load`, and updated via `store`. LLVM's `mem2reg` pass optimizes these into hardware registers and SSA phi nodes automatically.

## 5.4 Global Variable Linkage Rules

1. `internal global`: Private to the module (used for `TOK_*`, `AST_*`, `TYPE_*` constants).
2. `common global`: Merged across compilation units with zero initializer (used for shared state).
3. `global`: Used for initialized module data.
4. `external global`: Forward reference to global state in another object.

---

# Chapter 6: Multi-Object Modular Linking and ABI

## 6.1 The Challenge of Native Multi-Object Linking

In multi-object modular compilation, each `.inc` is compiled in isolation. Calling conventions across x86_64 require exact argument types and counts to prevent register and stack corruption.

## 6.2 The Declarations Solution (`src/common/declarations.inc`)

`src/common/declarations.inc` is automatically prepended during `.inc` compilation, providing exact `declare` prototypes across all 68 modules.

## 6.3 Topological Group Linking (`link_all_modules.sh`)

`link_all_modules.sh` groups 68 objects into 9 topological tiers and uses `-Wl,--start-group ... -Wl,--end-group` to resolve cyclic symbol dependencies cleanly.

---

# Chapter 7: The Infinite Bootstrap and Self-Hosting Loop

## 7.1 The Point of Inflection

The Stage 6 compiler has achieved the **Point of Inflection**: `compiler_dev` can compile all 68 modules from scratch, link a new generation ($G_1$), which in turn compiles ($G_2$), in an infinite, self-sustaining loop.

## 7.2 Full Test Suite Matrix

| Suite | Test Count | Pass Rate |
| :--- | :---: | :---: |
| `test_suite_v6dv/*.lr` | 60 | **100% (60/60)** |
| `examples/*.lr` + `tests/*.lr` | 63 | **100% (63/63)** |
| `modular_test/app.lr` | 1 | **100% (1/1)** |
| `test_full_flags/` | Complete | **100%** |
| **Total Global Tests** | **124** | **100%** |

---

# Chapter 8: Guide for Future Maintainers and AI Agents

## 8.1 Golden Invariants
1. **150-Line Limit**: Never create `.inc` files exceeding 150 lines.
2. **Type Inference Priority**: `fn_lookup_ret_tag` must always precede name-prefix heuristics.
3. **Global Linkage**: Use `common global` for uninitialized shared variables, `internal global` for constants.

## 8.2 6-Step Feature Workflow
1. Add tokens/AST kinds in `src/common/constants.inc`.
2. Update lexer scanner rules in `src/lexer/`.
3. Add grammar parsing in `src/parser/`.
4. Validate types in `src/semantic/`.
5. Emit LLVM IR instructions in `src/codegen/`.
6. Update `src/common/declarations.inc` and verify with `make -f Makefile_dev test-all`.
