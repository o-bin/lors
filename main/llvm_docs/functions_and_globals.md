# LLVM IR Functions, Globals & Module Structure

## 1. Global String Constants

String constants in LLVM IR are defined as private unnamed address constants:

```llvm
@.str.0 = private unnamed_addr constant [14 x i8] c"Hello, World!\00", align 1
@.fmt_i64 = private unnamed_addr constant [6 x i8] c"%lld\0A\00", align 1
@.fmt_f64 = private unnamed_addr constant [4 x i8] c"%g\0A\00", align 1
@.fmt_str = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
```

To use the string constant as a `ptr`:
```llvm
%msg_ptr = getelementptr [14 x i8], ptr @.str.0, i64 0, i64 0
call i32 (ptr, ...) @printf(ptr @.fmt_str, ptr %msg_ptr)
```

---

## 2. Global Variables

Global mutable variables:
```llvm
@global_counter = global i64 0, align 8
@global_flag = global i1 false, align 1
@global_name = global ptr null, align 8
```

Accessing globals in functions:
```llvm
%val = load i64, ptr @global_counter, align 8
%next = add i64 %val, 1
store i64 %next, ptr @global_counter, align 8
```

---

## 3. Function Definitions

Syntax:
```llvm
define [linkage] <ReturnType> @<FunctionName>(<ParamType1> %<param1>, ...) {
entry:
    ; allocas and function body
    ret <ReturnType> <value>
}
```

Example Lors algorithm `add_numbers(a : whole, b : whole) -> whole`:
```llvm
define i64 @add_numbers(i64 %a, i64 %b) {
entry:
    %a.addr = alloca i64
    %b.addr = alloca i64
    store i64 %a, ptr %a.addr
    store i64 %b, ptr %b.addr
    %val_a = load i64, ptr %a.addr
    %val_b = load i64, ptr %b.addr
    %sum = add i64 %val_a, %val_b
    ret i64 %sum
}
```

---

## 4. Entry Point (`main` vs `genesis`)

Lors programs define `genesis()` as their entry point.
The compiler emits a standard C `main` function that initializes command line arguments, invokes `@genesis()`, and returns its code:

```llvm
define i32 @main(i32 %argc, ptr %argv) {
entry:
    ; initialize CLI globals if needed
    call void @__init_cli_args(i32 %argc, ptr %argv)
    %ret = call i64 @genesis()
    %exit_code = trunc i64 %ret to i32
    ret i32 %exit_code
}
```
