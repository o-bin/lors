#!/bin/bash
# ==========================================================
# Comprehensive CLI Flags Test Suite for Lors Stage 6
# ==========================================================

COMPILER="../compiler"
FAILED=0
PASSED=0

cd "$(dirname "$0")" || exit 1

echo "=========================================================="
echo "Starting Stage 6 Full CLI Flags Execution & Output Suite"
echo "=========================================================="

cleanup() {
    rm -f simple simple.o simple.ll
    rm -f mod_a.o mod_a.ll mod_b.o mod_b.ll
    rm -f program custom_app error_prog error_prog.ll error_prog.o .files.tmp .o_files.tmp *.log
}

cleanup

# ----------------------------------------------------------
# Test 1: No arguments (Usage output)
# ----------------------------------------------------------
echo "------------------------------------------------------------"
echo "[TEST 1] Command: ./compiler"
echo "[OUTPUT]"
OUT=$($COMPILER 2>&1)
echo "$OUT"
if echo "$OUT" | grep -q "Usage:"; then
    PASSED=$((PASSED + 1))
else
    echo "[ERROR] Expected Usage message, got: $OUT"
    FAILED=$((FAILED + 1))
fi

# ----------------------------------------------------------
# Test 2: Standard compilation (Executable created, .ll removed)
# ----------------------------------------------------------
echo "------------------------------------------------------------"
echo "[TEST 2] Command: ./compiler simple.lr && ./simple"
$COMPILER simple.lr >/dev/null 2>&1
if [ -f "simple" ] && [ ! -f "simple.ll" ]; then
    RUN_OUT=$(./simple)
    echo "[OUTPUT]"
    echo "$RUN_OUT"
    if [ "$RUN_OUT" = "Flags Simple Success" ]; then
        PASSED=$((PASSED + 1))
    else
        echo "[ERROR] Unexpected output: $RUN_OUT"
        FAILED=$((FAILED + 1))
    fi
else
    echo "[ERROR] Binary 'simple' not created or 'simple.ll' not cleaned up"
    FAILED=$((FAILED + 1))
fi
cleanup

# ----------------------------------------------------------
# Test 3: Flag -s (Save .ll on success)
# ----------------------------------------------------------
echo "------------------------------------------------------------"
echo "[TEST 3] Command: ./compiler simple.lr -s"
$COMPILER simple.lr -s >/dev/null 2>&1
if [ -f "simple" ] && [ -f "simple.ll" ]; then
    echo "[OUTPUT]"
    echo "Generated Binary: simple (exists)"
    echo "Preserved LLVM IR: simple.ll (exists)"
    PASSED=$((PASSED + 1))
else
    echo "[ERROR] Missing simple or simple.ll"
    FAILED=$((FAILED + 1))
fi
cleanup

# ----------------------------------------------------------
# Test 4: Flag -o (Object file output)
# ----------------------------------------------------------
echo "------------------------------------------------------------"
echo "[TEST 4] Command: ./compiler simple.lr -o"
$COMPILER simple.lr -o >/dev/null 2>&1
if [ -f "simple.o" ] && [ ! -f "simple" ]; then
    echo "[OUTPUT]"
    echo "Generated Object File: simple.o (exists, executable omitted as requested by -o)"
    PASSED=$((PASSED + 1))
else
    echo "[ERROR] Object file simple.o was not created"
    FAILED=$((FAILED + 1))
fi
cleanup

# ----------------------------------------------------------
# Test 5: Flag -o with -s (Object file and save .ll)
# ----------------------------------------------------------
echo "------------------------------------------------------------"
echo "[TEST 5] Command: ./compiler simple.lr -o -s"
$COMPILER simple.lr -o -s >/dev/null 2>&1
if [ -f "simple.o" ] && [ -f "simple.ll" ]; then
    echo "[OUTPUT]"
    echo "Generated Object File: simple.o (exists)"
    echo "Preserved LLVM IR: simple.ll (exists)"
    PASSED=$((PASSED + 1))
else
    echo "[ERROR] Missing simple.o or simple.ll"
    FAILED=$((FAILED + 1))
fi
cleanup

