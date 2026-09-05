#!/bin/bash
# ==========================================================
# Script de Enlazado Modular Topológico para Lors Stage 6
# Enlaza los 68 objetos en orden estricto de capas
# ==========================================================

BUILD_DIR="build_modular_objs"
OUTPUT_BIN="compiler_dev"

echo "=========================================================="
echo "Iniciando enlazado modular topológico de Stage 6"
echo "=========================================================="

if [ ! -d "$BUILD_DIR" ]; then
    echo "Error: El directorio '$BUILD_DIR' no existe. Ejecuta primero ./build_all_modules.sh"
    exit 1
fi

# Capa 1: Driver y Entrada Principal (@main)
LAYER_DRIVER=(
    "$BUILD_DIR/main_driver.o"
    "$BUILD_DIR/cli_options.o"
    "$BUILD_DIR/compile_pipeline.o"
    "$BUILD_DIR/batch_compiler.o"
)

# Capa 2: Backend de Generación de Código LLVM
LAYER_CODEGEN=(
    "$BUILD_DIR/llvm_entrypoint.o"
    "$BUILD_DIR/llvm_module.o"
    "$BUILD_DIR/llvm_emitter.o"
    "$BUILD_DIR/llvm_env.o"
    "$BUILD_DIR/llvm_types.o"
    "$BUILD_DIR/llvm_strings.o"
    "$BUILD_DIR/llvm_decl_func.o"
    "$BUILD_DIR/llvm_decl_struct.o"
    "$BUILD_DIR/llvm_stmt_dispatch.o"
    "$BUILD_DIR/llvm_stmt_decl.o"
    "$BUILD_DIR/llvm_stmt_assign.o"
    "$BUILD_DIR/llvm_stmt_flow.o"
    "$BUILD_DIR/llvm_stmt_io.o"
    "$BUILD_DIR/llvm_expr_dispatch.o"
    "$BUILD_DIR/llvm_expr_primary.o"
    "$BUILD_DIR/llvm_expr_binary.o"
    "$BUILD_DIR/llvm_expr_calls.o"
    "$BUILD_DIR/llvm_expr_struct.o"
    "$BUILD_DIR/llvm_expr_construct.o"
    "$BUILD_DIR/llvm_expr_array.o"
    "$BUILD_DIR/llvm_expr_builtin.o"
    "$BUILD_DIR/llvm_runtime_decls.o"
    "$BUILD_DIR/llvm_runtime_helpers.o"
    "$BUILD_DIR/llvm_runtime_fs.o"
    "$BUILD_DIR/llvm_runtime_seq.o"
)

# Capa 3: Analizador Semántico y Tablas de Símbolos
LAYER_SEMANTIC=(
    "$BUILD_DIR/semantic_analyzer.o"
    "$BUILD_DIR/type_checker_stmt.o"
    "$BUILD_DIR/type_checker_expr.o"
    "$BUILD_DIR/type_checker_calls.o"
    "$BUILD_DIR/symbol_table.o"
    "$BUILD_DIR/symbol_struct.o"
    "$BUILD_DIR/struct_registry.o"
)

# Capa 4: Analizador Sintáctico (Parser)
LAYER_PARSER=(
    "$BUILD_DIR/parse_program.o"
    "$BUILD_DIR/parse_algorithm.o"
    "$BUILD_DIR/parse_stmt_decl.o"
    "$BUILD_DIR/parse_stmt_assign.o"
    "$BUILD_DIR/parse_stmt_flow.o"
    "$BUILD_DIR/parse_stmt_io.o"
    "$BUILD_DIR/parse_expr_binary.o"
    "$BUILD_DIR/parse_expr_unary.o"
    "$BUILD_DIR/parse_primary.o"
    "$BUILD_DIR/parse_postfix.o"
    "$BUILD_DIR/parse_type.o"
    "$BUILD_DIR/parse_struct.o"
    "$BUILD_DIR/parser_state.o"
)

# Capa 5: Analizador Léxico (Lexer)
LAYER_LEXER=(
    "$BUILD_DIR/lexer_core.o"
    "$BUILD_DIR/lexer_keywords.o"
    "$BUILD_DIR/lexer_literals.o"
    "$BUILD_DIR/lexer_state.o"
    "$BUILD_DIR/token_struct.o"
)

# Capa 6: Preprocesador
LAYER_PREPROCESSOR=(
    "$BUILD_DIR/include_resolver.o"
    "$BUILD_DIR/file_reader.o"
)

# Capa 7: Árbol de Sintaxis Abstracta (AST)
LAYER_AST=(
    "$BUILD_DIR/ast_node.o"
    "$BUILD_DIR/ast_storage.o"
    "$BUILD_DIR/ast_helpers.o"
)

# Capa 8: Gestión de Memoria y Paginación
LAYER_MEMORY=(
    "$BUILD_DIR/arena_allocator.o"
    "$BUILD_DIR/buffer_contiguous.o"
    "$BUILD_DIR/paged_storage.o"
    "$BUILD_DIR/string_interner.o"
)

# Capa 9: Utilidades Comunes y Constantes Base
LAYER_COMMON=(
    "$BUILD_DIR/constants.o"
    "$BUILD_DIR/str_utils.o"
    "$BUILD_DIR/list_utils.o"
    "$BUILD_DIR/path_utils.o"
    "$BUILD_DIR/error_handler.o"
)

ALL_OBJECTS=(
    "${LAYER_DRIVER[@]}"
    "${LAYER_CODEGEN[@]}"
    "${LAYER_SEMANTIC[@]}"
    "${LAYER_PARSER[@]}"
    "${LAYER_LEXER[@]}"
    "${LAYER_PREPROCESSOR[@]}"
    "${LAYER_AST[@]}"
    "${LAYER_MEMORY[@]}"
    "${LAYER_COMMON[@]}"
)

TOTAL_OBJS=${#ALL_OBJECTS[@]}
echo "Total de módulos ordenados por capas: $TOTAL_OBJS"

# Verificar que todos los objetos existen
for obj in "${ALL_OBJECTS[@]}"; do
    if [ ! -f "$obj" ]; then
        echo "Error: Falta el objeto '$obj'"
        exit 1
    fi
done

echo "Enlazando con clang usando resolución de grupo cíclico..."

clang -Wl,--start-group "${ALL_OBJECTS[@]}" -Wl,--end-group -lm -o "$OUTPUT_BIN"
LINK_STATUS=$?

if [ $LINK_STATUS -eq 0 ] && [ -f "$OUTPUT_BIN" ]; then
    echo "=========================================================="
    echo "ÉXITO: Binario modular generado exitosamente: $OUTPUT_BIN"
    ls -lh "$OUTPUT_BIN"
    echo "=========================================================="
else
    echo "=========================================================="
    echo "Error: El enlazado falló con código de salida: $LINK_STATUS"
    echo "=========================================================="
    exit 1
fi
