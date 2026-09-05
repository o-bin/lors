#!/bin/bash
# Build script for the new self-hosted compiler

if [ -f "./twin" ]; then
    echo "Building self_compiler_s/compiler using twin..."
    ./twin self_compiler_s/lors_bootstrap.lr
    if [ -f "self_compiler_s/lors_bootstrap" ]; then
        mv self_compiler_s/lors_bootstrap self_compiler_s/compiler
        echo "Build successful: self_compiler_s/compiler created."
    else
        echo "Build failed: Output binary not found."
        exit 1
    fi
else
    echo "Error: 'twin' compiler not found in root directory."
    echo "Please run 'make bootstrap' first to build the bootstrap compiler."
    exit 1
fi
