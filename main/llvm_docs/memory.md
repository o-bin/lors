# LLVM IR Memory Model & Addressing

## 1. Stack Allocation: `alloca`

Allocates memory on the stack frame of the executing function. Stack memory is automatically reclaimed when the function returns.

Syntax:
```llvm
%ptr = alloca <type>
%ptr_arr = alloca <type>, i64 <num_elements>
```

Examples:
```llvm
%x = alloca i64
%d = alloca double
%s = alloca ptr
%p = alloca %struct.Point
```

---

## 2. Memory Access: `load` and `store`

### `load`
Reads a typed value from a memory address pointed to by a pointer.
Syntax:
```llvm
%val = load <type>, ptr <pointer_value>
```
Examples:
```llvm
%val_i64 = load i64, ptr %x
%val_ptr = load ptr, ptr %s
```

### `store`
Writes a typed value to a memory address.
Syntax:
```llvm
store <type> <val>, ptr <pointer_value>
```
Examples:
```llvm
store i64 100, ptr %x
store ptr %new_str, ptr %s
```

---

## 3. Address Calculation: `getelementptr` (GEP)

Calculates the address of a sub-element of an aggregate (array or struct) or pointer offset without accessing memory.

Syntax under opaque pointers:
```llvm
%field_ptr = getelementptr <BaseType>, ptr <pointer_val>, <index_0>, <index_1>, ...
```

### Struct Field Access:
For a struct `%struct.Point = type { i64, i64 }`:
- Index 0: traverses the pointer itself (usually `i64 0` or `i32 0`).
- Index 1: accesses the field (e.g. `i32 0` for `.x`, `i32 1` for `.y`).

Example:
```llvm
; Address of p.y
%y_ptr = getelementptr %struct.Point, ptr %p, i32 0, i32 1
store i64 20, ptr %y_ptr
```

### Array Element Access:
For an array or memory buffer:
```llvm
; Element arr[i]
%elem_ptr = getelementptr i64, ptr %arr_base, i64 %i
store i64 %new_elem, ptr %elem_ptr
```

---

## 4. Heap Memory Management

Dynamic memory is allocated and freed via standard libc `malloc` and `free`:
```llvm
declare ptr @malloc(i64)
declare void @free(ptr)
```

Example creating a heap struct:
```llvm
%heap_mem = call ptr @malloc(i64 16)
store i64 10, ptr %heap_mem
%f2_ptr = getelementptr %struct.Point, ptr %heap_mem, i32 0, i32 1
store i64 20, ptr %f2_ptr
```
