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

---

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

---

## 1.3 The Nine Architectural Layers

The Stage 6 compiler codebase is divided into 9 hierarchical layers:

```
+-------------------------------------------------------------+
| Layer 9: Driver (CLI, Pipeline Orchestration, Batching)     |
+-------------------------------------------------------------+
| Layer 8: Code Generation (LLVM IR Emission, Registers, ABI) |
+-------------------------------------------------------------+
| Layer 7: Semantic Analysis (Types, Scopes, Struct Registry) |
+-------------------------------------------------------------+
| Layer 6: Parser (Recursive Descent Grammar, AST Building)   |
+-------------------------------------------------------------+
| Layer 5: Lexer (Tokenization, Keywords, State Tracking)     |
+-------------------------------------------------------------+
| Layer 4: Preprocessor (Include Resolution, Cycle Detection) |
+-------------------------------------------------------------+
| Layer 3: Abstract Syntax Tree (Node Storage, Hierarchy)     |
+-------------------------------------------------------------+
| Layer 2: Memory & Storage (Arenas, Paged Tables, Interning) |
+-------------------------------------------------------------+
| Layer 1: Common Utilities (Strings, Lists, Paths, Errors)   |
+-------------------------------------------------------------+
```

### Layer Descriptions

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

---

## 1.4 The 150-Line Architectural Invariant

A strict design constraint in Stage 6 is that **no file may exceed 150 lines of code**.

### Rationale and Benefits
1. **Cognitive Load Reduction**: Each file handles one distinct, well-defined algorithmic task.
2. **Context Window Optimization**: Small modular files allow AI coding assistants and human developers to read and modify components without context saturation.
3. **True Modularity**: Forces developers to avoid monolithic anti-patterns and maintain clean decoupled interfaces.
4. **Independent Verifiability**: Enables automated linters and build scripts to compile and verify every sub-system in isolation.
