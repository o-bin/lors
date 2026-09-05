# Volume II: Memory Systems, Data Structures & Internal Runtime

## Chapter 3: Structure-of-Arrays (SoA) vs Array-of-Structures in Self-Hosting

### 3.1 The Memory Challenge in Self-Hosted Compilers

In conventional compiler architectures written in C++ or Rust, an AST node is commonly implemented as a polymorphic heap-allocated object or an enum variant containing raw pointers to child nodes:

```cpp
// Traditional C++ Array-of-Structures (AoS)
struct ASTNode {
    ASTKind kind;
    std::string s_val;
    int64_t n_val;
    TypeTag type_tag;
    std::string type_name;
    int64_t line;
    int64_t col;
    std::vector<ASTNode*> children;
};
```

While natural in high-level managed languages, this Array-of-Structures (AoS) approach presents catastrophic challenges when building a self-hosted bootstrap compiler:
1. **Dynamic Heap Fragmentation**: Millions of small allocations (`malloc`/`free`) cause heap fragmentation and memory leaks if a full garbage collector is not yet written in the language.
2. **Pointer Aliasing & ABI Hazards**: Passing complex struct pointers between independently compiled `.o` modules requires identical struct memory layout alignment (padding, vtables, alignment bytes) across all translation units.
3. **Cache Line Inefficiency**: Traversing an AoS tree causes random memory jumps across the heap, degrading CPU cache utilization.

---

### 3.2 The Lors Structure-of-Arrays (SoA) Solution

Stage 6 solves this fundamental problem by abandoning AoS in favor of a pure **Structure-of-Arrays (SoA)** flat table architecture.

In Lors, an AST node is simply an integer index `node_id : whole` (e.g., `0, 1, 2, ...`). The node's attributes are stored in parallel, pre-allocated global arrays in `src/ast/ast_storage.inc`:

```
Logical Node ID
      |
      +---> ast_kinds_data[node_id]          : whole (e.g. AST_BINOP = 40)
      +---> ast_s_vals_data[node_id]         : series (e.g. "+")
      +---> ast_n_vals_data[node_id]         : whole (e.g. 0)
      +---> ast_type_tags_data[node_id]      : whole (e.g. TYPE_WHOLE = 1)
      +---> ast_type_names_data[node_id]     : series (e.g. "whole")
      +---> ast_lines_data[node_id]          : whole (e.g. line 42)
      +---> ast_cols_data[node_id]           : whole (e.g. col 15)
      +---> ast_children_ptrs_data[node_id]  : series (e.g. "1,2;")
      +---> ast_children_counts_data[node_id]: whole (e.g. 2)
```

### 3.3 Node Creation Mechanics

When `ast_create_node(kind, s_val, n_val, line)` is called in `src/ast/ast_storage.inc`:

```lors
algorithm ast_create_node(kind : whole, s_val : series, n_val : whole, line : whole) -> whole
begin
    datum id : whole = ast_total_nodes;
    ast_kinds_data = int_list_add(ast_kinds_data, kind);
    ast_s_vals_data = str_list_add(ast_s_vals_data, s_val);
    ast_n_vals_data = int_list_add(ast_n_vals_data, n_val);
    ast_type_tags_data = int_list_add(ast_type_tags_data, TYPE_UNKNOWN);
    ast_type_names_data = str_list_add(ast_type_names_data, "");
    ast_lines_data = int_list_add(ast_lines_data, line);
    ast_cols_data = int_list_add(ast_cols_data, 0);
    ast_children_ptrs_data = str_list_add(ast_children_ptrs_data, "");
    ast_children_counts_data = int_list_add(ast_children_counts_data, 0);
    ast_total_nodes = ast_total_nodes + 1;
    result id;
end
```

#### Why This Model is Immune to Memory Corruption:
1. **Zero Raw Pointers**: A node ID is an integer. Passing node IDs between functions across `.o` modules never risks dangling pointers.
2. **Deterministic Reset**: When compiling multiple files in batch mode (`-oall`), the entire AST storage is instantly reset in $O(1)$ time by calling `ast_init()`:
   ```lors
   algorithm ast_init() -> void
   begin
       ast_total_nodes = 0;
       ast_kinds_data = "";
       ast_s_vals_data = "";
       ast_n_vals_data = "";
       ast_type_tags_data = "";
       ast_type_names_data = "";
       ast_lines_data = "";
       ast_cols_data = "";
       ast_children_ptrs_data = "";
       ast_children_counts_data = "";
   end
   ```

