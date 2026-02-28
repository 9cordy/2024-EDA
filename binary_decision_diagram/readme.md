# Binary Decision Diagram

## Introduction
This project implements a **Reduced Ordered Binary Decision Diagram (ROBDD)** generator. It converts Boolean functions into a canonical directed acyclic graph (DAG) representation, optimized to achieve the minimum number of nodes without relying on external libraries like CUDD.

## Algorithm Flow
* **Initial Parsing**: Reads Boolean expressions from the input file and constructs an initial decision tree.
* **Node Reduction**: Applies reduction rules to remove any node with identical children and merge isomorphic BDDs.
* **Canonical Ordering**: Ensures a fixed variable ordering to maintain the "Ordered" property, which is essential for the uniqueness of the BDD.
* **Node Minimization**: Automatically calculates the minimum number of nodes required for the final ROBDD structure.

## Compilation and Execution
```bash
# To compile
make

# To execute
./ROBDD [input_file] [output_file]

# To remove object files
make clean