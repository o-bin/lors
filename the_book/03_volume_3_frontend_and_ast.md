# Volume III: Frontend Architecture: Lexer, Preprocessor & AST

## Chapter 6: The Include Resolver, Visited Path Graphs, and Recursive Expansion

### 6.1 Modular File Composition via `incorporate`

In Lors, source code is divided into reusable modular files using the `incorporate` directive:

```lors
incorporate "src/common/constants.inc";
incorporate "src/common/str_utils.inc";
incorporate "src/lexer/token_struct.inc";
```

The preprocessor (`src/preprocessor/include_resolver.inc`) is responsible for resolving these directives recursively, reading the referenced files from disk, and constructing a unified source text stream for the lexical analyzer.

---

### 6.2 The Graph Cycle Problem

In a modular compiler comprising 68 interrelated files, modules frequently depend on common header definitions. For example:
- `parse_algorithm.inc` incorporates `constants.inc` and `ast_storage.inc`.
- `ast_storage.inc` incorporates `constants.inc` and `list_utils.inc`.
- `list_utils.inc` incorporates `constants.inc`.

Without cycle detection, expanding `incorporate` recursively results in infinite recursion, stack overflows, and redundant token duplication.

```
       parse_algorithm.inc
          /          \
         v            v
ast_storage.inc   constants.inc (Included multiple times!)
        |              ^
        v              |
  list_utils.inc ------+
```

---

### 6.3 The Visited Path Graph Algorithm

The include resolver maintains a persistent global visited registry string:
```lors
datum inc_visited_str : series;
```

#### Step-by-Step Resolution Process:
1. **Initialization**: Before preprocessing, `inc_init()` resets `inc_visited_str = ";"`.
2. **Visited Check**: When `preprocess_file(path)` is invoked:
   ```lors
   algorithm inc_is_visited(path : series) -> state
   begin
       result str_contains(inc_visited_str, ";" + path + ";");
   end
   ```
3. **Short-Circuit on Visited**: If `inc_is_visited(path)` returns `true`, `preprocess_file` immediately returns an empty string `""`.
4. **Registration**: If unvisited, `inc_mark_visited(path)` records the file:
   ```lors
   algorithm inc_mark_visited(path : series) -> void
   begin
       inc_visited_str = inc_visited_str + path + ";";
   end
   ```
5. **Recursive Expansion**:
   - The file content is read via `read_source_file(path)` in `src/preprocessor/file_reader.inc`.
   - The preprocessor scans line by line.
   - If a line starts with `incorporate "..."`, it extracts the sub-path and recursively invokes `preprocess_file(sub_path)`.
   - All other lines are appended directly to the accumulated output buffer.

This guarantees that every file in the dependency graph is expanded **exactly once**, yielding a deterministic, linear source code representation.

---

## Chapter 7: The Token Stream, State Machine, Keyword Lexing, and Character Classification

### 7.1 Lexical Analysis Architecture

The lexer (`src/lexer/`) processes the flattened source string into a contiguous array of strongly-typed tokens.

```
Flattened Source String
          |
          v
[lexer_state.inc] (lex_src, lex_pos, lex_line, lex_col)
          |
          +---> [lexer_core.inc] (Main dispatch loop)
          |        |
          |        +---> [lexer_keywords.inc] (Keywords & Identifiers)
          |        |
          |        +---> [lexer_literals.inc] (Numbers, Strings, Chars)
          |
          v
[token_struct.inc] (Parallel arrays: types, values, lines, columns)
```

---

### 7.2 The Token Array Representation

Rather than allocating individual token objects, `token_struct.inc` uses flat parallel arrays:

```lors
datum tok_count : whole = 0;
datum tok_types_data : series;
datum tok_vals_data : series;
datum tok_lines_data : series;
datum tok_cols_data : series;
```

#### Token Properties:
- `token_get_type(idx)`: Returns the integer token tag (`TOK_ALGORITHM`, `TOK_IDENT`, `TOK_INT`, `TOK_EQ`, etc.).
- `token_get_val(idx)`: Returns the textual string content of the token.
- `token_get_line(idx)`: Returns the 1-based source line number where the token occurred.
- `token_get_col(idx)`: Returns the 1-based column number.

---

### 7.3 Scanning States and Literal Handling

1. **Numerical Scanning (`src/lexer/lexer_literals.inc`)**:
   - Scans continuous digits `[0-9]+`.
   - If a decimal point `.` followed by digits is found, it classifies the token as `TOK_FLOAT` (for `precise` literals).
   - Otherwise, it classifies the token as `TOK_INT` (for `whole` literals).

2. **String Literal Scanning**:
   - When double quotes `"` are encountered, the scanner reads characters until the terminating quote.
   - Escape sequences (`\n`, `\t`, `\"`, `\\`) are preserved or translated.
   - The token is tagged as `TOK_STRING` with its value unquoted.

3. **Identifier vs Keyword Matching (`src/lexer/lexer_keywords.inc`)**:
   - Identifiers start with `[a-zA-Z_]` followed by `[a-zA-Z0-9_]*`.
   - The scanned string is compared against the keyword dictionary.
   - If matched, it returns the keyword token tag; otherwise, it returns `TOK_IDENT`.

