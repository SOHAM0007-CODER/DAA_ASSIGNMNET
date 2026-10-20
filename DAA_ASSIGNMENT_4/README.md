# DAA Assignment 4: Dijkstra's Algorithm

## Description
This assignment provides an implementation of **Dijkstra's Algorithm** in C++ to find the single-source shortest path in a weighted graph. The algorithm identifies the shortest path from a starting node to a destination node, ensuring the optimal cost is calculated. 

Additionally, the program allows dynamic updates to the graph's edge weights, recalculating the optimal path immediately after any updates.

## Features
- **Shortest Path Calculation:** Finds the minimum cost path and reconstructs the optimal path sequence.
- **Dynamic Edge Updates:** Users can update the weight of an existing connection and immediately observe the effect on the shortest path.
- **Adjacency Matrix Representation:** The graph is represented using a 2D matrix structure.
- **Robust Input Validation:** Ensures edges and weights are within valid boundaries.

## How to Run
1. Compile the code:
   ```bash
   g++ "Dijkstra's .cpp" -o Dijkstra
   ```
   *(Note: Ensure correct handling of spaces and special characters in the filename or rename it to `Dijkstra.cpp`)*
2. Run the application:
   ```bash
   ./Dijkstra
   ```
3. Input the number of nodes and connections (edges).
4. Provide the edge details: `Node1 Node2 Weight`.
5. Enter the source and destination nodes to find the path.
6. Follow the on-screen prompts if you wish to update any connections dynamically.

## Input file
`input.txt` contains the values from output.png: 5 nodes, 7 connections,
source 0, destination 4, and N for no update. Expected minimum cost: 10;
path: 0 -> 2 -> 1 -> 3 -> 4. Node IDs start at 0 in this program.
