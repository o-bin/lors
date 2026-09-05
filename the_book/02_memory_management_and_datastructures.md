# Chapter 2: Memory Management and Data Structures

## 2.1 Memory Model in a Self-Hosted Compiler

Building a self-hosted compiler in a language that does not expose explicit raw pointer arithmetic requires structured abstractions. The Lors compiler runtime uses a hybrid memory management model combining:

1. **Stack Allocation (`alloca` in LLVM IR)**: For all local variables, parameters, and temporary calculation slots.
2. **Global Segment Storage**: For compiler state, symbol tables, token streams, and AST nodes.
3. **Monotonic Arenas and Contiguous Buffers**: For dynamic text generation, string interning, and sequence management.

```
+-------------------------------------------------------------+
| Stack (LLVM alloca): Local frames, parameter mirrors        |
+-------------------------------------------------------------+
| Heap / BSS Data Segment: Global SoA tables (AST, Tokens)     |
+-------------------------------------------------------------+
| Constant Pool: Deduplicated String Literals (.rodata)       |
+-------------------------------------------------------------+
```

---

## 2.2 Structure-of-Arrays (SoA) Storage

To maintain extreme cache locality and avoid complex object allocators, the compiler uses **Structure-of-Arrays (SoA)** rather than Array-of-Structures (AoS).

### The AST Storage Model
An AST node in Lors is represented by an integer ID (`whole`). The node's properties are distributed across parallel dynamic arrays managed in `src/ast/ast_storage.inc`:

```
Node ID (Index) -> [0]      [1]      [2]      [3]      ...
ast_kinds_data  -> [BINOP]  [INT]    [IDENT]  [CALL]   ...
ast_s_vals_data -> ["+"]    ["42"]   ["x"]    ["foo"]  ...
ast_n_vals_data -> [0]      [42]     [0]      [1]      ...
ast_type_tags   -> [WHOLE]  [WHOLE]  [SERIES] [STATE]  ...
ast_type_names  -> ["whole"]["whole"]["series"]["state"]
ast_children    -> ["1,2;"] [""]     [""]     ["3;"]   ...
```

### Advantages of SoA in Self-Hosting
1. **Zero Dynamic Allocation per Node**: Allocating a node simply increments `ast_total_nodes` and appends values to flat strings or serialized lists.
2. **Simplified Garbage Collection**: The entire AST can be discarded between compilation units simply by setting `ast_total_nodes = 0` and resetting array heads.
3. **Portability Across Calling Conventions**: Passing a single integer ID (`whole` / `i64`) between functions replaces complex struct pointer dereferences.

---

## 2.3 List Serialization and Paged Storage

### List Serialization Format (`src/common/list_utils.inc`)
Because early stages of the self-hosted compiler operate with strings (`series`), lists of integers and strings are serialized using structured delimiters:

- **String List**: Elements separated by semicolons (`;`).
  ```
  "first_item;second_item;third_item;"
  ```
- **List Helpers**:
  - `str_list_add(list, item)`: Appends `item + ";"` to `list`.
  - `str_list_get(list, index)`: Scans semicolons up to `index` and returns the substring.
  - `str_list_set(list, index, item)`: Reconstructs the string replacing the specified slice.

### Paged Table Storage (`src/memory/paged_storage.inc`)
To avoid quadratic re-allocation costs when arrays grow large, `paged_storage.inc` implements virtual paging:
- Data is partitioned into fixed-size chunks (e.g., 256 entries per page).
- A directory table maps logical indices to physical page slots:
  $$\text{Page Index} = \lfloor \text{Logical Index} / \text{Page Capacity} \rfloor$$
  $$\text{Offset in Page} = \text{Logical Index} \pmod{\text{Page Capacity}}$$

---

## 2.4 String Interning and Hash Tables

The string interner (`src/memory/string_interner.inc`) deduplicates identifiers, keyword strings, and literal values across the compiler.

### FNV-1a Hash Algorithm
The compiler implements the 64-bit Fowler–Noll–Vo hash function:

```lors
algorithm fnv1a_hash(s : series) -> whole
begin
    datum hash : whole = 14695981039346656037;
    datum slen : whole = length(s);
    datum i : whole = 0;
    cycle (i < slen) do
        datum byte_val : whole = char_at(s, i);
        hash = hash ^ byte_val;
        hash = hash * 1099511628211;
        i = i + 1;
    conclude
    result hash;
end
```

### Lookup and Insertion
1. When a token string is encountered by the lexer, `intern_string(s)` computes its hash.
2. If the string exists in the table, its existing unique integer ID is returned.
3. If new, it is appended to the interner pool.
4. String equality comparisons throughout the semantic analyzer and parser are thereby reduced to fast integer comparisons (`id_a == id_b`).
