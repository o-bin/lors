#!/bin/bash
# ==========================================================
# Lors Test Runner Helper for CMake Pipeline
# Compiles, executes, verifies, and immediately removes test binaries
# Shows [OUTPUT] ONLY for LLVM family compilers (Stage 6 / v6-dv)
# Pre-LLVM stages (Stage 0, 1, 2, 3, 4) remain silent (> /dev/null 2>&1)
# ==========================================================
set -e

if [ $# -lt 2 ]; then
    echo "Usage: $0 <compiler_command_or_binary> <test_dir_1> [test_dir_2 ...]"
    exit 1
fi

COMPILER="$1"
shift
TEST_DIRS=("$@")

# Determine if compiler belongs to LLVM family
IS_LLVM=0
if echo "$COMPILER" | grep -q -E "v6-dv|llvm"; then
    IS_LLVM=1
fi

passed=0
failed=0

echo "=========================================================="
echo "Running Tests using Compiler: $COMPILER"
echo "Directories: ${TEST_DIRS[*]}"
echo "=========================================================="

for dir in "${TEST_DIRS[@]}"; do
    if [ ! -d "$dir" ]; then
        echo "Warning: Test directory not found: $dir"
        continue
    fi

    for src in "$dir"/*.lr; do
        if [ ! -f "$src" ]; then continue; fi
        if echo "$src" | grep -q "\.inc"; then continue; fi

        exe="${src%.lr}"
        echo "----------------------------------------------------------"
        echo "[FILE] $src"

        # Compile
        if [ "$IS_LLVM" -eq 1 ]; then
            if ! eval "$COMPILER \"$src\""; then
                echo "[FAIL] Compilation failed for $src"
                failed=$((failed + 1))
                continue
            fi
        else
            if ! eval "$COMPILER \"$src\" > /dev/null 2>&1"; then
                echo "[FAIL] Compilation failed for $src"
                failed=$((failed + 1))
                continue
            fi
        fi

        if [ ! -f "$exe" ]; then
            echo "[FAIL] Executable not generated: $exe"
            failed=$((failed + 1))
            continue
        fi

        # Execute with appropriate input/args
        set +e
        if [ "$IS_LLVM" -eq 1 ]; then
            echo "[OUTPUT]"
            if echo "$exe" | grep -q "test_calculator"; then
                printf "1\n10\n20\n" | "$exe"
            elif echo "$exe" | grep -q "test_string_input"; then
                printf "HelloInput\n" | "$exe"
            elif echo "$exe" | grep -q "test_cli_args_basic"; then
                "$exe" arg1 arg2
            elif echo "$exe" | grep -q "test_cli_args_usage"; then
                "$exe" myargument
            else
                "$exe"
            fi
            ret=$?
        else
            if echo "$exe" | grep -q "test_calculator"; then
                printf "1\n10\n20\n" | "$exe" > /dev/null 2>&1
            elif echo "$exe" | grep -q "test_string_input"; then
                printf "HelloInput\n" | "$exe" > /dev/null 2>&1
            elif echo "$exe" | grep -q "test_cli_args_basic"; then
                "$exe" arg1 arg2 > /dev/null 2>&1
            elif echo "$exe" | grep -q "test_cli_args_usage"; then
                "$exe" myargument > /dev/null 2>&1
            else
                "$exe" > /dev/null 2>&1
            fi
            ret=$?
        fi
        set -e

        # Clean up test binary immediately
        rm -f "$exe" "$exe.o" "$exe.ll" "$exe.cpp"

        if [ $ret -ne 0 ]; then
            echo "[FAIL] Execution exited with error code $ret"
            failed=$((failed + 1))
        else
            echo "[PASS] $src"
            passed=$((passed + 1))
        fi
    done
done

echo "=========================================================="
echo "Test Execution Summary: Passed: $passed, Failed: $failed"
echo "=========================================================="

if [ $failed -ne 0 ]; then
    echo "ERROR: Test suite failed! Aborting pipeline."
    exit 1
fi
