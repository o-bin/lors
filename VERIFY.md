zx@zx:~/projects/6ls/build$ cmake ..
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/zx/projects/6ls/build
zx@zx:~/projects/6ls/build$ cmake --build .
[  6%] >>> [STAGE 0 TEST] Running and verifying tests with Python compiler (Stage 0)...
==========================================================
Running Tests using Compiler: /usr/bin/python3 /home/zx/projects/6ls/main/compiler.py
Directories: /home/zx/projects/6ls/main/lors/examples /home/zx/projects/6ls/main/lors/tests
==========================================================
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/calculation.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/calculation.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/hello.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/hello.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/logic.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/logic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/edge_cases.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/edge_cases.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_adv_math_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_adv_math_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_access.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_access.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_decl.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_decl.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_file_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_file_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_modify.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_modify.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_no_mod_yet.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_no_mod_yet.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_bool_logic_complex.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_bool_logic_complex.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_calculator.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_calculator.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_chain_add.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_chain_add.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_chemistry_molar.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_chemistry_molar.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_cli_args_basic.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_cli_args_basic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_cli_args_usage.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_cli_args_usage.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_empty_array.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_empty_array.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_even_odd.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_even_odd.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_factorial.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_factorial.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fibonacci.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fibonacci.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_file_custom_ext.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_file_custom_ext.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_file_write_read.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_file_write_read.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_float_ops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_float_ops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_delete_file.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_delete_file.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_exists_check.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_exists_check.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_io_flow.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_io_flow.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_hypotenuse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_hypotenuse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_inc_a.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_inc_a.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_is_alnum.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_is_alnum.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_and.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_and.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_mixed.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_mixed.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_not.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_not.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_or.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_or.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_loop_sum.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_loop_sum.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_abs.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_abs.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_pi.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_pi.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_pow.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_pow.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_root.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_root.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_trig.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_trig.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_mixed_parsing.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_mixed_parsing.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_logic_advanced.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_logic_advanced.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_loops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_loops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_verify.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_verify.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_order_ops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_order_ops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_os_env_read.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_os_env_read.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_os_system_call.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_os_system_call.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_physics_gravity.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_physics_gravity.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_prime_stub.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_prime_stub.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_case.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_case.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_float_parse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_float_parse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_string_input.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_string_input.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_lib_combo.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_lib_combo.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_reverse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_reverse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_search.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_search.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_types.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_types.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_access.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_access.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_array.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_array.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_basic.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_basic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_func.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_func.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_nested.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_nested.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_system_echo.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_system_echo.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_terminal_ls.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_terminal_ls.lr
==========================================================
Test Execution Summary: Passed: 63, Failed: 0
==========================================================
[  6%] Built target test_stage0
[ 12%] >>> [STAGE 1] Compiling lors_bootstrap.lr using Python compiler (Stage 0)...
[ 12%] Built target stage1_bootstrap
[ 18%] >>> [STAGE 1 TEST] Running and verifying tests with lors_bootstrap...
==========================================================
Running Tests using Compiler: /home/zx/projects/6ls/main/lors_bootstrap
Directories: /home/zx/projects/6ls/main/lors/examples /home/zx/projects/6ls/main/lors/tests
==========================================================
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/calculation.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/calculation.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/hello.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/hello.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/logic.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/logic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/edge_cases.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/edge_cases.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_adv_math_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_adv_math_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_access.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_access.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_decl.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_decl.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_file_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_file_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_modify.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_modify.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_no_mod_yet.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_no_mod_yet.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_bool_logic_complex.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_bool_logic_complex.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_calculator.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_calculator.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_chain_add.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_chain_add.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_chemistry_molar.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_chemistry_molar.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_cli_args_basic.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_cli_args_basic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_cli_args_usage.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_cli_args_usage.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_empty_array.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_empty_array.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_even_odd.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_even_odd.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_factorial.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_factorial.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fibonacci.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fibonacci.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_file_custom_ext.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_file_custom_ext.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_file_write_read.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_file_write_read.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_float_ops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_float_ops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_delete_file.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_delete_file.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_exists_check.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_exists_check.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_io_flow.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_io_flow.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_hypotenuse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_hypotenuse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_inc_a.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_inc_a.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_is_alnum.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_is_alnum.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_and.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_and.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_mixed.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_mixed.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_not.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_not.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_or.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_or.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_loop_sum.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_loop_sum.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_abs.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_abs.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_pi.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_pi.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_pow.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_pow.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_root.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_root.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_trig.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_trig.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_mixed_parsing.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_mixed_parsing.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_logic_advanced.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_logic_advanced.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_loops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_loops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_verify.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_verify.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_order_ops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_order_ops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_os_env_read.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_os_env_read.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_os_system_call.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_os_system_call.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_physics_gravity.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_physics_gravity.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_prime_stub.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_prime_stub.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_case.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_case.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_float_parse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_float_parse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_string_input.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_string_input.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_lib_combo.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_lib_combo.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_reverse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_reverse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_search.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_search.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_types.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_types.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_access.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_access.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_array.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_array.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_basic.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_basic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_func.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_func.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_nested.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_nested.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_system_echo.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_system_echo.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_terminal_ls.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_terminal_ls.lr
==========================================================
Test Execution Summary: Passed: 63, Failed: 0
==========================================================
[ 18%] Built target test_stage1
[ 25%] >>> [STAGE 2] Compiling twin.lr using lors_bootstrap (Stage 1)...
[ 25%] Built target stage2_twin
[ 31%] >>> [STAGE 2 TEST] Running and verifying tests with twin...
==========================================================
Running Tests using Compiler: /home/zx/projects/6ls/main/twin
Directories: /home/zx/projects/6ls/main/lors/examples /home/zx/projects/6ls/main/lors/tests
==========================================================
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/calculation.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/calculation.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/hello.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/hello.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/logic.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/logic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/edge_cases.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/edge_cases.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_adv_math_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_adv_math_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_access.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_access.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_decl.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_decl.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_file_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_file_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_modify.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_modify.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_no_mod_yet.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_no_mod_yet.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_bool_logic_complex.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_bool_logic_complex.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_calculator.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_calculator.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_chain_add.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_chain_add.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_chemistry_molar.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_chemistry_molar.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_cli_args_basic.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_cli_args_basic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_cli_args_usage.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_cli_args_usage.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_empty_array.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_empty_array.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_even_odd.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_even_odd.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_factorial.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_factorial.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fibonacci.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fibonacci.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_file_custom_ext.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_file_custom_ext.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_file_write_read.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_file_write_read.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_float_ops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_float_ops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_delete_file.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_delete_file.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_exists_check.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_exists_check.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_io_flow.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_io_flow.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_hypotenuse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_hypotenuse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_inc_a.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_inc_a.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_is_alnum.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_is_alnum.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_and.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_and.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_mixed.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_mixed.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_not.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_not.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_or.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_or.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_loop_sum.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_loop_sum.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_abs.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_abs.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_pi.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_pi.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_pow.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_pow.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_root.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_root.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_trig.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_trig.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_mixed_parsing.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_mixed_parsing.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_logic_advanced.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_logic_advanced.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_loops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_loops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_verify.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_verify.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_order_ops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_order_ops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_os_env_read.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_os_env_read.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_os_system_call.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_os_system_call.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_physics_gravity.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_physics_gravity.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_prime_stub.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_prime_stub.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_case.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_case.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_float_parse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_float_parse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_string_input.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_string_input.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_lib_combo.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_lib_combo.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_reverse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_reverse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_search.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_search.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_types.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_types.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_access.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_access.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_array.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_array.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_basic.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_basic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_func.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_func.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_nested.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_nested.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_system_echo.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_system_echo.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_terminal_ls.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_terminal_ls.lr
==========================================================
Test Execution Summary: Passed: 63, Failed: 0
==========================================================
[ 31%] Built target test_stage2
[ 37%] >>> [STAGE 3] Compiling self_compiler_s/lors_bootstrap.lr using twin (Stage 2)...
[ 37%] Built target stage3_compiler
[ 43%] >>> [STAGE 3 TEST] Running and verifying tests with stage3_compiler...
==========================================================
Running Tests using Compiler: /home/zx/projects/6ls/main/self_compiler_s/stage3_compiler
Directories: /home/zx/projects/6ls/main/lors/examples /home/zx/projects/6ls/main/lors/tests /home/zx/projects/6ls/main/test_v2
==========================================================
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/calculation.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/calculation.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/hello.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/hello.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/logic.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/logic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/edge_cases.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/edge_cases.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_adv_math_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_adv_math_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_access.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_access.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_decl.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_decl.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_file_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_file_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_modify.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_modify.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_no_mod_yet.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_no_mod_yet.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_bool_logic_complex.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_bool_logic_complex.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_calculator.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_calculator.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_chain_add.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_chain_add.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_chemistry_molar.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_chemistry_molar.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_cli_args_basic.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_cli_args_basic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_cli_args_usage.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_cli_args_usage.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_empty_array.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_empty_array.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_even_odd.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_even_odd.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_factorial.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_factorial.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fibonacci.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fibonacci.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_file_custom_ext.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_file_custom_ext.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_file_write_read.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_file_write_read.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_float_ops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_float_ops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_delete_file.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_delete_file.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_exists_check.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_exists_check.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_io_flow.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_io_flow.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_hypotenuse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_hypotenuse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_inc_a.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_inc_a.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_is_alnum.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_is_alnum.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_and.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_and.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_mixed.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_mixed.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_not.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_not.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_or.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_or.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_loop_sum.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_loop_sum.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_abs.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_abs.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_pi.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_pi.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_pow.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_pow.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_root.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_root.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_trig.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_trig.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_mixed_parsing.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_mixed_parsing.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_logic_advanced.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_logic_advanced.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_loops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_loops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_verify.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_verify.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_order_ops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_order_ops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_os_env_read.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_os_env_read.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_os_system_call.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_os_system_call.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_physics_gravity.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_physics_gravity.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_prime_stub.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_prime_stub.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_case.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_case.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_float_parse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_float_parse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_string_input.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_string_input.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_lib_combo.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_lib_combo.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_reverse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_reverse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_search.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_search.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_types.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_types.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_access.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_access.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_array.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_array.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_basic.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_basic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_func.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_func.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_nested.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_nested.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_system_echo.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_system_echo.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_terminal_ls.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_terminal_ls.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/test_v2/simple.lr
[PASS] /home/zx/projects/6ls/main/test_v2/simple.lr
==========================================================
Test Execution Summary: Passed: 64, Failed: 0
==========================================================
[ 43%] Built target test_stage3
[ 50%] >>> [STAGE 4] Compiling self_compiler_s/stage4.lr using stage3_compiler (Stage 3)...
Compiling: /home/zx/projects/6ls/main/self_compiler_s/stage4.lr
[ 50%] Built target stage4_self_compiled
[ 56%] >>> [STAGE 4 TEST] Running and verifying tests with Stage 4 compiler (stage4)...
==========================================================
Running Tests using Compiler: /home/zx/projects/6ls/main/self_compiler_s/stage4
Directories: /home/zx/projects/6ls/main/lors/examples /home/zx/projects/6ls/main/lors/tests /home/zx/projects/6ls/main/test_v2
==========================================================
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/calculation.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/calculation.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/hello.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/hello.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/examples/logic.lr
[PASS] /home/zx/projects/6ls/main/lors/examples/logic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/edge_cases.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/edge_cases.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_adv_math_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_adv_math_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_access.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_access.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_decl.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_decl.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_file_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_file_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_modify.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_modify.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_array_no_mod_yet.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_array_no_mod_yet.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_bool_logic_complex.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_bool_logic_complex.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_calculator.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_calculator.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_chain_add.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_chain_add.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_chemistry_molar.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_chemistry_molar.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_cli_args_basic.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_cli_args_basic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_cli_args_usage.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_cli_args_usage.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_empty_array.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_empty_array.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_even_odd.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_even_odd.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_factorial.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_factorial.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fibonacci.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fibonacci.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_file_custom_ext.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_file_custom_ext.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_file_write_read.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_file_write_read.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_float_ops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_float_ops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_delete_file.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_delete_file.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_exists_check.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_exists_check.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_fs_io_flow.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_fs_io_flow.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_hypotenuse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_hypotenuse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_inc_a.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_inc_a.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_is_alnum.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_is_alnum.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_and.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_and.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_mixed.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_mixed.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_not.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_not.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_logic_or.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_logic_or.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_loop_sum.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_loop_sum.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_abs.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_abs.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_pi.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_pi.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_pow.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_pow.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_root.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_root.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_math_trig.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_math_trig.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_mixed_parsing.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_mixed_parsing.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_logic_advanced.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_logic_advanced.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_loops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_loops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_nested_verify.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_nested_verify.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_order_ops.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_order_ops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_os_env_read.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_os_env_read.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_os_system_call.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_os_system_call.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_physics_gravity.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_physics_gravity.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_prime_stub.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_prime_stub.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_case.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_case.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_float_parse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_float_parse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_string_input.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_string_input.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_lib_combo.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_lib_combo.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_reverse.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_reverse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_search.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_search.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_str_types.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_str_types.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_access.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_access.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_array.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_array.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_basic.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_basic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_func.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_func.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_io.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_struct_nested.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_struct_nested.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_system_echo.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_system_echo.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/lors/tests/test_terminal_ls.lr
[PASS] /home/zx/projects/6ls/main/lors/tests/test_terminal_ls.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/test_v2/simple.lr
[PASS] /home/zx/projects/6ls/main/test_v2/simple.lr
==========================================================
Test Execution Summary: Passed: 64, Failed: 0
==========================================================
[ 56%] Built target test_stage4
[ 62%] >>> [STAGE 5] Compiling self_hosted_v5/lors_compiler.lr using Stage 4 compiler (stage4)...
Compiling: lors_compiler.lr
[ 62%] Built target stage5_llvm
[ 68%] >>> [STAGE 5] Building universal_test/test_runner using Stage 4 compiler...
Compiling: test_runner.lr
[ 75%] >>> [STAGE 5 TEST] Running universal_test/test_runner inside self_hosted_v5...
========================================
   UNIVERSAL TEST RUNNER (SELF-HOSTED)
