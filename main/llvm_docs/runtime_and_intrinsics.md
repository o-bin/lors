# LLVM IR Runtime Support & C Standard Library Declarations

To support all Lors built-in functions seamlessly across stages without requiring external C runtime files, the compiler can declare and link against standard libc functions:

## 1. Standard C Library Declarations

```llvm
; I/O Operations
declare i32 @printf(ptr, ...)
declare i32 @puts(ptr)
declare i32 @snprintf(ptr, i64, ptr, ...)
declare i32 @getchar()
declare ptr @fgets(ptr, i32, ptr)

; Memory Management
declare ptr @malloc(i64)
declare ptr @realloc(ptr, i64)
declare void @free(ptr)
declare void @llvm.memcpy.p0.p0.i64(ptr, ptr, i64, i1)
declare void @llvm.memset.p0.i64(ptr, i8, i64, i1)

; String & Character Operations
declare i64 @strlen(ptr)
declare i32 @strcmp(ptr, ptr)
declare ptr @strcpy(ptr, ptr)
declare ptr @strcat(ptr, ptr)
declare ptr @strdup(ptr)

; Math Library (libm)
declare double @sin(double)
declare double @cos(double)
declare double @tan(double)
declare double @sqrt(double)
declare double @pow(double, double)
declare double @fabs(double)

; System & Process
declare i32 @system(ptr)
declare ptr @getenv(ptr)
declare void @exit(i32)
declare ptr @fopen(ptr, ptr)
declare i64 @fread(ptr, i64, i64, ptr)
declare i64 @fwrite(ptr, i64, i64, ptr)
declare i32 @fclose(ptr)
declare i32 @remove(ptr)
declare i32 @access(ptr, i32)
```

## 2. Built-in Runtime Helper Functions in LLVM IR
Lors functions map directly to standard runtime routines:
- `reveal(str)` -> `printf("%s\n", str)`
- `reveal(whole)` -> `printf("%lld\n", whole)`
- `reveal(precise)` -> `printf("%g\n", precise)`
- `reveal(state)` -> `printf("true\n")` or `printf("false\n")`
- `file_read(path)` -> reads file content into a heap-allocated string buffer
- `file_write(path, content)` -> writes content to a file using `fopen`/`fwrite`/`fclose`
- `file_remove(path)` -> calls `remove(path)`
- `file_exists(path)` -> calls `access(path, 0) == 0`
- `substring(s, start, len)` -> creates a new null-terminated string slice
- `length(s)` -> `strlen(s)` (or array length)
- `inquire()` -> reads a line from stdin (via `fgets` or `getline`)
- `to_string(num)` -> formats number via `snprintf`
- `to_precise(str)` -> parses double via `atof`/`strtod`
- `to_upper(str)` / `to_lower(str)` -> converts ASCII case
- `reverse(str)` -> reverses character sequence
- `is_alnum(c)` / `is_digit(c)` / `is_upper(c)` / `is_lower(c)` -> ASCII checks
- `execute_system(cmd)` -> calls `system(cmd)`
- `env_get(var)` -> calls `getenv(var)`
- `arg_count()` / `arg_value(i)` -> accesses CLI argc/argv
