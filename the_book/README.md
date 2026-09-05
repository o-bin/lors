# The Lors Compiler Architecture and Self-Hosting Book (Stage 6)

## Overview

This repository book constitutes the definitive technical specification, architectural record, and maintainer's encyclopedia for the **Lors Stage 6 (`v6-dv`) LLVM Modular Self-Hosted Compiler**.

---

## Complete Volume Index

| Volume | File | Subject Matter |
| :--- | :--- | :--- |
| **Volume I** | [01_volume_1_language_and_philosophy.md](01_volume_1_language_and_philosophy.md) | The Lors Language Specification, Deterministic Design, and the Stage 5 vs Stage 6 Evolution |
| **Volume II** | [02_volume_2_memory_and_datastructures.md](02_volume_2_memory_and_datastructures.md) | Structure-of-Arrays (SoA) Storage, Paged Tables, List Serialization, and FNV-1a Interning |
| **Volume III** | [03_volume_3_frontend_and_ast.md](03_volume_3_frontend_and_ast.md) | Preprocessor Graph Cycle Prevention, Token Scanning State Machine, AST Nodes, and Recursive Descent Parser |
| **Volume IV** | [04_volume_4_semantic_and_types.md](04_volume_4_semantic_and_types.md) | 3-Pass Semantic Analyzer, Scoped Symbol Tables, Struct Registries, and the Function Call Type Inference Hierarchy |
| **Volume V** | [05_volume_5_llvm_backend_and_abi.md](05_volume_5_llvm_backend_and_abi.md) | LLVM IR Code Generation, Type Mappings, Control Flow SSA Translation, System V x86_64 ABI, and Linkage Types |
| **Volume VI** | [06_volume_6_multiobject_linking.md](06_volume_6_multiobject_linking.md) | Standalone `.inc` to `.o` Compilation, Header Injection via `declarations.inc`, and Topological Group Linking |
| **Volume VII** | [07_volume_7_infinite_bootstrap.md](07_volume_7_infinite_bootstrap.md) | The Bootstrap Paradox, The Point of Inflection, and 100% Test Suite Verification (124+ tests) |
| **Volume VIII** | [08_volume_8_maintainer_encyclopedia.md](08_volume_8_maintainer_encyclopedia.md) | The Maintainer's Encyclopedia, AI Agent Playbook, Invariants, Case Studies in Debugging, and Extension Recipes |
| **Volume IX** | [09_volume_9_module_catalog.md](09_volume_9_module_catalog.md) | Complete Catalog and Directory Breakdown of All 68 Compiler Modules across 9 Layers |

---

## Single-Document Master Edition

The entire uncompressed, unabridged treatise combining all 9 Volumes in a single continuous document is available at:
* **[THE_LORS_COMPILER_COMPLETE_TREATISE.md](THE_LORS_COMPILER_COMPLETE_TREATISE.md)**
