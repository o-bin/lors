cmake_minimum_required(VERSION 3.20)
project(Lors_Bootstrap_Pipeline LANGUAGES C CXX)

find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MAIN_DIR "${ROOT_DIR}/main")
set(TEST_RUNNER "${ROOT_DIR}/cmake/install.sh")

# ==============================================================================
# STAGE 0: Python Compiler Tests (main/compiler.py)
# ==============================================================================
add_custom_target(test_stage0
    COMMAND "${TEST_RUNNER}" "${Python3_EXECUTABLE} ${MAIN_DIR}/compiler.py" "${MAIN_DIR}/lors/examples" "${MAIN_DIR}/lors/tests"
    WORKING_DIRECTORY "${MAIN_DIR}"
    COMMENT ">>> [STAGE 0 TEST] Running and verifying tests with Python compiler (Stage 0)..."
)

# ==============================================================================
# STAGE 0 -> STAGE 1: Bootstrap Compiler (lors_bootstrap)
# ==============================================================================
add_custom_command(
    OUTPUT "${MAIN_DIR}/lors_bootstrap"
    COMMAND ${Python3_EXECUTABLE} "${MAIN_DIR}/compiler.py" "${MAIN_DIR}/lors_bootstrap.lr"
    WORKING_DIRECTORY "${MAIN_DIR}"
    DEPENDS test_stage0 "${MAIN_DIR}/compiler.py" "${MAIN_DIR}/lors_bootstrap.lr"
    COMMENT ">>> [STAGE 1] Compiling lors_bootstrap.lr using Python compiler (Stage 0)..."
)
add_custom_target(stage1_bootstrap DEPENDS "${MAIN_DIR}/lors_bootstrap")

# Test Stage 1: Must pass 100% before advancing to Stage 2
add_custom_target(test_stage1
    COMMAND "${TEST_RUNNER}" "${MAIN_DIR}/lors_bootstrap" "${MAIN_DIR}/lors/examples" "${MAIN_DIR}/lors/tests"
    WORKING_DIRECTORY "${MAIN_DIR}"
    DEPENDS stage1_bootstrap
    COMMENT ">>> [STAGE 1 TEST] Running and verifying tests with lors_bootstrap..."
)

# ==============================================================================
# STAGE 1 -> STAGE 2: Twin Compiler (twin)
# ==============================================================================
add_custom_command(
    OUTPUT "${MAIN_DIR}/twin"
    COMMAND "${MAIN_DIR}/lors_bootstrap" "${MAIN_DIR}/twin.lr"
    WORKING_DIRECTORY "${MAIN_DIR}"
    DEPENDS test_stage1 "${MAIN_DIR}/twin.lr"
    COMMENT ">>> [STAGE 2] Compiling twin.lr using lors_bootstrap (Stage 1)..."
)
add_custom_target(stage2_twin DEPENDS "${MAIN_DIR}/twin")

# Test Stage 2: Must pass 100% before advancing to Stage 3
add_custom_target(test_stage2
    COMMAND "${TEST_RUNNER}" "${MAIN_DIR}/twin" "${MAIN_DIR}/lors/examples" "${MAIN_DIR}/lors/tests"
    WORKING_DIRECTORY "${MAIN_DIR}"
    DEPENDS stage2_twin
    COMMENT ">>> [STAGE 2 TEST] Running and verifying tests with twin..."
)

# ==============================================================================
# STAGE 2 -> STAGE 3: Self Compiler S (Stage 3 binary)
# ==============================================================================
add_custom_command(
    OUTPUT "${MAIN_DIR}/self_compiler_s/stage3_compiler"
    COMMAND "${MAIN_DIR}/twin" "${MAIN_DIR}/self_compiler_s/lors_bootstrap.lr"
    COMMAND ${CMAKE_COMMAND} -E rename "${MAIN_DIR}/self_compiler_s/lors_bootstrap" "${MAIN_DIR}/self_compiler_s/stage3_compiler"
    WORKING_DIRECTORY "${MAIN_DIR}"
    DEPENDS test_stage2 "${MAIN_DIR}/self_compiler_s/lors_bootstrap.lr"
    COMMENT ">>> [STAGE 3] Compiling self_compiler_s/lors_bootstrap.lr using twin (Stage 2)..."
)
add_custom_target(stage3_compiler DEPENDS "${MAIN_DIR}/self_compiler_s/stage3_compiler")

