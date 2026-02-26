# FM Partitioning - Circuit Partitioning Tool

## Introduction
This project implements the **Fiduccia-Mattheyses (FM) Algorithm** for 2-way hypergraph partitioning. The goal is to minimize the **cut-size** while maintaining strict area balance constraints.

## Versions
* **Version 1 (Procedural)**: A baseline implementation focusing on the core algorithm logic.
* **Version 2 (OOP Optimized)**: 
    * Encapsulates the FM logic into a dedicated `class FM`.
    * Improves code reusability and maintainability.
    * Efficiently manages internal data structures like the Gain Bucket and Cell information within the class scope.

## Technical Highlights
* **Gain Bucket Management**: High-speed updates of cell gains during movement.
* **Area Balancing**: Ensures the area ratio between the two partitions stays within the allowed tolerance.

## Compilation and Execution
```bash
# To compile (Makefile configured for class-based FM)
make

# To execute
./FM_partition <input_file> <output_file>