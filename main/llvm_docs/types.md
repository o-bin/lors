# LLVM IR Types Reference

## 1. Primitive Scalar Types

### Integer Types
LLVM integer types have arbitrary bit widths specified as `iN`.
Common widths in 64-bit target systems:
- `i1`: 1-bit integer, used for boolean states (`true` = 1, `false` = 0) and comparison results.
- `i8`: 8-bit integer, character byte.
- `i32`: 32-bit integer, common for status codes, C `int`, and array indices.
- `i64`: 64-bit integer, standard for Lors `whole` data type.

### Floating-Point Types
- `float`: 32-bit IEEE 754 floating point.
- `double`: 64-bit IEEE 754 floating point, standard for Lors `precise` data type.

### Void Type
- `void`: Represents the absence of a value (e.g. procedures returning no result).

## 2. Pointer Types (Opaque Pointers)

Modern LLVM (LLVM 15+) uses **opaque pointers**:
- Syntax: `ptr`
- Replaces typed pointers like `i32*`, `i8*`, `%struct.Node*`.
- Removes need for explicit `bitcast` instructions across pointer types.
- Address calculation (`getelementptr`) and memory operations (`load`, `store`) specify the pointee type explicitly.

Example:
```llvm
%x = alloca i64
store i64 42, ptr %x
%val = load i64, ptr %x
```

## 3. Aggregate Types

### Structure Types (`%struct.Name` or anonymous `{ T1, T2, ... }`)
Structure types represent a collection of fields stored contiguously in memory with alignment padding.
- Identified struct:
  ```llvm
  %struct.Point = type { i64, i64 }
  %struct.Vector = type { double, double }
  %struct.Node = type { i64, ptr }
  ```
- Anonymous struct: `{ i64, ptr, double }`

### Array Types (`[N x ElementType]`)
Fixed-size arrays with $N$ elements:
- Syntax: `[10 x i64]`, `[14 x i8]` (for strings like `c"Hello, World!\00"`).

## 4. Function Types
Syntax: `<ReturnType> (<ParamType1>, <ParamType2>, ...)`
Examples:
- `i64 (i64, i64)`
- `void (ptr)`
- `double (double)`
