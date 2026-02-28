# Maze Router

## Introduction
This project implements a **Maze Router** based on the **Lee Algorithm** (BFS-based shortest path search). It features a **Rip-up and Reroute** mechanism to resolve routing congestion and conflicts.

## Algorithm Flow
* **Initial Sorting**: The net list is initially sorted based on the Manhattan distance from source to target.
* **Path Finding**: Uses the Lee Algorithm to find the shortest available path between pins.
* **Backtracing**: Once the target is reached, the path is reconstructed using stored predecessor coordinates.
* **Rip-up and Reroute**: If a net cannot be routed, all currently routed nets are ripped up; the failed net is moved to the front of the net list, and the routing procedure restarts.

## Compilation and Execution
```bash
# To compile
make

# To execute
./router <input_file_name> <output_file_name>