---

## Chapter 4: Paged Tables, Dynamic String Serialization, and FNV-1a Interning

### 4.1 Delimited String Serialization (`src/common/list_utils.inc`)

In the early bootstrap phase, dynamic arrays of strings and integers are serialized into contiguous strings using standard delimiters:

- **String Lists**: Elements are delimited by trailing semicolons:
  $$\text{List} = s_0 + \text{";"} + s_1 + \text{";"} + \dots + s_{n-1} + \text{";"}$$
- **Adding an Element**: `list = list + item + ";"`
- **Accessing Element $k$**: Scans character by character, counting semicolons until reaching the $k$-th delimiter, and slices the substring between delimiter $k-1$ and $k$.
- **Integer Lists**: Stored identically by serializing integers with `to_string(val) + ";"`.

---

### 4.2 The Virtual Paged Storage System (`src/memory/paged_storage.inc`)

When compilation units contain thousands of tokens and AST nodes, repeated string concatenation of long arrays can incur quadratic re-allocation costs ($O(N^2)$). To eliminate this bottleneck, `paged_storage.inc` implements virtual 2D paging:

```
Virtual Index: [0 ... 255]       [256 ... 511]      [512 ... 767]
                 Page 0             Page 1             Page 2
               +--------+         +--------+         +--------+
               | Slot 0 |         | Slot 0 |         | Slot 0 |
               | Slot 1 |         | Slot 1 |         | Slot 1 |
               |  ...   |         |  ...   |         |  ...   |
               |Slot 255|         |Slot 255|         |Slot 255|
               +--------+         +--------+         +--------+
                    ^                  ^                  ^
                    |                  |                  |
               Page Pointer 0     Page Pointer 1     Page Pointer 2
```

1. Each page holds a fixed capacity (e.g., $C = 256$ entries).
2. Given a virtual index $I$:
   $$\text{Page ID} = I / C$$
   $$\text{Page Offset} = I \pmod C$$
3. Appending a new element only touches the current active page, bounding allocation cost to strictly $O(1)$.

---

### 4.3 FNV-1a String Interning Engine (`src/memory/string_interner.inc`)

During tokenization and parsing, string identifiers such as `"algorithm"`, `"verify"`, `"datum"`, and variable names are encountered thousands of times. Comparing strings via character-by-character loops (`strcmp`) degrades parsing throughput.

The string interner computes a 64-bit FNV-1a hash for every encountered identifier:

$$\text{hash}_0 = 14695981039346656037$$
$$\text{hash}_{i+1} = (\text{hash}_i \oplus \text{byte}_i) \times 1099511628211 \pmod{2^{64}}$$

```
Raw String: "compile_single_file"
        |
        v
[fnv1a_hash] -> 0xA789F12BC84E3102
        |
        v
[intern_string] -> Intern ID #42
```

Once interned:
1. Every unique string in the program corresponds to exactly one integer ID.
2. String equality checks throughout the compiler reduce from $O(L)$ string comparisons to a single $O(1)$ integer CPU instruction:
   ```lors
   verify (token_id_a == token_id_b) then ... conclude
   ```

---

## Chapter 5: Global Data Segments, Stack Allocas, and Garbage-Free Lifecycles

### 5.1 The Stack Alloca Pattern in Generated Code

The code generation subsystem never relies on an external garbage collector or runtime heap allocator for local variables. Instead, it translates every local variable into an LLVM `alloca` instruction:

```llvm
; Compiling: datum count : whole = 10;
%var_count = alloca i64, align 8
store i64 10, ptr %var_count, align 8
```

#### Why Alloca-Centric Codegen is Crucial:
1. **Zero Heap Overhead**: Stack allocations cost 0 CPU instructions at runtime because the compiler adjusts the stack pointer `%rsp` once in the function prologue.
2. **Automatic Lifecycle Cleanup**: When a function returns, its entire stack frame is instantly reclaimed with zero garbage collection pause.
3. **Compatibility with LLVM `mem2reg`**: Clang's optimization passes automatically convert all non-escaped `alloca` memory locations into virtual SSA hardware registers, yielding maximum performance.
