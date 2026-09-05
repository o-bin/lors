# LLVM IR Instruction Set Reference

## 1. Terminator Instructions

Every Basic Block must end with exactly one terminator instruction.

### `ret` (Return)
- Returns a value or void from a function:
  ```llvm
  ret i64 %val
  ret double %dval
  ret ptr %ptrval
  ret void
  ```

### `br` (Branch)
- Unconditional Branch:
  ```llvm
  br label %target_block
  ```
- Conditional Branch:
  ```llvm
  br i1 %cond, label %true_block, label %false_block
  ```

### `switch`
- Multiway branch based on an integer value:
  ```llvm
  switch i64 %val, label %default_block [
      i64 0, label %case0
      i64 1, label %case1
  ]
  ```

### `unreachable`
- Informs the optimizer that control flow will never reach this point:
  ```llvm
  unreachable
  ```

---

## 2. Binary Arithmetic Operations

### Integer Arithmetic
- Addition: `%r = add i64 %a, %b`
- Subtraction: `%r = sub i64 %a, %b`
- Multiplication: `%r = mul i64 %a, %b`
- Signed Division: `%r = sdiv i64 %a, %b`
- Signed Remainder (Modulo): `%r = srem i64 %a, %b`

### Floating-Point Arithmetic
- Float Addition: `%r = fadd double %a, %b`
- Float Subtraction: `%r = fsub double %a, %b`
- Float Multiplication: `%r = fmul double %a, %b`
- Float Division: `%r = fdiv double %a, %b`
- Float Remainder: `%r = frem double %a, %b`

---

## 3. Bitwise & Logic Operations

- Bitwise AND: `%r = and i1 %a, %b` (or `i64`)
- Bitwise OR: `%r = or i1 %a, %b`
- Bitwise XOR (Not / Invert): `%r = xor i1 %a, true` / `%r = xor i64 %a, %b`
- Shift Left: `%r = shl i64 %a, %shift`
- Logical Shift Right: `%r = lshr i64 %a, %shift`
- Arithmetic Shift Right: `%r = ashr i64 %a, %shift`

---

## 4. Comparisons

### Integer Comparisons (`icmp`)
Syntax: `%r = icmp <cond> <type> <op1>, <op2>`
Yields an `i1` result.
- `eq`: Equal (`==`)
- `ne`: Not equal (`!=`)
- `sgt`: Signed greater than (`>`)
- `sge`: Signed greater or equal (`>=`)
- `slt`: Signed less than (`<`)
- `sle`: Signed less or equal (`<=`)

Example:
```llvm
%cmp = icmp slt i64 %i, 10
br i1 %cmp, label %loop_body, label %loop_end
```

### Floating-Point Comparisons (`fcmp`)
Syntax: `%r = fcmp <cond> double <op1>, <op2>`
Yields an `i1` result.
- `oeq`: Ordered and equal (`==`)
- `one`: Ordered and not equal (`!=`)
- `ogt`: Ordered greater than (`>`)
- `oge`: Ordered greater or equal (`>=`)
- `olt`: Ordered less than (`<`)
- `ole`: Ordered less or equal (`<=`)

---

## 5. Type Conversions & Casts

- `trunc <type> <val> to <target>`: Truncate integer (e.g. `trunc i64 %a to i32`)
- `zext <type> <val> to <target>`: Zero extend integer (e.g. `zext i1 %b to i64`)
- `sext <type> <val> to <target>`: Sign extend integer (e.g. `sext i32 %a to i64`)
- `sitofp <type> <val> to <target>`: Signed int to float (e.g. `sitofp i64 %a to double`)
- `fptosi <type> <val> to <target>`: Float to signed int (e.g. `fptosi double %f to i64`)
- `bitcast <type> <val> to <target>`: Reinterpret bit pattern
- `ptrtoint ptr <val> to i64`: Pointer to integer
- `inttoptr i64 <val> to ptr`: Integer to pointer

---

## 6. PHI Node (`phi`)

Used to select values depending on the basic block predecessors:
```llvm
%res = phi i64 [ %val_from_entry, %entry ], [ %val_from_loop, %loop_body ]
```