# Test Stage 3: Must pass 100% before advancing to Stage 4
add_custom_target(test_stage3
    COMMAND "${TEST_RUNNER}" "${MAIN_DIR}/self_compiler_s/stage3_compiler" "${MAIN_DIR}/lors/examples" "${MAIN_DIR}/lors/tests" "${MAIN_DIR}/test_v2"
    WORKING_DIRECTORY "${MAIN_DIR}"
    DEPENDS stage3_compiler
    COMMENT ">>> [STAGE 3 TEST] Running and verifying tests with stage3_compiler..."
)

# ==============================================================================
# STAGE 3 -> STAGE 4: Self-Compiled S via stage4.lr (Repeating Clause 3)
# ==============================================================================
add_custom_command(
    OUTPUT "${MAIN_DIR}/self_compiler_s/stage4" "${MAIN_DIR}/self_compiler_s/compiler"
    COMMAND "${MAIN_DIR}/self_compiler_s/stage3_compiler" "${MAIN_DIR}/self_compiler_s/stage4.lr"
    COMMAND ${CMAKE_COMMAND} -E copy "${MAIN_DIR}/self_compiler_s/stage4" "${MAIN_DIR}/self_compiler_s/compiler"
    WORKING_DIRECTORY "${MAIN_DIR}"
    DEPENDS test_stage3 "${MAIN_DIR}/self_compiler_s/stage4.lr"
    COMMENT ">>> [STAGE 4] Compiling self_compiler_s/stage4.lr using stage3_compiler (Stage 3)..."
)
add_custom_target(stage4_self_compiled DEPENDS "${MAIN_DIR}/self_compiler_s/stage4")

# Test Stage 4: Must pass 100% before advancing to Stage 5
add_custom_target(test_stage4
    COMMAND "${TEST_RUNNER}" "${MAIN_DIR}/self_compiler_s/stage4" "${MAIN_DIR}/lors/examples" "${MAIN_DIR}/lors/tests" "${MAIN_DIR}/test_v2"
    WORKING_DIRECTORY "${MAIN_DIR}"
    DEPENDS stage4_self_compiled
    COMMENT ">>> [STAGE 4 TEST] Running and verifying tests with Stage 4 compiler (stage4)..."
)

# ==============================================================================
# STAGE 4 -> STAGE 5: Native LLVM Compiler (self_hosted_v5/lors_compiler)
# ==============================================================================
add_custom_command(
    OUTPUT "${MAIN_DIR}/self_hosted_v5/lors_compiler"
    COMMAND "${MAIN_DIR}/self_compiler_s/stage4" "lors_compiler.lr" "-o"
    COMMAND ${CMAKE_CXX_COMPILER} "lors_compiler.o" "-o" "lors_compiler"
    COMMAND ${CMAKE_COMMAND} -E remove "lors_compiler.o"
    WORKING_DIRECTORY "${MAIN_DIR}/self_hosted_v5"
    DEPENDS test_stage4 "${MAIN_DIR}/self_hosted_v5/lors_compiler.lr"
    COMMENT ">>> [STAGE 5] Compiling self_hosted_v5/lors_compiler.lr using Stage 4 compiler (stage4)..."
)
add_custom_target(stage5_llvm DEPENDS "${MAIN_DIR}/self_hosted_v5/lors_compiler")

# Test Stage 5 (Using universal_test/test_runner from inside self_hosted_v5)
add_custom_command(
    OUTPUT "${MAIN_DIR}/universal_test/test_runner"
    COMMAND "${MAIN_DIR}/self_compiler_s/stage4" "test_runner.lr" "-o"
    COMMAND ${CMAKE_CXX_COMPILER} "test_runner.o" "-o" "test_runner"
    COMMAND ${CMAKE_COMMAND} -E remove "test_runner.o"
    WORKING_DIRECTORY "${MAIN_DIR}/universal_test"
    DEPENDS stage5_llvm "${MAIN_DIR}/universal_test/test_runner.lr"
    COMMENT ">>> [STAGE 5] Building universal_test/test_runner using Stage 4 compiler..."
)

add_custom_target(test_stage5
    COMMAND "${MAIN_DIR}/universal_test/test_runner"
    COMMAND ${CMAKE_COMMAND} -E remove "${MAIN_DIR}/universal_test/test_runner"
    WORKING_DIRECTORY "${MAIN_DIR}/self_hosted_v5"
    DEPENDS "${MAIN_DIR}/universal_test/test_runner"
    COMMENT ">>> [STAGE 5 TEST] Running universal_test/test_runner inside self_hosted_v5..."
)

