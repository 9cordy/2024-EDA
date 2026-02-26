# 2024 Electronic Design Automation Core Algorithms

This repository contains three core low-level algorithm projects developed independently using C/C++ for the "Electronic Design Automation" course. These projects cover key methodologies in the EDA flow, ranging from Logic Synthesis to Physical Design, implemented under strict performance and runtime constraints.

## Tech Stack
* **Programming Languages**: C/C++ (Extensive use of STL containers, pointers, and memory management)
* **Core Technologies**: Object-Oriented Programming, Graph Theory, Heuristic Algorithms, Custom Parsers
* **Domain Knowledge**: Physical Design Automation, Logic Minimization, Routing

---

## Projects Overview

### 1. [ROBDD (Logic Optimization & Binary Decision Diagrams)](./ROBDD)
* **Objective**: Construct Reduced Ordered Binary Decision Diagrams (ROBDDs) from Boolean equations in Sum-of-Products form and determine the optimal variable ordering that requires the minimum number of nodes.
* **Technical Highlights**: 
  * Achieved the strictest assignment requirement by **building the ROBDD core engine completely from scratch without using the standard CUDD package** (awarded 20% bonus). 
  * Implemented recursive tree construction, isomorphic subgraph reduction, and dynamic node matching to optimize memory usage.

### 2. [FM_Partition (Circuit Partitioning)](./partition)
* **Objective**: Partition a given hardware netlist into two groups to minimize the cut size while strictly maintaining a balance factor between **0.45 and 0.55**.
* **Technical Highlights**: 
  * Implemented the classic **Fiduccia-Mattheyses (FM) algorithm**.
  * Refactored a procedural C-style approach into a highly maintainable **Object-Oriented Programming (OOP)** architecture. 
  * Optimized execution efficiency to strictly pass the 30-second time limit constraint.

### 3. [Router (2D Maze Routing Algorithm)](./router)
* **Objective**: Develop a 2D maze router for a two-terminal routing problem on a gridded routing region with blockages, aiming to connect all terminals while minimizing the total wiring grids.
* **Technical Highlights**: 
  * Handled complex pathfinding around blockages and implemented routing logic to prevent grid overlapping.
  * Demonstrated practical capability in parsing grid coordinates and managing large-scale hardware routing data.

---

## How to Run
Each project folder contains a standalone `Makefile` and test cases (`.txt` or `.hgr` files). 

To compile and execute a project:
1. Navigate to the specific project directory.
2. Run `make` to compile the source code into an executable binary.
3. Execute the binary with the required input and output arguments as specified in the local instructions.