---

## Chapter 8: The Abstract Syntax Tree: Memory Nodes, Hierarchy, and Traversal

### 8.1 AST Node Taxonomy

The AST is composed of normalized integer node kinds defined in `src/common/constants.inc`:

| AST Kind Constant | Value | Description |
| :--- | :---: | :--- |
| `AST_PROGRAM` | 1 | Root compilation unit node |
| `AST_ALGORITHM_DECL` | 2 | Function declaration or definition |
| `AST_STRUCT_DECL` | 3 | Compound structure declaration |
| `AST_GLOBAL_DATUM` | 4 | Global variable declaration |
| `AST_DATUM_DECL` | 10 | Local variable or parameter declaration |
| `AST_ASSIGN` | 11 | Variable assignment statement (`x = expr;`) |
| `AST_VERIFY` | 12 | Conditional statement (`verify then otherwise`) |
| `AST_CYCLE` | 13 | Loop construct (`cycle do conclude`) |
| `AST_RESULT` | 14 | Return statement (`result expr;`) |
| `AST_REVEAL` | 15 | Standard output statement (`reveal(expr);`) |
| `AST_BLOCK` | 16 | Block of statements enclosed in `begin ... end` |
| `AST_BINOP` | 20 | Binary arithmetic, relational, or logical operator |
| `AST_UNOP` | 21 | Unary operator (`not`, `-`) |
| `AST_CALL` | 22 | Function call or struct constructor |
| `AST_INDEX` | 23 | Sequence indexing (`arr[i]`) |
| `AST_MEMBER` | 24 | Struct member access (`obj.field`) |
| `AST_IDENT` | 30 | Variable or identifier reference |
| `AST_INT` | 31 | Integer literal (`whole`) |
| `AST_FLOAT` | 32 | Floating-point literal (`precise`) |
| `AST_STRING` | 33 | String literal (`series`) |
| `AST_BOOL` | 34 | Boolean literal (`true`, `false`) |

---

### 8.2 AST Hierarchy and Child Linking

Each AST node maintains a dynamic child list serialized as comma-delimited integers in `ast_children_ptrs_data`:

```
Node #0 (AST_PROGRAM)
   |
   +---> Child #1 (AST_STRUCT_DECL: "Point")
   |        +---> Child #2 (AST_DATUM_DECL: "x" : precise)
   |        +---> Child #3 (AST_DATUM_DECL: "y" : precise)
   |
   +---> Child #4 (AST_ALGORITHM_DECL: "genesis")
            +---> Child #5 (AST_BLOCK)
                     +---> Child #6 (AST_REVEAL)
                              +---> Child #7 (AST_STRING: "Hello, World!")
```

Child manipulation helpers in `src/ast/ast_node.inc`:
- `ast_add_child(parent_id, child_id)`: Appends `to_string(child_id) + ","` to `ast_children_ptrs_data[parent_id]`.
- `ast_get_child_count(parent_id)`: Returns the total number of children linked to the parent.
- `ast_get_child(parent_id, index)`: Retrieves the child node ID at position `index`.

---

## Chapter 9: The LL(1) Recursive Descent Parser & Precedence Climbing

### 9.1 Parser State & Lookahead Management

The parser (`src/parser/`) is a recursive descent parser with 1 token lookahead ($LL(1)$).

```lors
datum parse_pos : whole = 0;
```

- `parse_peek_type()`: Examines `tok_types_data[parse_pos]` without advancing.
- `parse_advance()`: Advances `parse_pos` by 1.
- `parse_match(tok_type)`: If `parse_peek_type() == tok_type`, advances and returns `true`; else returns `false`.
- `parse_expect(tok_type, error_msg)`: Asserts match. On failure, calls `error_report(error_msg, line, col)`.

---

### 9.2 Precedence Climbing for Binary Expressions

To correctly parse complex mathematical expressions such as:
$$a + b \times c - d / e == f \text{ and not } g$$
without building an ambiguous grammar, expression parsing is decomposed into 6 strict precedence tiers:

```
parse_expression()
       |
       v
parse_expr_or()            (Precedence 1: 'or')
       |
       v
parse_expr_and()           (Precedence 2: 'and')
       |
       v
parse_expr_equality()      (Precedence 3: '==', '!=')
       |
       v
parse_expr_relational()    (Precedence 4: '<', '<=', '>', '>=')
       |
       v
parse_expr_additive()      (Precedence 5: '+', '-')
       |
       v
parse_expr_multiplicative()(Precedence 6: '*', '/', '%')
       |
       v
parse_expr_unary()         (Unary: 'not', '-')
       |
       v
parse_postfix()            (Postfix: Call '()', Index '[]', Member '.')
       |
       v
parse_primary()            (Literals, Identifiers, Parenthesized '(expr)')
```

Every level consumes its matching operators in a deterministic `cycle` loop, constructing left-associative binary operator AST nodes (`AST_BINOP`).