# ==============================================================================
# STAGE 5 -> STAGE 6: Modular Monolithic Seed (v6-dv/compiler)
# ==============================================================================
add_custom_command(
    OUTPUT "${MAIN_DIR}/v6-dv/compiler"
    COMMAND "${MAIN_DIR}/self_hosted_v5/lors_compiler" "compiler.lr"
    WORKING_DIRECTORY "${MAIN_DIR}/v6-dv"
    DEPENDS test_stage5 "${MAIN_DIR}/v6-dv/compiler.lr"
    COMMENT ">>> [STAGE 6] Compiling v6-dv/compiler.lr using self_hosted_v5 (Stage 5)..."
)
add_custom_target(stage6_seed DEPENDS "${MAIN_DIR}/v6-dv/compiler")

# Test Stage 6: Must pass 100% before advancing to Stage 7
add_custom_target(test_stage6
    COMMAND "${TEST_RUNNER}" "${MAIN_DIR}/v6-dv/compiler" "${MAIN_DIR}/v6-dv/examples" "${MAIN_DIR}/v6-dv/tests"
    WORKING_DIRECTORY "${MAIN_DIR}/v6-dv"
    DEPENDS stage6_seed
    COMMENT ">>> [STAGE 6 TEST] Running and verifying tests with v6-dv/compiler..."
)

# ==============================================================================
# STAGE 6 -> STAGE 7: Modular Compiler Dev & The Singularity (v6-dv/compiler_dev)
# ==============================================================================
add_custom_command(
    OUTPUT "${MAIN_DIR}/v6-dv/compiler_dev"
    COMMAND ./build_all_modules.sh
    COMMAND ./link_all_modules.sh
    WORKING_DIRECTORY "${MAIN_DIR}/v6-dv"
    DEPENDS test_stage6
    COMMENT ">>> [STAGE 7] Building 68 modular objects and linking compiler_dev (Stage 7)..."
)
add_custom_target(stage7_modular DEPENDS "${MAIN_DIR}/v6-dv/compiler_dev")

# Test Stage 7: Runs complete test-all on compiler_dev
add_custom_target(test_stage7
    COMMAND make -f Makefile_dev test-all
    WORKING_DIRECTORY "${MAIN_DIR}/v6-dv"
    DEPENDS stage7_modular
    COMMENT ">>> [STAGE 7 TEST] Running complete 100% test suite with compiler_dev..."
)

# ==============================================================================
# CLEAN ALL TARGET (Removes all stage compilers, .o objects, and temp files)
# ==============================================================================
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove -f
        "${MAIN_DIR}/lors_bootstrap"
        "${MAIN_DIR}/twin"
        "${MAIN_DIR}/build_check"
        "${MAIN_DIR}/ns_compiler"
        "${MAIN_DIR}/lors_bootstrap.o"
        "${MAIN_DIR}/self_compiler_s/stage3_compiler"
        "${MAIN_DIR}/self_compiler_s/stage4"
        "${MAIN_DIR}/self_compiler_s/compiler"
        "${MAIN_DIR}/self_compiler_s/original"
        "${MAIN_DIR}/self_hosted_v5/lors_compiler"
        "${MAIN_DIR}/self_hosted_v5/lors_compiler.o"
        "${MAIN_DIR}/self_hosted_v5/test_inquire_simple"
        "${MAIN_DIR}/universal_test/test"
        "${MAIN_DIR}/universal_test/test_runner"
        "${MAIN_DIR}/v6-dv/compiler"
        "${MAIN_DIR}/v6-dv/compiler_dev"
    COMMAND bash -c "rm -f ${MAIN_DIR}/flags_test/*.o ${MAIN_DIR}/flags_test/test_prog ${MAIN_DIR}/v6-dv/*.o ${MAIN_DIR}/v6-dv/*.ll ${MAIN_DIR}/v6-dv/build_modular_objs/*.o ${MAIN_DIR}/v6-dv/build_modular_objs/*.ll ${MAIN_DIR}/lors/tests/*.o ${MAIN_DIR}/v6-dv/tests/*.o"
    WORKING_DIRECTORY "${ROOT_DIR}"
    COMMENT ">>> [CLEAN ALL] Removed all stage compilers, object files (.o), and build artifacts."
)

# Master All Target
add_custom_target(all_stages ALL DEPENDS test_stage7)
