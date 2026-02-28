# Partition

## Introduction
This project implements the **Fiduccia-Mattheyses (FM) Algorithm** for 2-way hypergraph partitioning. The goal is to minimize the **cut-size** while maintaining area balance constraints.

## Versions
* **Version 1 (Procedural)**: A baseline implementation focusing on the core algorithm logic.
* **Version 2 (OOP Optimized)**: 
    * Encapsulates the FM logic into a dedicated `class FM`.
    * Improves code reusability and maintainability.
    * Efficiently manages internal data structures like the Gain Bucket and Cell information within the class scope.

## Algorithm Flow
* **Initial Partitioning**: Divides nodes into two initial sets (Left and Right) based on a balance factor.
* **Gain Calculation**: Computes the initial gain for each cell, representing the reduction in cut-size if the cell is moved.
* **Iterative Movement**: 
    * Selects the unlocked cell with the maximum gain that satisfies the balance constraint.
    * Moves the cell to the opposite side and locks it to prevent thrashing.
* **Gain Update**: Efficiently updates the gains of all neighboring cells affected by the move.
* **Best State Recovery**: Identifies the step with the maximum partial sum of gains during an entire pass and reverts to that optimal state.

## Compilation and Execution
```bash
# To compile
make

# To execute
./FM_partition <input_file> <output_file>

# To remove object files
make clean