========================================
Checking directory: lors/examples
>> TEST: ../lors/examples/calculation.lr
   Compiling...
   Output:
   -------
107
93
700
14
7.000000
   -------
   [PASS]

>> TEST: ../lors/examples/hello.lr
   Compiling...
   Output:
   -------
Hello, Lors!
30
x is smaller
0
1
2
3
4
   -------
   [PASS]

>> TEST: ../lors/examples/logic.lr
   Compiling...
   Output:
   -------
Condition is true
Looping...
Looping...
Looping...
Loop finished
   -------
   [PASS]

Checking directory: lors/tests
>> TEST: ../lors/tests/edge_cases.lr
   Compiling...
   Output:
   -------
120
Factorial correct
   -------
   [PASS]

>> TEST: ../lors/tests/test_adv_math_io.lr
   Compiling...
   Output:
   -------
78.539750
   -------
   [PASS]

>> TEST: ../lors/tests/test_array_access.lr
   Compiling...
   Output:
   -------
20
   -------
   [PASS]

>> TEST: ../lors/tests/test_array_decl.lr
   Compiling...
   Output:
   -------
   -------
   [PASS]

>> TEST: ../lors/tests/test_array_file_io.lr
   Compiling...
   Output:
   -------
1, 2, 3
   -------
   [PASS]

