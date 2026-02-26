# ROBDD - Node Minimization Tool

## Introduction
This tool converts Boolean functions into **ROBDD (Reduced Ordered Binary Decision Diagram)** format to determine the minimum number of nodes required for a specific input.

## Key Features
* **Independent Implementation**: This program is built from scratch and does **not** use the CUDD library.
* **Optimization**: Automatically calculates the Reduced Ordered form to ensure node minimization.

## Compilation and Execution
```bash
# To compile
make

# To execute
./ROBDD [input_file] [output_file]

# To remove object files
make clean