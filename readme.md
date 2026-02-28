# 2024 Electronic Design Automation (EDA)

This repository contains three algorithmic projects developed for the "Electronic Design Automation" course in 2024. The implementations focus on core methodologies in the EDA flow, including logic optimization, circuit partitioning, and physical routing.

---

## Tech Stack
* **Language**: C / C++
* **Algorithms**: Fiduccia-Mattheyses (FM) Algorithm, Lee Algorithm (BFS), Graph Reduction
* **Concepts**: Object-Oriented Programming (OOP), Directed Acyclic Graphs (DAG), Hypergraph Partitioning

---

## Projects Overview

### 1. [Binary Decision Diagram](./binary_decision_diagram)
* **Description**: A Reduced Ordered Binary Decision Diagram (ROBDD) generator that converts Boolean functions into a canonical Directed Acyclic Graph (DAG) representation.
* **Implementation Details**:
  * Implemented strictly from scratch without relying on external libraries such as CUDD.
  * Applies reduction rules to eliminate nodes with identical children and merge isomorphic subgraphs.
  * Calculates the minimum number of nodes required for the ROBDD structure under a given variable ordering.

### 2. [Partitioning](./partition)
* **Description**: A 2-way hypergraph partitioner based on the Fiduccia-Mattheyses (FM) algorithm, designed to minimize cut-size while maintaining area balance constraints.
* **Implementation Details**:
  * Refactored into an Object-Oriented Programming (OOP) architecture (`class FM`) for better data structure management.
  * Features iterative cell movement based on maximum gain computation and lock status.
  * Includes a best-state recovery mechanism to revert to the optimal partial sum of gains during passes.

### 3. [Maze Router](./maze_router)
* **Description**: A grid-based Maze Router that establishes shortest available paths between pins using the Lee Algorithm (BFS-based search).
* **Implementation Details**:
  * Initially sorts the netlist based on Manhattan distance.
  * Incorporates a "Rip-up and Reroute" mechanism to systematically resolve routing congestion and conflicts.
  * Reconstructs paths via backtracing using stored predecessor coordinates.

---

## Compilation and Execution
Each project is independently maintained with its own `Makefile`. 

To run a specific project:
1. Navigate to the corresponding sub-directory.
2. Run `make` to compile the executable.
3. Follow the specific execution commands outlined in the local `README.md` of each project.