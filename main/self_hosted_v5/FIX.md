# FIX.md - Handoff for self_hosted_v5 LLVM Compiler

## Context
We are building `self_hosted_v5`, a self-hosted version of the Lors compiler that directly outputs LLVM IR (`.ll` files) instead of transpiling to C++. The code must be fully written in `.lr` and `.inc` files.

The architecture uses a new AST Type Propagation pass (`llvm_types.inc`) that runs before code generation. In the LLVM code generator (`llvm_codegen.inc`), we have fully transitioned to modern **Opaque Pointers (`ptr`)** to eliminate `bitcast` clutter and rely strictly on the AST analyzer for strong typing.

## Current Blocker
The compiler is currently blocked from compiling itself (the "bootstrap" step using the older V4 compiler `../self_compiler_s/compiler`).

When running `cd self_hosted_v5 && make`, the V4 compiler crashes with a syntax error:
```
Compiling: lors_compiler.lr
Syntax Error: )
Got token type: 41 at line 365
```
*(Line numbers shift as the code is edited)*. Token 41 is the `[` character (bracket).

## The Root Cause
The older V4 Lors parser has a known limitation: **It struggles to parse highly nested `verify ... otherwise` blocks and compound logical conditions** (e.g., `verify (a == b or c == d and e != f)`). When expressions become too long or deeply nested, the parser state machine breaks down, loses track of parenthesis/brackets, and throws an obscure syntax error.

## The Approach (What I was doing)
I have been manually "flattening" the boolean logic in `self_hosted_v5/self_compiler/llvm_types.inc` and `llvm_codegen.inc`.

Instead of this (which breaks the V4 parser):
```lors
verify (fname == "to_string" or fname == "substring" or fname == "to_upper") then
    res_type = "ptr";
otherwise
    verify (fname == "length" or fname == "to_integer") then
        res_type = "i64";
    conclude
conclude
```

I have been rewriting it to this flat structure:
```lors
datum is_str_fn : state = false;
verify (fname == "to_string") then is_str_fn = true; conclude
verify (fname == "substring") then is_str_fn = true; conclude
verify (fname == "to_upper") then is_str_fn = true; conclude

datum is_int_fn : state = false;
verify (fname == "length") then is_int_fn = true; conclude
verify (fname == "to_integer") then is_int_fn = true; conclude

verify (is_str_fn) then
    res_type = "ptr";
conclude
verify (is_int_fn) then
    res_type = "i64";
conclude
```

I also removed deep `otherwise` nesting in favor of sequential `verify` statements or early returns.

## Your Task (Next AI)
1. You must finish flattening the remaining complex logical conditions (`or`, `and`) and deeply nested `verify` / `otherwise` blocks in `self_hosted_v5/self_compiler/llvm_types.inc` and `llvm_codegen.inc`.
2. Pay special attention to the `propagate_type` and `propagate_stmt` functions in `llvm_types.inc`, as they still contain nested `otherwise` blocks that are triggering the `Syntax Error: ) Got token type: 41` near lines 350-450.
3. Test your progress by running:
   ```bash
   cd self_hosted_v5
   ../self_compiler_s/compiler -debug lors_compiler.lr
   ```
   Or simply `make`.
4. Keep breaking down the logic until `lors_compiler.lr` successfully compiles into an executable binary (`lors_compiler`). Do not introduce Python or C++ scripts. The compiler must be written strictly in Lors.