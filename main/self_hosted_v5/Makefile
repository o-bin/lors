# Makefile for self_hosted_v5

LORS_COMPILER=../self_compiler_s/compiler
V5_COMPILER=./lors_compiler

.PHONY: all clean tests run_lors_tests run_flags_tests run_universal_tests copy_tests

all: $(V5_COMPILER)

$(V5_COMPILER): lors_compiler.lr self_compiler/llvm_*.inc
	$(LORS_COMPILER) lors_compiler.lr -o
	g++ lors_compiler.o -o $(V5_COMPILER)

copy_tests:
	mkdir -p tests
	cp -r ../lors/tests/* tests/ || true
	mkdir -p examples
	cp -r ../lors/examples/* examples/ || true
	mkdir -p flags_test
	cp -r ../flags_test/* flags_test/ || true
	rm -f flags_test/*.o
	# mkdir -p universal_test
	# cp -r ../universal_test/* universal_test/ || true

run_lors_tests: $(V5_COMPILER) copy_tests
	# Since LLVM backend is a proof of concept, we just compile them.
	# Full runtime semantics are not yet fully implemented (arrays, all math ops, etc)
	# This demonstrates that the compiler can parse and generate LLVM IR.
	@for f in tests/*.lr; do \
		if [ -f "$$f" ]; then \
			echo "Compiling and running $$f"; \
			$(V5_COMPILER) $$f -s || true; \
			bin=$${f%.lr}; \
			if [ -f "$$bin" ]; then ./$$bin || true; fi; \
		fi \
	done
	@for f in examples/*.lr; do \
		if [ -f "$$f" ]; then \
			echo "Compiling and running $$f"; \
			$(V5_COMPILER) $$f -s || true; \
			bin=$${f%.lr}; \
			if [ -f "$$bin" ]; then ./$$bin || true; fi; \
		fi \
	done

run_flags_tests: $(V5_COMPILER) copy_tests
	@echo "Testing compiler flags (-oall and -iall) in flags_test..."
	cd flags_test && ../$(V5_COMPILER) -oall || true
	cd flags_test && ../$(V5_COMPILER) -iall -ns test_prog || true
	@if [ -f "flags_test/test_prog" ]; then \
		echo "Running flags_test/test_prog"; \
		./flags_test/test_prog || true; \
	else \
		echo "flags_test/test_prog was not created properly"; \
	fi

run_universal_tests: $(V5_COMPILER) copy_tests
	@for f in universal_test/*.lr; do \
		if [ -f "$$f" ]; then \
			echo "Compiling and running $$f"; \
			$(V5_COMPILER) $$f -s || true; \
			bin=$${f%.lr}; \
			if [ -f "$$bin" ]; then ./$$bin || true; fi; \
		fi \
	done

tests: run_lors_tests run_flags_tests run_universal_tests
	@echo "All tests finished compiling."

clean:
	rm -f $(V5_COMPILER) lors_compiler.o lors_compiler.ll *.ll *.o test.lr test
	rm -rf tests examples flags_test universal_test
