#!/bin/bash
# ==========================================================
# Script de Compilación Modular Separada para Lors Stage 6
# Muestra los errores exactos de cada módulo .inc
# ==========================================================

COMPILER="./compiler"
BUILD_DIR="build_modular_objs"
FAILED=0
PASSED=0

echo "=========================================================="
echo "Iniciando compilación modular individual de Stage 6 (.o)"
echo "=========================================================="

mkdir -p "$BUILD_DIR"
rm -f "$BUILD_DIR"/*.o "$BUILD_DIR"/*.ll

for inc_file in src/*/*.inc; do
    if [ -f "$inc_file" ]; then
        base_name=$(basename "$inc_file" .inc)
        echo "----------------------------------------------------------"
        echo "[MODULO] $inc_file"
        
        OUT=$($COMPILER "$inc_file" -o -debug 2>&1)
        ret=$?
        obj_file="${inc_file%.inc}.o"
        
        if [ -f "$obj_file" ]; then
            mv "$obj_file" "$BUILD_DIR/${base_name}.o"
            echo "-> OK"
            PASSED=$((PASSED + 1))
        else
            echo "-> FALLO"
            echo "$OUT"
            FAILED=$((FAILED + 1))
        fi
    fi
done

echo "----------------------------------------------------------"
echo "Resumen de compilación: Exitosos: $PASSED, Fallidos: $FAILED"
echo "=========================================================="