>> TEST: ../lors/tests/test_array_modify.lr
   Compiling...
   Output:
   -------
99
2
198
6
   -------
   [PASS]

>> TEST: ../lors/tests/test_array_no_mod_yet.lr
   Compiling...
   Output:
   -------
   -------
   [PASS]

>> TEST: ../lors/tests/test_bool_logic_complex.lr
   Compiling...
   Output:
   -------
Complex logic pass
Negation pass
   -------
   [PASS]

>> TEST: ../lors/tests/test_calculator.lr
   Compiling...
   Input: 1, 10, 20
   Output:
   -------
Enter operation (1=add, 2=sub, 3=mul, 4=div):
Enter first number:
Enter second number:
Result:
30.000000
   -------
   [PASS]

>> TEST: ../lors/tests/test_chain_add.lr
   Compiling...
   Output:
   -------
6.000000
   -------
   [PASS]

>> TEST: ../lors/tests/test_chemistry_molar.lr
   Compiling...
   Output:
   -------
Mass of water:
36.030000
   -------
   [PASS]

>> TEST: ../lors/tests/test_cli_args_basic.lr
   Compiling...
   Args: arg1 arg2
   Output:
   -------
3
./../lors/tests/test_cli_args_basic
arg1
arg2
   -------
   [PASS]

>> TEST: ../lors/tests/test_cli_args_usage.lr
   Compiling...
   Args: myargument
   Output:
   -------
First arg:
myargument
   -------
   [PASS]

>> TEST: ../lors/tests/test_empty_array.lr
   Compiling...
   Output:
   -------
   -------
   [PASS]

>> TEST: ../lors/tests/test_even_odd.lr
   Compiling...
   Output:
   -------
Even
   -------
   [PASS]

>> TEST: ../lors/tests/test_factorial.lr
   Compiling...
   Output:
   -------
120
   -------
   [PASS]

>> TEST: ../lors/tests/test_fibonacci.lr
   Compiling...
   Output:
   -------
0
1
1
2
3
5
8
13
21
34
   -------
   [PASS]

>> TEST: ../lors/tests/test_file_custom_ext.lr
   Compiling...
   Output:
   -------
key=value
   -------
   [PASS]

>> TEST: ../lors/tests/test_file_write_read.lr
   Compiling...
   Output:
   -------
Hello File I/O
File read/write successful
   -------
   [PASS]

>> TEST: ../lors/tests/test_float_ops.lr
   Compiling...
   Output:
   -------
9.500000
   -------
   [PASS]

>> TEST: ../lors/tests/test_fs_delete_file.lr
   Compiling...
   Output:
   -------
File deleted
   -------
   [PASS]

>> TEST: ../lors/tests/test_fs_exists_check.lr
   Compiling...
   Output:
   -------
File exists
   -------
   [PASS]

>> TEST: ../lors/tests/test_fs_io_flow.lr
   Compiling...
   Output:
   -------
Step 1 OK
Step 2 OK
Step 3 OK
   -------
   [PASS]

>> TEST: ../lors/tests/test_hypotenuse.lr
   Compiling...
   Output:
   -------
3.535534
   -------
   [PASS]

>> TEST: ../lors/tests/test_inc_a.lr
   Compiling...
   Output:
   -------
100
   -------
   [PASS]

>> TEST: ../lors/tests/test_is_alnum.lr
   Compiling...
   Output:
   -------
A is alnum
2 is alnum
! is not alnum
   -------
   [PASS]

>> TEST: ../lors/tests/test_logic_and.lr
   Compiling...
   Output:
   -------
Correct
   -------
   [PASS]

>> TEST: ../lors/tests/test_logic_mixed.lr
   Compiling...
   Output:
   -------
Correct
   -------
   [PASS]

>> TEST: ../lors/tests/test_logic_not.lr
   Compiling...
   Output:
   -------
Correct
   -------
   [PASS]

>> TEST: ../lors/tests/test_logic_or.lr
   Compiling...
   Output:
   -------
Correct
   -------
   [PASS]

>> TEST: ../lors/tests/test_loop_sum.lr
   Compiling...
   Output:
   -------
10
   -------
   [PASS]

>> TEST: ../lors/tests/test_math_abs.lr
   Compiling...
   Output:
   -------
-10.500000
   -------
   [PASS]

>> TEST: ../lors/tests/test_math_pi.lr
   Compiling...
   Output:
   -------
-1.000000
   -------
   [PASS]

>> TEST: ../lors/tests/test_math_pow.lr
   Compiling...
   Output:
   -------
8.000000
   -------
   [PASS]

>> TEST: ../lors/tests/test_math_root.lr
   Compiling...
   Output:
   -------
4.000000
   -------
   [PASS]

>> TEST: ../lors/tests/test_math_trig.lr
   Compiling...
   Output:
   -------
0.000000
1.000000
   -------
   [PASS]

>> TEST: ../lors/tests/test_mixed_parsing.lr
   Compiling...
   Output:
   -------
112.500000
Mixed Parse Pass
   -------
   [PASS]

>> TEST: ../lors/tests/test_nested_logic_advanced.lr
   Compiling...
   Output:
   -------
Deep nesting pass
   -------
   [PASS]

>> TEST: ../lors/tests/test_nested_loops.lr
   Compiling...
   Output:
   -------
0
1
10
11
20
21
   -------
   [PASS]

>> TEST: ../lors/tests/test_nested_verify.lr
   Compiling...
   Output:
   -------
Inside range
   -------
   [PASS]

>> TEST: ../lors/tests/test_order_ops.lr
   Compiling...
   Output:
   -------
Order of ops correct
   -------
   [PASS]

>> TEST: ../lors/tests/test_os_env_read.lr
   Compiling...
   Output:
   -------
Read PATH env
Handled missing env
   -------
   [PASS]

>> TEST: ../lors/tests/test_os_system_call.lr
   Compiling...
   Output:
   -------
OS Call
   -------
   [PASS]

>> TEST: ../lors/tests/test_physics_gravity.lr
   Compiling...
   Output:
   -------
Distance fallen:
30.656250
   -------
   [PASS]

>> TEST: ../lors/tests/test_prime_stub.lr
   Compiling...
   Output:
   -------
1
   -------
   [PASS]

>> TEST: ../lors/tests/test_str_case.lr
   Compiling...
   Output:
   -------
HELLO 123
hello 123
Case Pass
   -------
   [PASS]

>> TEST: ../lors/tests/test_str_float_parse.lr
   Compiling...
   Output:
   -------
3.141590
6.283180
Parse Float Pass
   -------
   [PASS]

>> TEST: ../lors/tests/test_str_lib_combo.lr
   Compiling...
   Output:
   -------
Palindrome Detected
Conversion Pass
   -------
   [PASS]

>> TEST: ../lors/tests/test_str_reverse.lr
   Compiling...
   Output:
   -------
dlroW olleH
Reverse Pass
   -------
   [PASS]

>> TEST: ../lors/tests/test_str_search.lr
   Compiling...
   Output:
   -------
Hello
Substring Pass
CharAt Pass
   -------
   [PASS]

>> TEST: ../lors/tests/test_str_types.lr
   Compiling...
   Output:
   -------
Type Check Pass
   -------
   [PASS]

