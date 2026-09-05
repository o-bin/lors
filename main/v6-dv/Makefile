# Makefile for Lors Stage 6 (v6-dv) Self-Hosted Compiler

V5_COMPILER = ../self_hosted_v5/lors_compiler
V6_COMPILER = ./compiler
V6_DEV_COMPILER = ./compiler_dev
SOURCES = compiler.lr $(wildcard src/*/*.inc)

.PHONY: all build build-dev test test-dev test-summary test-flags test-modular test-suite-v6dv test-all compile-self clean

all: build build-dev

build: $(V6_COMPILER)

$(V6_COMPILER): $(SOURCES)
	@echo "=========================================="
	@echo "Building Lors Stage 6 Monolithic Compiler (Stage 5 bootstrap)..."
	@echo "=========================================="
	$(V5_COMPILER) compiler.lr

build-dev: $(V6_DEV_COMPILER)

$(V6_DEV_COMPILER): $(SOURCES)
	@echo "=========================================="
	@echo "Building All Stage 6 Modular Objects (.o)..."
	@echo "=========================================="
	@./build_all_modules.sh
	@echo "=========================================="
	@echo "Linking All Stage 6 Objects into compiler_dev..."
	@echo "=========================================="
	@./link_all_modules.sh

test: build
	@echo "=========================================="
	@echo "Running and Displaying All Test Suite Outputs"
	@echo "=========================================="
	@failed=0; passed=0; \
	for src in examples/*.lr tests/*.lr; do \
		if [ -f "$$src" ]; then \
			exe=$${src%.lr}; \
			echo "------------------------------------------------------------"; \
			echo "[FILE] $$src"; \
			$(V6_COMPILER) $$src; \
			if [ $$? -ne 0 ] || [ ! -f "$$exe" ]; then \
				echo "[ERROR] Compilation failed for $$src"; \
				failed=$$((failed + 1)); \
				continue; \
			fi; \
			echo "[OUTPUT]"; \
			if echo "$$exe" | grep -q "test_calculator"; then \
				printf "1\n10\n20\n" | ./$$exe; \
			elif echo "$$exe" | grep -q "test_string_input"; then \
				printf "HelloInput\n" | ./$$exe; \
			elif echo "$$exe" | grep -q "test_cli_args_basic"; then \
				./$$exe arg1 arg2; \
			elif echo "$$exe" | grep -q "test_cli_args_usage"; then \
				./$$exe myargument; \
			else \
				./$$exe; \
			fi; \
			ret=$$?; \
			if [ $$ret -ne 0 ]; then \
				echo "[ERROR] Runtime exited with status code $$ret"; \
				failed=$$((failed + 1)); \
			else \
				passed=$$((passed + 1)); \
			fi; \
			rm -f $$exe $$exe.o $$exe.ll; \
		fi; \
	done; \
	echo "------------------------------------------------------------"; \
	echo "=========================================="; \
	echo "Execution Complete: Total: $$((passed + failed)), Passed: $$passed, Failed: $$failed"; \
	echo "=========================================="; \
	if [ $$failed -ne 0 ]; then exit 1; fi

test-dev: build-dev
	@echo "=========================================="
	@echo "Running Complete Test Suite with Modular compiler_dev..."
	@echo "=========================================="
	@failed=0; passed=0; \
	for src in examples/*.lr tests/*.lr test_suite_v6dv/*.lr; do \
		if [ -f "$$src" ]; then \
			exe=$${src%.lr}; \
			echo "------------------------------------------------------------"; \
			echo "[FILE] $$src"; \
			$(V6_DEV_COMPILER) $$src; \
			if [ $$? -ne 0 ] || [ ! -f "$$exe" ]; then \
				echo "[ERROR] Compilation failed for $$src"; \
				failed=$$((failed + 1)); \
				continue; \
			fi; \
			echo "[OUTPUT]"; \
			if echo "$$exe" | grep -q "test_calculator"; then \
				printf "1\n10\n20\n" | ./$$exe; \
			elif echo "$$exe" | grep -q "test_string_input"; then \
				printf "HelloInput\n" | ./$$exe; \
			elif echo "$$exe" | grep -q "test_cli_args_basic"; then \
				./$$exe arg1 arg2; \
			elif echo "$$exe" | grep -q "test_cli_args_usage"; then \
				./$$exe myargument; \
			else \
				./$$exe; \
			fi; \
			ret=$$?; \
			if [ $$ret -ne 0 ]; then \
				echo "[ERROR] Runtime exited with status code $$ret"; \
				failed=$$((failed + 1)); \
			else \
				passed=$$((passed + 1)); \
			fi; \
			rm -f $$exe $$exe.o $$exe.ll; \
		fi; \
	done; \
	echo "------------------------------------------------------------"; \
	echo "=========================================="; \
	echo "Modular compiler_dev Suite Complete: Total: $$((passed + failed)), Passed: $$passed, Failed: $$failed"; \
	echo "=========================================="; \
	if [ $$failed -ne 0 ]; then exit 1; fi

test-flags: build
	@chmod +x test_full_flags/run_all_flags_test.sh
	@./test_full_flags/run_all_flags_test.sh

test-modular: build build-dev
	@echo "=========================================="
	@echo "Running Modular Math Library Test with compiler_dev..."
	@echo "=========================================="
	$(V6_DEV_COMPILER) modular_test/app.lr
	@./modular_test/app
	@rm -f modular_test/app modular_test/app.o modular_test/app.ll
	@echo "Modular test passed successfully!"

test-suite-v6dv: build-dev
	@echo "=========================================="
	@echo "Running and Displaying All test_suite_v6dv Outputs with compiler_dev"
	@echo "=========================================="
	@failed=0; passed=0; \
	for src in test_suite_v6dv/*.lr; do \
		if [ -f "$$src" ]; then \
			exe=$${src%.lr}; \
			echo "------------------------------------------------------------"; \
			echo "[FILE] $$src"; \
			$(V6_DEV_COMPILER) $$src; \
			if [ $$? -ne 0 ] || [ ! -f "$$exe" ]; then \
				echo "[ERROR] Compilation failed for $$src"; \
				failed=$$((failed + 1)); \
				continue; \
				fi; \
			echo "[OUTPUT]"; \
			if echo "$$exe" | grep -q "test_calculator"; then \
				printf "1\n10\n20\n" | ./$$exe; \
			elif echo "$$exe" | grep -q "test_string_input"; then \
				printf "HelloInput\n" | ./$$exe; \
			elif echo "$$exe" | grep -q "test_cli_args_basic"; then \
				./$$exe arg1 arg2; \
			elif echo "$$exe" | grep -q "test_cli_args_usage"; then \
				./$$exe myargument; \
			else \
				./$$exe; \
			fi; \
			ret=$$?; \
			if [ $$ret -ne 0 ]; then \
				echo "[ERROR] Runtime exited with status code $$ret"; \
				failed=$$((failed + 1)); \
			else \
				passed=$$((passed + 1)); \
			fi; \
			rm -f $$exe $$exe.o $$exe.ll; \
		fi; \
	done; \
	echo "------------------------------------------------------------"; \
	echo "=========================================="; \
	echo "test_suite_v6dv Complete: Total: $$((passed + failed)), Passed: $$passed, Failed: $$failed"; \
	echo "=========================================="; \
	if [ $$failed -ne 0 ]; then exit 1; fi

compile-self: build
	@echo "=========================================="
	@echo "Executing Separate Compilation of Stage 6 Modules..."
	@echo "=========================================="
	@./build_all_modules.sh
	@echo "=========================================="
	@echo "Linking All Object Files into compiler_dev..."
	@echo "=========================================="
	@./link_all_modules.sh
	@echo "=========================================="
	@echo "Verifying compiler_dev Functionality..."
	@echo "=========================================="
	@./compiler_dev tests/test_factorial.lr
	@./tests/test_factorial
	@rm -f tests/test_factorial

test-all: test test-flags test-modular test-suite-v6dv test-dev

clean:
	rm -f $(V6_COMPILER) $(V6_DEV_COMPILER) compiler.o compiler.ll compiler_dev.o compiler_dev.ll *.o *.ll
	rm -f build_modular_objs/*.o build_modular_objs/*.ll
	rm -f examples/hello examples/calculation examples/logic
	rm -f tests/test_*
	rm -f test_full_flags/simple test_full_flags/*.o test_full_flags/*.ll test_full_flags/program test_full_flags/custom_app
	rm -f modular_test/app modular_test/*.o modular_test/*.ll
	rm -f test_suite_v6dv/test_* test_suite_v6dv/edge_cases
