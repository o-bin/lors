# Volume I: The Lors Language Specification & Compiler Philosophy

## Chapter 1: Grammar, Semantics, Types, and Deterministic Design Philosophy

### 1.1 The Philosophy of Determinism

The Lors programming language is engineered with a strict core philosophy: **absolute determinism, explicit typing, and transparent computational cost**. Unlike dynamic scripting languages that introduce hidden runtime allocations or complex object lifecycles, and unlike modern C++ with hidden copy constructors and implicit template instantiations, Lors enforces a 1-to-1 correspondence between high-level syntactic constructs and generated machine instructions.

In Lors:
1. Every variable has an explicitly declared type or a deterministically inferred type tag.
2. Memory mutation is localized, explicit, and trackable.
3. Control flow paths are un-aliased: every branch must terminate or merge cleanly into a continuation block.
4. Function signatures strictly specify parameter counts, argument types, and return types.

---

### 1.2 Formal Lexical Grammar & Keywords

Lors programs are composed of statements, declarations, and structured expressions. The keyword vocabulary is deliberately minimal, avoiding syntactic overloading:

- `algorithm`: Declares a procedural function or sub-routine.
- `begin` / `end`: Demarcates the executable body block of an algorithm.
- `datum`: Declares a typed variable binding in local or global scope.
- `verify ... then ... otherwise ... conclude`: Structured conditional branching.
- `cycle ... do ... conclude`: Structured deterministic iteration.
- `result`: Returns a computed expression or exits a void function.
- `reveal`: Formatted output to standard output stream.
- `structure`: Defines a compound record with named, typed fields.
- `incorporate`: Preprocessor directive for modular source file inclusion.

#### Primitive Type Specifiers
- `whole`: 64-bit signed integer (LLVM `i64`). Used for counting, array indexing, pointers, and bitwise operations.
- `precise`: 64-bit double-precision IEEE 754 floating-point number (LLVM `double`).
- `series`: Pointer to a null-terminated UTF-8 / ASCII string buffer (LLVM `ptr`).
- `state`: 1-bit boolean truth value (LLVM `i1`), evaluating strictly to `true` or `false`.
- `void`: Indicates that an algorithm produces no return value.
- `sequence<T>`: Homogeneous dynamic array containing elements of type `T`.
- `<CustomStruct>`: User-defined composite structure declared via `structure <Name>`.

---

### 1.3 Concrete Syntactic Forms

#### 1.3.1 Algorithm Definition
```lors
algorithm compute_hypotenuse(a : precise, b : precise) -> precise
begin
    datum a_sq : precise = a * a;
    datum b_sq : precise = b * b;
    datum sum : precise = a_sq + b_sq;
    result root(sum);
end
```

#### 1.3.2 Structured Conditional Branching
```lors
verify (x > 0 and x < 100) then
    reveal("x is within valid range");
otherwise
    reveal("x is out of bounds");
conclude
```

#### 1.3.3 Structured Iteration
```lors
datum i : whole = 0;
cycle (i < 10) do
    reveal(to_string(i));
    i = i + 1;
conclude
```

#### 1.3.4 Custom Structure Declarations
```lors
structure Point
    x : precise,
    y : precise,
    label : series
conclude
```

---

## Chapter 2: The Monolithic Stage 5 Legacy vs The Stage 6 Modular Revolution

### 2.1 The Architectural Crisis of Stage 5

Prior to Stage 6, the Lors self-hosted compiler existed in a monolithic format (`self_hosted_v5/lors_compiler`). In Stage 5, the entire compiler implementation was consolidated into a massive continuous file structure. While Stage 5 successfully proved that Lors could compile Lors, it introduced severe architectural bottlenecks that threatened the long-term survival and scalability of the language:

1. **The Monolithic Parsing Ceiling**:
   As the compiler codebase approached 10,000 lines of code, the lexical scanner and AST allocator began hitting memory and recursion constraints. Compiling a 15,000-line monolithic file required enormous contiguous string allocations.

2. **The Inability to Perform Separate Compilation**:
   Stage 5 could only compile an entire program as a single unit. It possessed no concept of producing separate `.o` object files or linking independent translation units. Any change to a single error message required recompiling the entire 10,000+ line compiler from scratch.

3. **Symbol Pollution and Global Name Collisions**:
   Without compilation boundaries, every helper function in the lexer was globally visible to the code generator, causing name shadowing and identifier collisions.

4. **Inscrutability for Language Models and Human Developers**:
   A single monolithic file of 15,000 lines exceeds the practical token window for precise AI reasoning and exhausts the human working memory. Refactoring a function in the middle of a massive file frequently broke unrelated components at the bottom of the file.

---

### 2.2 The Stage 6 Modular Architecture

Stage 6 (`v6-dv`) was conceived not merely as an incremental update, but as a complete paradigm shift: **The Full Modularization of the Compiler**.

```
+-------------------------------------------------------------------------------+
|                             STAGE 6 ARCHITECTURE                             |
+-------------------------------------------------------------------------------+
| 68 Independent Modules (.inc) | Strictly <= 150 Lines per File                |
| 9 Architectural Layers        | Unidirectional Dependency Graph               |
| Separate .o Compilation       | Every Module Compiles Standalone              |
| Topological Linker Group      | Resolves Cyclic Dependencies in One Binary    |
| Native LLVM Backend           | Emits Pure LLVM IR without C Transpilation    |
| Self-Hosting Bootstrap Loop   | Stage 6 Compiles Stage 6 Infinitely           |
+-------------------------------------------------------------------------------+
```

### 2.3 The Strict 150-Line Modular Invariant

To permanently prevent regression into monolithic architectures, Stage 6 established a non-negotiable invariant:
$$\forall f \in \text{SourceModules}(\text{Stage 6}), \quad \text{LineCount}(f) \le 150$$

#### Why 150 Lines?
- **Single Responsibility Principle**: A 150-line file can contain at most 2 to 4 closely related algorithms (e.g., `parse_expr_binary.inc` only parses binary expressions; `llvm_strings.inc` only handles string constant pools).
- **Zero-Ambiguity Context**: An AI model or human engineer can load the entire file, comprehend every branch, and make guaranteed bug-free modifications without context truncation.
- **Fast Build Increments**: During development, only modified `.inc` files are recompiled to `.o` before fast relinking.