# ----------------------------------------------------------
# Test 6: Flag -oall (Batch compile all .lr to .o)
# ----------------------------------------------------------
echo "------------------------------------------------------------"
echo "[TEST 6] Command: ./compiler -oall"
echo "[OUTPUT]"
# Keep only mod_a.lr and mod_b.lr for clean batch testing
mv simple.lr simple.lr.bak
mv error_prog.lr error_prog.lr.bak 2>/dev/null

OUT=$($COMPILER -oall 2>&1)
echo "$OUT"
if [ -f "mod_a.o" ] && [ -f "mod_b.o" ]; then
    echo "Compiled modules: mod_a.o, mod_b.o"
    PASSED=$((PASSED + 1))
else
    echo "[ERROR] mod_a.o or mod_b.o not found"
    FAILED=$((FAILED + 1))
fi

# ----------------------------------------------------------
# Test 7: Flag -iall (Batch link all .o to default 'program')
# ----------------------------------------------------------
echo "------------------------------------------------------------"
echo "[TEST 7] Command: ./compiler -iall && ./program"
echo "[OUTPUT]"
OUT=$($COMPILER -iall 2>&1)
echo "$OUT"
if [ -f "program" ]; then
    RUN_OUT=$(./program)
    echo "$RUN_OUT"
    if echo "$RUN_OUT" | grep -q "40"; then
        PASSED=$((PASSED + 1))
    else
        echo "[ERROR] Unexpected program output"
        FAILED=$((FAILED + 1))
    fi
    rm -f program
else
    echo "[ERROR] Executable 'program' not created"
    FAILED=$((FAILED + 1))
fi

# ----------------------------------------------------------
# Test 8: Flag -iall with -ns <name> (Batch link to custom name)
# ----------------------------------------------------------
echo "------------------------------------------------------------"
echo "[TEST 8] Command: ./compiler -iall -ns custom_app && ./custom_app"
echo "[OUTPUT]"
OUT=$($COMPILER -iall -ns custom_app 2>&1)
echo "$OUT"
if [ -f "custom_app" ]; then
    RUN_OUT=$(./custom_app)
    echo "$RUN_OUT"
    if echo "$RUN_OUT" | grep -q "40"; then
        PASSED=$((PASSED + 1))
    else
        echo "[ERROR] Unexpected custom_app output"
        FAILED=$((FAILED + 1))
    fi
    rm -f custom_app
else
    echo "[ERROR] Executable 'custom_app' not created"
    FAILED=$((FAILED + 1))
fi

# Restore backed up files
mv simple.lr.bak simple.lr
mv error_prog.lr.bak error_prog.lr 2>/dev/null
cleanup

# ----------------------------------------------------------
# Test 9: Flag -ns without parameter (Error checking)
# ----------------------------------------------------------
echo "------------------------------------------------------------"
echo "[TEST 9] Command: ./compiler -ns (Missing parameter error test)"
echo "[OUTPUT]"
OUT=$($COMPILER -ns 2>&1)
echo "$OUT"
if echo "$OUT" | grep -qi "requires a name parameter"; then
    PASSED=$((PASSED + 1))
else
    echo "[ERROR] Did not show required parameter error"
    FAILED=$((FAILED + 1))
fi

# ----------------------------------------------------------
# Test 10: Unknown Flag (Error checking)
# ----------------------------------------------------------
echo "------------------------------------------------------------"
echo "[TEST 10] Command: ./compiler simple.lr -invalid_flag (Unknown flag error test)"
echo "[OUTPUT]"
OUT=$($COMPILER simple.lr -invalid_flag 2>&1)
echo "$OUT"
if echo "$OUT" | grep -qi "Unknown flag"; then
    PASSED=$((PASSED + 1))
else
    echo "[ERROR] Did not show unknown flag error"
    FAILED=$((FAILED + 1))
fi

cleanup

echo "------------------------------------------------------------"
echo "=========================================================="
echo "Execution Complete: Total: $((PASSED + FAILED)), Passed: $PASSED, Failed: $FAILED"
echo "=========================================================="

if [ $FAILED -ne 0 ]; then
    exit 1
fi
exit 0
