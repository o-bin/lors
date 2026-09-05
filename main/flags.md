# Compiler Flags Documentation

This document describes the new flags added to the self-hosted Lors compiler.

## New Flags

### `-oall`
Compiles all `.lr` and `.inc` files in the current directory into object files (`.o`).

- If a `.inc` file has a corresponding `.lr` file (e.g., `math.inc` and `math.lr`), the compiler uses the `.lr` file to compile it.
- If a `.inc` file is an "orphan" (no corresponding `.lr`), the compiler automatically generates a temporary wrapper to compile it.

**Usage:**
```bash
self_compiler -oall
```

### `-iall`
Links all `.o` files in the current directory into a single executable.

**Usage:**
```bash
self_compiler -iall [-ns <output_name>]
```

### `-ns <name>`
Specifies the name of the output executable when using `-iall`.
If not provided, the output will default to `program`.

## Testing Example

A sample test environment is provided in the `flags_test` directory.

**Files:**
- `main.lr`: The entry point.
- `math_utils.inc` + `math_utils.lr`: A module with a proper .lr wrapper.
- `orphan.inc`: A module without a .lr wrapper (demonstrates auto-wrapping).

**Steps:**
```bash
cd flags_test
../self_compiler_s/compiler -oall
../self_compiler_s/compiler -iall -ns test_prog
./test_prog
```
