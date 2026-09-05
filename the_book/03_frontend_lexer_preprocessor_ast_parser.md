# Chapter 3: Frontend: Preprocessor, Lexer, AST and Parser

## 3.1 Preprocessor Architecture and Include Resolution

The Lors preprocessor (`src/preprocessor/`) resolves `incorporate "<filepath>";` directives recursively before lexical analysis begins.

```
Source File (.lr / .inc)
        |
        v
[include_resolver] <---> [file_reader]
        |
        v
Cycle Detection (inc_visited_str)
        |
        v
Flattened Source String
```

### Preventing Circular Dependencies
In a large modular codebase with dozens of cross-referencing files, circular includes (`A incorporates B`, `B incorporates A`) can cause infinite expansion loops.

The preprocessor implements a visited registry:
1. `inc_init()` clears the visited path string (`inc_visited_str = ";"`).
2. When `preprocess_file(path)` is called:
   - It checks `inc_is_visited(path)`.
   - If already visited, it returns an empty string `""` immediately.
   - If not visited, it marks the path with `inc_mark_visited(path)`.
3. It reads the file using `read_source_file(path)`, scans for `incorporate` statements, replaces them recursively with the expanded child contents, and returns the complete flattened text.

---

## 3.2 Lexer Architecture and State Machine

The lexer (`src/lexer/`) transforms raw character streams into a contiguous array of tokens.

### Token Data Representation (`src/lexer/token_struct.inc`)
Tokens are stored in parallel arrays:
- `tok_types_data`: Integer token constants (`TOK_IDENT`, `TOK_INT`, `TOK_ALGORITHM`, etc.).
- `tok_vals_data`: Literal text or identifier names.
- `tok_lines_data`: 1-based source line numbers for diagnostic reporting.
- `tok_cols_data`: 1-based source column numbers.

### Lexical Scanning Loop (`src/lexer/lexer_core.inc`)
The scanning engine maintains:
- `lex_pos`: Current character index in source string.
- `lex_line`: Current line number.
- `lex_col`: Current column number.

```lors
algorithm lexer_tokenize() -> void
begin
    cycle (lexer_is_at_end() == false) do
        datum c : whole = lexer_peek();
        verify (c == 32 or c == 9 or c == 13 or c == 10) then
            lexer_advance(); // Skip whitespace
        otherwise
            verify (c == 47 and lexer_peek_next() == 47) then
                // Single-line comment // ...
                cycle (lexer_is_at_end() == false and lexer_peek() != 10) do
                    lexer_advance();
                conclude
            otherwise
                lexer_scan_token();
            conclude
        conclude
    conclude
    token_add(TOK_EOF, "", lex_line, lex_col);
end
```

### Keyword Classification (`src/lexer/lexer_keywords.inc`)
Identifiers are scanned and matched against the reserved keyword table:
- `algorithm` -> `TOK_ALGORITHM`
- `begin` -> `TOK_BEGIN`
- `end` -> `TOK_END`
- `datum` -> `TOK_DATUM`
- `verify` -> `TOK_VERIFY`
- `then` -> `TOK_THEN`
- `otherwise` -> `TOK_OTHERWISE`
- `conclude` -> `TOK_CONCLUDE`
- `cycle` -> `TOK_CYCLE`
- `do` -> `TOK_DO`
- `result` -> `TOK_RESULT`
- `reveal` -> `TOK_REVEAL`
- `structure` -> `TOK_STRUCTURE`
- `whole`, `precise`, `series`, `state`, `void`, `sequence` -> Type tokens.

---

## 3.3 Parser Architecture: Recursive Descent Engine

The parser (`src/parser/`) constructs the Abstract Syntax Tree using recursive descent with single-token lookahead ($LL(1)$).

```
                      parse_program()
                             |
         +-------------------+-------------------+
         |                                       |
  parse_struct_decl()                 parse_algorithm_decl()
                                                 |
                                         parse_statement()
                                                 |
                                         parse_expression()
```

### Safe Token Consumption (`src/parser/parser_state.inc`)
To prevent infinite loops during syntax errors, the parser uses strict helper routines:
- `parse_peek_type()`: Returns the type of the current token without consuming it.
- `parse_advance()`: Consumes the current token and increments `parse_pos`.
- `parse_match(expected)`: If the current token matches `expected`, consumes it and returns `true`; otherwise returns `false`.
- `parse_expect(expected, err_msg)`: Asserts that the current token matches `expected`. If true, advances and returns `true`. If false, emits a detailed error report with line and column numbers and returns `false`.

### Expression Precedence Hierarchy
Expression parsing is decomposed into hierarchical layers to enforce standard operator precedence without ambiguity:

1. **`parse_expression` / `parse_expr_binary`**:
   - Level 1: Logical OR (`or`)
   - Level 2: Logical AND (`and`)
   - Level 3: Equality (`==`, `!=`)
   - Level 4: Relational (`<`, `<=`, `>`, `>=`)
   - Level 5: Additive (`+`, `-`)
   - Level 6: Multiplicative (`*`, `/`, `%`)
2. **`parse_expr_unary`**: Unary minus (`-`), logical NOT (`not`).
3. **`parse_postfix`**: Function calls `foo(...)`, array indexation `arr[i]`, member access `obj.field`.
4. **`parse_primary`**: Literal numbers, strings, booleans, identifiers, and parenthesized sub-expressions `(...)`.
