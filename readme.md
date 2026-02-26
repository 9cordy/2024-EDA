# 2024 Electronic Design Automation (EDA) Core Algorithms

This repository contains three core low-level algorithm projects developed independently using C/C++ during the "Electronic Design Automation (EDA)" course in 2024. These projects cover key technologies ranging from Logic Synthesis to Physical Design.

## 🛠️ Tech Stack
* **Programming Languages**: C / C++ (Extensive use of STL containers and memory pointers)
* **Core Technologies**: Object-Oriented Programming (OOP), Data Structure Design (Trees, Graphs), Memory Management, Custom Parsers
* **Domain Knowledge**: Physical Design Automation, Logic Minimization

---

## 📂 Projects Overview

### 1. [ROBDD (Logic Optimization & Binary Decision Diagrams)](./ROBDD)
* **Description**: Built a Reduced Ordered Binary Decision Diagram (ROBDD) core engine from scratch to process Boolean functions in Sum-of-Products (SOP) form[cite: 427].
* **Technical Highlights**: Bypassed existing third-party packages like CUDD to independently implement recursive tree construction and isomorphic subgraph reduction. Achieved precise memory deallocation and optimal node reduction through dynamic node matching.

### 2. [FM_Partition (Fiduccia-Mattheyses Algorithm)](./partition)
* **Description**: Implemented the classic FM algorithm used in physical design to optimize hardware node partitioning, minimizing the cut size (connections) across different blocks.
* **Technical Highlights**: Refactored a procedural C-style algorithm into a highly maintainable **Object-Oriented Programming (OOP)** architecture. Encapsulated graph data structures and state management to significantly enhance code readability and scalability.

### 3. [Router (Physical Routing Algorithm)](./router)
* **Description**: Developed a grid-based router applied in the physical layout stage of IC design.
* **Technical Highlights**: Optimized pathfinding algorithms for hardware layout performance and space utilization, demonstrating practical capability in handling and parsing large-scale hardware netlist nodes.

---

## 🚀 How to Run
Each project folder includes a standalone `Makefile` and test cases. Navigate to the specific project directory and use the `make` command to compile the source code and generate the executable binary. 

Please refer to the documentation within each specific project folder for detailed execution parameters and input formats.