>> TEST: ../lors/tests/test_string_input.lr
   Compiling...
   Input: HelloInput
   Output:
   -------
Enter a word:
You typed:
HelloInput
   -------
   [PASS]

>> TEST: ../lors/tests/test_struct_access.lr
   Compiling...
   Output:
   -------
100
50
Struct Modify Pass
   -------
   [PASS]

>> TEST: ../lors/tests/test_struct_array.lr
   Compiling...
   Output:
   -------
1
2
Struct Array Pass
   -------
   [PASS]

>> TEST: ../lors/tests/test_struct_basic.lr
   Compiling...
   Output:
   -------
10
20
Struct Basic Pass
   -------
   [PASS]

>> TEST: ../lors/tests/test_struct_func.lr
   Compiling...
   Output:
   -------
4
6
Struct Func Pass
   -------
   [PASS]

>> TEST: ../lors/tests/test_struct_io.lr
   Compiling...
   Output:
   -------
localhost:8080
   -------
   [PASS]

>> TEST: ../lors/tests/test_struct_nested.lr
   Compiling...
   Output:
   -------
42
Struct Nested Pass
   -------
   [PASS]

>> TEST: ../lors/tests/test_system_echo.lr
   Compiling...
   Output:
   -------
System command works
   -------
   [PASS]

>> TEST: ../lors/tests/test_terminal_ls.lr
   Compiling...
   Output:
   -------
total 644
drwxrwxr-x  4 zx zx   4096 Sep  8 02:08 .
drwxrwxr-x 12 zx zx   4096 Sep  8 02:08 ..
-rw-rw-r--  1 zx zx   3291 May 27 07:42 FIX.md
-rw-rw-r--  1 zx zx   2249 May 27 07:42 Makefile
-rw-rw-r--  1 zx zx    151 May 27 07:42 build_log.txt
-rw-rw-r--  1 zx zx  85294 May 27 07:42 combined.lr
-rw-rw-r--  1 zx zx  94776 May 27 07:42 combined_debug.lr
-rwxrwxr-x  1 zx zx 372080 Sep  8 02:08 lors_compiler
-rw-rw-r--  1 zx zx   8892 May 27 07:42 lors_compiler.lr
drwxrwxr-x  3 zx zx   4096 May 27 07:42 sandbox
drwxrwxr-x  2 zx zx   4096 May 27 07:42 self_compiler
-rw-rw-r--  1 zx zx   1815 May 27 07:42 test_execution.log
-rw-rw-r--  1 zx zx   1893 May 27 07:42 test_full_results.log
-rw-rw-r--  1 zx zx    476 May 27 07:42 test_include.lr
-rw-rw-r--  1 zx zx    101 May 27 07:42 test_inquire_simple.lr
-rw-rw-r--  1 zx zx   2051 Sep  8 02:08 test_list.tmp
-rw-rw-r--  1 zx zx  12333 May 27 07:42 test_output.log
-rw-rw-r--  1 zx zx  10730 May 27 07:42 test_results.log
-rw-rw-r--  1 zx zx  10457 May 27 07:42 test_results2.log
   -------
   [PASS]

Checking directory: test_v2
>> TEST: ../test_v2/simple.lr
   Compiling...
   Output:
   -------
Hello from Test V2
   -------
   [PASS]

========================================
Summary:
  Passed: 64
  Failed: 0
========================================
[ 75%] Built target test_stage5
[ 81%] >>> [STAGE 6] Compiling v6-dv/compiler.lr using self_hosted_v5 (Stage 5)...
Compiling to LLVM IR: compiler.lr
DEBUG: generate_code called
[ 81%] Built target stage6_seed
[ 87%] >>> [STAGE 6 TEST] Running and verifying tests with v6-dv/compiler...
==========================================================
Running Tests using Compiler: /home/zx/projects/6ls/main/v6-dv/compiler
Directories: /home/zx/projects/6ls/main/v6-dv/examples /home/zx/projects/6ls/main/v6-dv/tests
==========================================================
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/examples/calculation.lr
[OUTPUT]
107
93
700
14
7
[PASS] /home/zx/projects/6ls/main/v6-dv/examples/calculation.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/examples/hello.lr
[OUTPUT]
Hello, Lors!
30
x is smaller
0
1
2
3
4
[PASS] /home/zx/projects/6ls/main/v6-dv/examples/hello.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/examples/logic.lr
[OUTPUT]
Condition is true
Looping...
Looping...
Looping...
Loop finished
[PASS] /home/zx/projects/6ls/main/v6-dv/examples/logic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/edge_cases.lr
[OUTPUT]
120
Factorial correct
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/edge_cases.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_adv_math_io.lr
[OUTPUT]
78.5397
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_adv_math_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_array_access.lr
[OUTPUT]
20
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_array_access.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_array_decl.lr
[OUTPUT]
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_array_decl.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_array_file_io.lr
[OUTPUT]
1, 2, 3
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_array_file_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_array_modify.lr
[OUTPUT]
99
2
198
6
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_array_modify.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_array_no_mod_yet.lr
[OUTPUT]
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_array_no_mod_yet.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_bool_logic_complex.lr
[OUTPUT]
Complex logic pass
Negation pass
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_bool_logic_complex.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_calculator.lr
[OUTPUT]
Enter operation (1=add, 2=sub, 3=mul, 4=div):
Enter first number:
Enter second number:
Result:
30
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_calculator.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_chain_add.lr
[OUTPUT]
6
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_chain_add.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_chemistry_molar.lr
[OUTPUT]
Mass of water:
36.03
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_chemistry_molar.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_cli_args_basic.lr
[OUTPUT]
3
/home/zx/projects/6ls/main/v6-dv/tests/test_cli_args_basic
arg1
arg2
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_cli_args_basic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_cli_args_usage.lr
[OUTPUT]
First arg:
myargument
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_cli_args_usage.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_empty_array.lr
[OUTPUT]
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_empty_array.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_even_odd.lr
[OUTPUT]
Even
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_even_odd.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_factorial.lr
[OUTPUT]
120
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_factorial.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_fibonacci.lr
[OUTPUT]
0
1
1
2
3
5
8
13
21
34
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_fibonacci.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_file_custom_ext.lr
[OUTPUT]
key=value
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_file_custom_ext.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_file_write_read.lr
[OUTPUT]
Hello File I/O
File read/write successful
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_file_write_read.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_float_ops.lr
[OUTPUT]
9.5
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_float_ops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_fs_delete_file.lr
[OUTPUT]
File deleted
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_fs_delete_file.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_fs_exists_check.lr
[OUTPUT]
File exists
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_fs_exists_check.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_fs_io_flow.lr
[OUTPUT]
Step 1 OK
Step 2 OK
Step 3 OK
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_fs_io_flow.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_hypotenuse.lr
[OUTPUT]
3.53553
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_hypotenuse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_inc_a.lr
[OUTPUT]
100
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_inc_a.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_is_alnum.lr
[OUTPUT]
A is alnum
2 is alnum
! is not alnum
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_is_alnum.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_logic_and.lr
[OUTPUT]
Correct
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_logic_and.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_logic_mixed.lr
[OUTPUT]
Correct
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_logic_mixed.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_logic_not.lr
[OUTPUT]
Correct
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_logic_not.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_logic_or.lr
[OUTPUT]
Correct
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_logic_or.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_loop_sum.lr
[OUTPUT]
10
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_loop_sum.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_math_abs.lr
[OUTPUT]
10.5
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_math_abs.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_math_pi.lr
[OUTPUT]
-1
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_math_pi.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_math_pow.lr
[OUTPUT]
8
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_math_pow.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_math_root.lr
[OUTPUT]
4
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_math_root.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_math_trig.lr
[OUTPUT]
0
1
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_math_trig.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_mixed_parsing.lr
[OUTPUT]
112.5
Mixed Parse Pass
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_mixed_parsing.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_nested_logic_advanced.lr
[OUTPUT]
Deep nesting pass
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_nested_logic_advanced.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_nested_loops.lr
[OUTPUT]
0
1
10
11
20
21
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_nested_loops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_nested_verify.lr
[OUTPUT]
Inside range
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_nested_verify.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_order_ops.lr
[OUTPUT]
Order of ops correct
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_order_ops.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_os_env_read.lr
[OUTPUT]
Read PATH env
Handled missing env
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_os_env_read.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_os_system_call.lr
[OUTPUT]
OS Call
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_os_system_call.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_physics_gravity.lr
[OUTPUT]
Distance fallen:
30.6562
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_physics_gravity.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_prime_stub.lr
[OUTPUT]
true
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_prime_stub.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_str_case.lr
[OUTPUT]
HELLO 123
hello 123
Case Pass
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_str_case.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_str_float_parse.lr
[OUTPUT]
3.14159
6.28318
Parse Float Pass
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_str_float_parse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_string_input.lr
[OUTPUT]
Enter a word:
You typed:
HelloInput
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_string_input.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_str_lib_combo.lr
[OUTPUT]
Palindrome Detected
Conversion Pass
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_str_lib_combo.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_str_reverse.lr
[OUTPUT]
dlroW olleH
Reverse Pass
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_str_reverse.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_str_search.lr
[OUTPUT]
Hello
Substring Pass
CharAt Pass
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_str_search.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_str_types.lr
[OUTPUT]
Type Check Pass
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_str_types.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_struct_access.lr
[OUTPUT]
100
50
Struct Modify Pass
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_struct_access.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_struct_array.lr
[OUTPUT]
1
2
Struct Array Pass
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_struct_array.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_struct_basic.lr
[OUTPUT]
10
20
Struct Basic Pass
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_struct_basic.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_struct_func.lr
[OUTPUT]
4
6
Struct Func Pass
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_struct_func.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_struct_io.lr
[OUTPUT]
localhost:8080
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_struct_io.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_struct_nested.lr
[OUTPUT]
42
Struct Nested Pass
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_struct_nested.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_system_echo.lr
[OUTPUT]
System command works
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_system_echo.lr
----------------------------------------------------------
[FILE] /home/zx/projects/6ls/main/v6-dv/tests/test_terminal_ls.lr
[OUTPUT]
total 256
drwxrwxr-x  9 zx zx   4096 Sep  8 02:08 .
drwxrwxr-x 12 zx zx   4096 Sep  8 02:08 ..
-rw-r--r--  1 zx zx    111 Sep  5 09:14 .gitignore
-rw-r--r--  1 zx zx   7448 Aug 27 22:44 Makefile
-rw-r--r--  1 zx zx   5366 Aug 27 22:42 Makefile_dev
-rwxr-xr-x  1 zx zx   1398 Aug 27 21:59 build_all_modules.sh
drwxrwxr-x  2 zx zx   4096 Sep  8 02:04 build_modular_objs
-rwxrwxr-x  1 zx zx 180928 Sep  8 02:08 compiler
-rw-r--r--  1 zx zx   3121 Aug 27 21:29 compiler.lr
-rw-r--r--  1 zx zx   3121 Aug 27 21:30 compiler_dev.lr
drwxrwxr-x  2 zx zx   4096 Sep  8 02:08 examples
-rwxr-xr-x  1 zx zx   4696 Aug 27 22:20 link_all_modules.sh
drwxr-xr-x  5 zx zx   4096 Sep  8 02:04 modular_test
drwxrwxr-x 11 zx zx   4096 Aug 27 21:28 src
drwxr-xr-x  2 zx zx   4096 Sep  8 02:04 test_full_flags
drwxrwxr-x  2 zx zx   4096 Sep  8 02:04 test_suite_v6dv
drwxrwxr-x  2 zx zx   4096 Sep  8 02:08 tests
[PASS] /home/zx/projects/6ls/main/v6-dv/tests/test_terminal_ls.lr
==========================================================
Test Execution Summary: Passed: 63, Failed: 0
==========================================================
[ 87%] Built target test_stage6
[ 93%] >>> [STAGE 7] Building 68 modular objects and linking compiler_dev (Stage 7)...
==========================================================
Iniciando compilación modular individual de Stage 6 (.o)
==========================================================
----------------------------------------------------------
[MODULO] src/ast/ast_helpers.inc
-> OK
----------------------------------------------------------
[MODULO] src/ast/ast_node.inc
-> OK
----------------------------------------------------------
[MODULO] src/ast/ast_storage.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_decl_func.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_decl_struct.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_emitter.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_entrypoint.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_env.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_expr_array.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_expr_binary.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_expr_builtin.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_expr_calls.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_expr_construct.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_expr_dispatch.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_expr_primary.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_expr_struct.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_module.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_runtime_decls.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_runtime_fs.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_runtime_helpers.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_runtime_seq.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_stmt_assign.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_stmt_decl.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_stmt_dispatch.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_stmt_flow.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_stmt_io.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_strings.inc
-> OK
----------------------------------------------------------
[MODULO] src/codegen/llvm_types.inc
-> OK
----------------------------------------------------------
[MODULO] src/common/constants.inc
-> OK
----------------------------------------------------------
[MODULO] src/common/declarations.inc
-> OK
----------------------------------------------------------
[MODULO] src/common/error_handler.inc
-> OK
----------------------------------------------------------
[MODULO] src/common/list_utils.inc
-> OK
----------------------------------------------------------
[MODULO] src/common/path_utils.inc
-> OK
----------------------------------------------------------
[MODULO] src/common/str_utils.inc
-> OK
----------------------------------------------------------
[MODULO] src/driver/batch_compiler.inc
-> OK
----------------------------------------------------------
[MODULO] src/driver/cli_options.inc
-> OK
----------------------------------------------------------
[MODULO] src/driver/compile_pipeline.inc
-> OK
----------------------------------------------------------
[MODULO] src/driver/main_driver.inc
-> OK
----------------------------------------------------------
[MODULO] src/lexer/lexer_core.inc
-> OK
----------------------------------------------------------
[MODULO] src/lexer/lexer_keywords.inc
-> OK
----------------------------------------------------------
[MODULO] src/lexer/lexer_literals.inc
-> OK
----------------------------------------------------------
[MODULO] src/lexer/lexer_state.inc
-> OK
----------------------------------------------------------
[MODULO] src/lexer/token_struct.inc
-> OK
----------------------------------------------------------
[MODULO] src/memory/arena_allocator.inc
-> OK
----------------------------------------------------------
[MODULO] src/memory/buffer_contiguous.inc
-> OK
----------------------------------------------------------
[MODULO] src/memory/paged_storage.inc
-> OK
----------------------------------------------------------
[MODULO] src/memory/string_interner.inc
-> OK
----------------------------------------------------------
[MODULO] src/parser/parse_algorithm.inc
-> OK
----------------------------------------------------------
[MODULO] src/parser/parse_expr_binary.inc
-> OK
----------------------------------------------------------
[MODULO] src/parser/parse_expr_unary.inc
-> OK
----------------------------------------------------------
[MODULO] src/parser/parse_postfix.inc
-> OK
----------------------------------------------------------
[MODULO] src/parser/parse_primary.inc
-> OK
----------------------------------------------------------
[MODULO] src/parser/parse_program.inc
-> OK
----------------------------------------------------------
[MODULO] src/parser/parser_state.inc
-> OK
----------------------------------------------------------
[MODULO] src/parser/parse_stmt_assign.inc
-> OK
----------------------------------------------------------
[MODULO] src/parser/parse_stmt_decl.inc
-> OK
----------------------------------------------------------
[MODULO] src/parser/parse_stmt_flow.inc
-> OK
----------------------------------------------------------
[MODULO] src/parser/parse_stmt_io.inc
-> OK
----------------------------------------------------------
[MODULO] src/parser/parse_struct.inc
-> OK
----------------------------------------------------------
[MODULO] src/parser/parse_type.inc
-> OK
----------------------------------------------------------
[MODULO] src/preprocessor/file_reader.inc
-> OK
----------------------------------------------------------
[MODULO] src/preprocessor/include_resolver.inc
-> OK
----------------------------------------------------------
[MODULO] src/semantic/semantic_analyzer.inc
-> OK
----------------------------------------------------------
[MODULO] src/semantic/struct_registry.inc
-> OK
----------------------------------------------------------
[MODULO] src/semantic/symbol_struct.inc
-> OK
----------------------------------------------------------
[MODULO] src/semantic/symbol_table.inc
-> OK
----------------------------------------------------------
[MODULO] src/semantic/type_checker_calls.inc
-> OK
----------------------------------------------------------
[MODULO] src/semantic/type_checker_expr.inc
-> OK
----------------------------------------------------------
[MODULO] src/semantic/type_checker_stmt.inc
-> OK
----------------------------------------------------------
Resumen de compilación: Exitosos: 69, Fallidos: 0
==========================================================
==========================================================
Iniciando enlazado modular topológico de Stage 6
==========================================================
Total de módulos ordenados por capas: 68
Enlazando con clang usando resolución de grupo cíclico...
==========================================================
ÉXITO: Binario modular generado exitosamente: compiler_dev
-rwxrwxr-x 1 zx zx 454K Sep  8 02:09 compiler_dev
==========================================================
[ 93%] Built target stage7_modular
[100%] >>> [STAGE 7 TEST] Running complete 100% test suite with compiler_dev...
==========================================
Running All Tests with compiler_dev
==========================================
------------------------------------------------------------
[FILE] examples/calculation.lr
[OUTPUT]
107
93
700
14
7
------------------------------------------------------------
[FILE] examples/hello.lr
[OUTPUT]
Hello, Lors!
30
x is smaller
0
1
2
3
4
------------------------------------------------------------
[FILE] examples/logic.lr
[OUTPUT]
Condition is true
Looping...
Looping...
Looping...
Loop finished
------------------------------------------------------------
[FILE] tests/edge_cases.lr
[OUTPUT]
120
Factorial correct
------------------------------------------------------------
[FILE] tests/test_adv_math_io.lr
[OUTPUT]
78.5397
------------------------------------------------------------
[FILE] tests/test_array_access.lr
[OUTPUT]
20
------------------------------------------------------------
[FILE] tests/test_array_decl.lr
[OUTPUT]
------------------------------------------------------------
[FILE] tests/test_array_file_io.lr
[OUTPUT]
1, 2, 3
------------------------------------------------------------
[FILE] tests/test_array_modify.lr
[OUTPUT]
99
2
198
6
------------------------------------------------------------
[FILE] tests/test_array_no_mod_yet.lr
[OUTPUT]
------------------------------------------------------------
[FILE] tests/test_bool_logic_complex.lr
[OUTPUT]
Complex logic pass
Negation pass
------------------------------------------------------------
[FILE] tests/test_calculator.lr
[OUTPUT]
Enter operation (1=add, 2=sub, 3=mul, 4=div):
Enter first number:
Enter second number:
Result:
30
------------------------------------------------------------
[FILE] tests/test_chain_add.lr
[OUTPUT]
6
------------------------------------------------------------
[FILE] tests/test_chemistry_molar.lr
[OUTPUT]
Mass of water:
36.03
------------------------------------------------------------
[FILE] tests/test_cli_args_basic.lr
[OUTPUT]
3
./tests/test_cli_args_basic
arg1
arg2
------------------------------------------------------------
[FILE] tests/test_cli_args_usage.lr
[OUTPUT]
First arg:
myargument
------------------------------------------------------------
[FILE] tests/test_empty_array.lr
[OUTPUT]
------------------------------------------------------------
[FILE] tests/test_even_odd.lr
[OUTPUT]
Even
------------------------------------------------------------
[FILE] tests/test_factorial.lr
[OUTPUT]
120
------------------------------------------------------------
[FILE] tests/test_fibonacci.lr
[OUTPUT]
0
1
1
2
3
5
8
13
21
34
------------------------------------------------------------
[FILE] tests/test_file_custom_ext.lr
[OUTPUT]
key=value
------------------------------------------------------------
[FILE] tests/test_file_write_read.lr
[OUTPUT]
Hello File I/O
File read/write successful
------------------------------------------------------------
[FILE] tests/test_float_ops.lr
[OUTPUT]
9.5
------------------------------------------------------------
[FILE] tests/test_fs_delete_file.lr
[OUTPUT]
File deleted
------------------------------------------------------------
[FILE] tests/test_fs_exists_check.lr
[OUTPUT]
File exists
------------------------------------------------------------
[FILE] tests/test_fs_io_flow.lr
[OUTPUT]
Step 1 OK
Step 2 OK
Step 3 OK
------------------------------------------------------------
[FILE] tests/test_hypotenuse.lr
[OUTPUT]
3.53553
------------------------------------------------------------
[FILE] tests/test_inc_a.lr
[OUTPUT]
100
------------------------------------------------------------
[FILE] tests/test_is_alnum.lr
[OUTPUT]
A is alnum
2 is alnum
! is not alnum
------------------------------------------------------------
[FILE] tests/test_logic_and.lr
[OUTPUT]
Correct
------------------------------------------------------------
[FILE] tests/test_logic_mixed.lr
[OUTPUT]
Correct
------------------------------------------------------------
[FILE] tests/test_logic_not.lr
[OUTPUT]
Correct
------------------------------------------------------------
[FILE] tests/test_logic_or.lr
[OUTPUT]
Correct
------------------------------------------------------------
[FILE] tests/test_loop_sum.lr
[OUTPUT]
10
------------------------------------------------------------
[FILE] tests/test_math_abs.lr
[OUTPUT]
10.5
------------------------------------------------------------
[FILE] tests/test_math_pi.lr
[OUTPUT]
-1
------------------------------------------------------------
[FILE] tests/test_math_pow.lr
[OUTPUT]
8
------------------------------------------------------------
[FILE] tests/test_math_root.lr
[OUTPUT]
4
------------------------------------------------------------
[FILE] tests/test_math_trig.lr
[OUTPUT]
0
1
------------------------------------------------------------
[FILE] tests/test_mixed_parsing.lr
[OUTPUT]
112.5
Mixed Parse Pass
------------------------------------------------------------
[FILE] tests/test_nested_logic_advanced.lr
[OUTPUT]
Deep nesting pass
------------------------------------------------------------
[FILE] tests/test_nested_loops.lr
[OUTPUT]
0
1
10
11
20
21
------------------------------------------------------------
[FILE] tests/test_nested_verify.lr
[OUTPUT]
Inside range
------------------------------------------------------------
[FILE] tests/test_order_ops.lr
[OUTPUT]
Order of ops correct
------------------------------------------------------------
[FILE] tests/test_os_env_read.lr
[OUTPUT]
Read PATH env
Handled missing env
------------------------------------------------------------
[FILE] tests/test_os_system_call.lr
[OUTPUT]
OS Call
------------------------------------------------------------
[FILE] tests/test_physics_gravity.lr
[OUTPUT]
Distance fallen:
30.6562
------------------------------------------------------------
[FILE] tests/test_prime_stub.lr
[OUTPUT]
true
------------------------------------------------------------
[FILE] tests/test_str_case.lr
[OUTPUT]
HELLO 123
hello 123
Case Pass
------------------------------------------------------------
[FILE] tests/test_str_float_parse.lr
[OUTPUT]
3.14159
6.28318
Parse Float Pass
------------------------------------------------------------
[FILE] tests/test_str_lib_combo.lr
[OUTPUT]
Palindrome Detected
Conversion Pass
------------------------------------------------------------
[FILE] tests/test_str_reverse.lr
[OUTPUT]
dlroW olleH
Reverse Pass
------------------------------------------------------------
[FILE] tests/test_str_search.lr
[OUTPUT]
Hello
Substring Pass
CharAt Pass
------------------------------------------------------------
[FILE] tests/test_str_types.lr
[OUTPUT]
Type Check Pass
------------------------------------------------------------
[FILE] tests/test_string_input.lr
[OUTPUT]
Enter a word:
You typed:
HelloInput
------------------------------------------------------------
[FILE] tests/test_struct_access.lr
[OUTPUT]
100
50
Struct Modify Pass
------------------------------------------------------------
[FILE] tests/test_struct_array.lr
[OUTPUT]
1
2
Struct Array Pass
------------------------------------------------------------
[FILE] tests/test_struct_basic.lr
[OUTPUT]
10
20
Struct Basic Pass
------------------------------------------------------------
[FILE] tests/test_struct_func.lr
[OUTPUT]
4
6
Struct Func Pass
------------------------------------------------------------
[FILE] tests/test_struct_io.lr
[OUTPUT]
localhost:8080
------------------------------------------------------------
[FILE] tests/test_struct_nested.lr
[OUTPUT]
42
Struct Nested Pass
------------------------------------------------------------
[FILE] tests/test_system_echo.lr
[OUTPUT]
System command works
------------------------------------------------------------
[FILE] tests/test_terminal_ls.lr
[OUTPUT]
total 712
drwxrwxr-x  9 zx zx   4096 Sep  8 02:09 .
drwxrwxr-x 12 zx zx   4096 Sep  8 02:08 ..
-rw-r--r--  1 zx zx    111 Sep  5 09:14 .gitignore
-rw-r--r--  1 zx zx   7448 Aug 27 22:44 Makefile
-rw-r--r--  1 zx zx   5366 Aug 27 22:42 Makefile_dev
-rwxr-xr-x  1 zx zx   1398 Aug 27 21:59 build_all_modules.sh
drwxrwxr-x  2 zx zx   4096 Sep  8 02:09 build_modular_objs
-rwxrwxr-x  1 zx zx 180928 Sep  8 02:08 compiler
-rw-r--r--  1 zx zx   3121 Aug 27 21:29 compiler.lr
-rwxrwxr-x  1 zx zx 464392 Sep  8 02:09 compiler_dev
-rw-r--r--  1 zx zx   3121 Aug 27 21:30 compiler_dev.lr
drwxrwxr-x  2 zx zx   4096 Sep  8 02:09 examples
-rwxr-xr-x  1 zx zx   4696 Aug 27 22:20 link_all_modules.sh
drwxr-xr-x  5 zx zx   4096 Sep  8 02:04 modular_test
drwxrwxr-x 11 zx zx   4096 Aug 27 21:28 src
drwxr-xr-x  2 zx zx   4096 Sep  8 02:04 test_full_flags
drwxrwxr-x  2 zx zx   4096 Sep  8 02:04 test_suite_v6dv
drwxrwxr-x  2 zx zx   4096 Sep  8 02:09 tests
------------------------------------------------------------
==========================================
compiler_dev Test Complete: Total: 63, Passed: 63, Failed: 0
==========================================
==========================================
Running Flag Suite with compiler_dev...
==========================================
Flags Simple Success
Batch Multi-Module Result:
40
Flags tests passed successfully!
==========================================
Running Modular Test with compiler_dev...
==========================================
==========================================
Modular Math Library Demonstration
==========================================
--- 2D Vector Operations ---
v1 + v2 x:
4
v1 + v2 y:
6
Magnitude of v1 (expected 5.0):
5
Distance between v1 and v2:
2.82843
Dot product v1 . v2 (expected 11.0):
11
--- 3D Vector Operations ---
Cross product a x b (expected 0, 0, 1):
0
0
1
Magnitude of cross product (expected 1.0):
1
--- Statistical Computations ---
Dataset count (expected 5):
5
Dataset Min (expected 10.0):
10
Dataset Max (expected 50.0):
50
Dataset Mean (expected 30.0):
30
Dataset Variance (expected 200.0):
200
Dataset Standard Deviation:
14.1421
==========================================
Modular Math Demo Finished Successfully!
==========================================
Modular test passed successfully!
==========================================
Running test_suite_v6dv with compiler_dev
==========================================
------------------------------------------------------------
[FILE] test_suite_v6dv/edge_cases.lr
[OUTPUT]
120
Factorial correct
------------------------------------------------------------
[FILE] test_suite_v6dv/test_adv_math_io.lr
[OUTPUT]
78.5397
------------------------------------------------------------
[FILE] test_suite_v6dv/test_array_access.lr
[OUTPUT]
20
------------------------------------------------------------
[FILE] test_suite_v6dv/test_array_decl.lr
[OUTPUT]
5
150
------------------------------------------------------------
[FILE] test_suite_v6dv/test_array_file_io.lr
[OUTPUT]
1, 2, 3
------------------------------------------------------------
[FILE] test_suite_v6dv/test_array_modify.lr
[OUTPUT]
99
2
198
6
------------------------------------------------------------
[FILE] test_suite_v6dv/test_array_no_mod_yet.lr
[OUTPUT]
2
-1
------------------------------------------------------------
[FILE] test_suite_v6dv/test_bool_logic_complex.lr
[OUTPUT]
Complex logic pass
Negation pass
------------------------------------------------------------
[FILE] test_suite_v6dv/test_calculator.lr
[OUTPUT]
Enter operation (1=add, 2=sub, 3=mul, 4=div):
Enter first number:
Enter second number:
Result:
30
------------------------------------------------------------
[FILE] test_suite_v6dv/test_chain_add.lr
[OUTPUT]
6
------------------------------------------------------------
[FILE] test_suite_v6dv/test_chemistry_molar.lr
[OUTPUT]
Mass of water:
36.03
------------------------------------------------------------
[FILE] test_suite_v6dv/test_cli_args_basic.lr
[OUTPUT]
3
./test_suite_v6dv/test_cli_args_basic
arg1
arg2
------------------------------------------------------------
[FILE] test_suite_v6dv/test_cli_args_usage.lr
[OUTPUT]
First arg:
myargument
------------------------------------------------------------
[FILE] test_suite_v6dv/test_empty_array.lr
[OUTPUT]
0
Empty sequence verified successfully
------------------------------------------------------------
[FILE] test_suite_v6dv/test_even_odd.lr
[OUTPUT]
Even
------------------------------------------------------------
[FILE] test_suite_v6dv/test_factorial.lr
[OUTPUT]
120
------------------------------------------------------------
[FILE] test_suite_v6dv/test_fibonacci.lr
[OUTPUT]
0
1
1
2
3
5
8
13
21
34
------------------------------------------------------------
[FILE] test_suite_v6dv/test_file_custom_ext.lr
[OUTPUT]
key=value
------------------------------------------------------------
[FILE] test_suite_v6dv/test_file_write_read.lr
[OUTPUT]
Hello File I/O
File read/write successful
------------------------------------------------------------
[FILE] test_suite_v6dv/test_float_ops.lr
[OUTPUT]
9.5
------------------------------------------------------------
[FILE] test_suite_v6dv/test_fs_delete_file.lr
[OUTPUT]
File deleted
------------------------------------------------------------
[FILE] test_suite_v6dv/test_fs_exists_check.lr
[OUTPUT]
File exists
------------------------------------------------------------
[FILE] test_suite_v6dv/test_fs_io_flow.lr
[OUTPUT]
Step 1 OK
Step 2 OK
Step 3 OK
------------------------------------------------------------
[FILE] test_suite_v6dv/test_hypotenuse.lr
[OUTPUT]
3.53553
------------------------------------------------------------
[FILE] test_suite_v6dv/test_inc_a.lr
[OUTPUT]
100
------------------------------------------------------------
[FILE] test_suite_v6dv/test_is_alnum.lr
[OUTPUT]
A is alnum
2 is alnum
! is not alnum
------------------------------------------------------------
[FILE] test_suite_v6dv/test_logic_and.lr
[OUTPUT]
Correct
------------------------------------------------------------
[FILE] test_suite_v6dv/test_logic_mixed.lr
[OUTPUT]
Correct
------------------------------------------------------------
[FILE] test_suite_v6dv/test_logic_not.lr
[OUTPUT]
Correct
------------------------------------------------------------
[FILE] test_suite_v6dv/test_logic_or.lr
[OUTPUT]
Correct
------------------------------------------------------------
[FILE] test_suite_v6dv/test_loop_sum.lr
[OUTPUT]
10
------------------------------------------------------------
[FILE] test_suite_v6dv/test_math_abs.lr
[OUTPUT]
10.5
------------------------------------------------------------
[FILE] test_suite_v6dv/test_math_pi.lr
[OUTPUT]
-1
------------------------------------------------------------
[FILE] test_suite_v6dv/test_math_pow.lr
[OUTPUT]
8
------------------------------------------------------------
[FILE] test_suite_v6dv/test_math_root.lr
[OUTPUT]
4
------------------------------------------------------------
[FILE] test_suite_v6dv/test_math_trig.lr
[OUTPUT]
0
1
------------------------------------------------------------
[FILE] test_suite_v6dv/test_mixed_parsing.lr
[OUTPUT]
112.5
Mixed Parse Pass
------------------------------------------------------------
[FILE] test_suite_v6dv/test_nested_logic_advanced.lr
[OUTPUT]
Deep nesting pass
------------------------------------------------------------
[FILE] test_suite_v6dv/test_nested_loops.lr
[OUTPUT]
0
1
10
11
20
21
------------------------------------------------------------
[FILE] test_suite_v6dv/test_nested_verify.lr
[OUTPUT]
Inside range
------------------------------------------------------------
[FILE] test_suite_v6dv/test_order_ops.lr
[OUTPUT]
Order of ops correct
------------------------------------------------------------
[FILE] test_suite_v6dv/test_os_env_read.lr
[OUTPUT]
Read PATH env
Handled missing env
------------------------------------------------------------
[FILE] test_suite_v6dv/test_os_system_call.lr
[OUTPUT]
OS Call
------------------------------------------------------------
[FILE] test_suite_v6dv/test_physics_gravity.lr
[OUTPUT]
Distance fallen:
30.6562
------------------------------------------------------------
[FILE] test_suite_v6dv/test_prime_stub.lr
[OUTPUT]
true
false
true
------------------------------------------------------------
[FILE] test_suite_v6dv/test_str_case.lr
[OUTPUT]
HELLO 123
hello 123
Case Pass
------------------------------------------------------------
[FILE] test_suite_v6dv/test_str_float_parse.lr
[OUTPUT]
3.14159
6.28318
Parse Float Pass
------------------------------------------------------------
[FILE] test_suite_v6dv/test_str_lib_combo.lr
[OUTPUT]
Palindrome Detected
Conversion Pass
------------------------------------------------------------
[FILE] test_suite_v6dv/test_str_reverse.lr
[OUTPUT]
dlroW olleH
Reverse Pass
------------------------------------------------------------
[FILE] test_suite_v6dv/test_str_search.lr
[OUTPUT]
Hello
Substring Pass
CharAt Pass
------------------------------------------------------------
[FILE] test_suite_v6dv/test_str_types.lr
[OUTPUT]
Type Check Pass
------------------------------------------------------------
[FILE] test_suite_v6dv/test_string_input.lr
[OUTPUT]
Enter a word:
You typed:
HelloInput
------------------------------------------------------------
[FILE] test_suite_v6dv/test_struct_access.lr
[OUTPUT]
100
50
Struct Modify Pass
------------------------------------------------------------
[FILE] test_suite_v6dv/test_struct_array.lr
[OUTPUT]
1
2
Struct Array Pass
------------------------------------------------------------
[FILE] test_suite_v6dv/test_struct_basic.lr
[OUTPUT]
10
20
Struct Basic Pass
------------------------------------------------------------
[FILE] test_suite_v6dv/test_struct_func.lr
[OUTPUT]
4
6
Struct Func Pass
------------------------------------------------------------
[FILE] test_suite_v6dv/test_struct_io.lr
[OUTPUT]
localhost:8080
------------------------------------------------------------
[FILE] test_suite_v6dv/test_struct_nested.lr
[OUTPUT]
42
Struct Nested Pass
------------------------------------------------------------
[FILE] test_suite_v6dv/test_system_echo.lr
[OUTPUT]
System command works
------------------------------------------------------------
[FILE] test_suite_v6dv/test_terminal_ls.lr
[OUTPUT]
total 712
drwxrwxr-x  9 zx zx   4096 Sep  8 02:09 .
drwxrwxr-x 12 zx zx   4096 Sep  8 02:08 ..
-rw-r--r--  1 zx zx    111 Sep  5 09:14 .gitignore
-rw-r--r--  1 zx zx   7448 Aug 27 22:44 Makefile
-rw-r--r--  1 zx zx   5366 Aug 27 22:42 Makefile_dev
-rwxr-xr-x  1 zx zx   1398 Aug 27 21:59 build_all_modules.sh
drwxrwxr-x  2 zx zx   4096 Sep  8 02:09 build_modular_objs
-rwxrwxr-x  1 zx zx 180928 Sep  8 02:08 compiler
-rw-r--r--  1 zx zx   3121 Aug 27 21:29 compiler.lr
-rwxrwxr-x  1 zx zx 464392 Sep  8 02:09 compiler_dev
-rw-r--r--  1 zx zx   3121 Aug 27 21:30 compiler_dev.lr
drwxrwxr-x  2 zx zx   4096 Sep  8 02:09 examples
-rwxr-xr-x  1 zx zx   4696 Aug 27 22:20 link_all_modules.sh
drwxr-xr-x  5 zx zx   4096 Sep  8 02:09 modular_test
drwxrwxr-x 11 zx zx   4096 Aug 27 21:28 src
drwxr-xr-x  2 zx zx   4096 Sep  8 02:09 test_full_flags
drwxrwxr-x  2 zx zx   4096 Sep  8 02:09 test_suite_v6dv
drwxrwxr-x  2 zx zx   4096 Sep  8 02:09 tests
------------------------------------------------------------
==========================================
test_suite_v6dv Complete: Total: 60, Passed: 60, Failed: 0
==========================================
[100%] Built target test_stage7
[100%] Built target all_stages
zx@zx:~/projects/6ls/build$ 

