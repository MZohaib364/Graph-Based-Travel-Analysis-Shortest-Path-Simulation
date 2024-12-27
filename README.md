# Graph-Based Travel Analysis: Shortest Path Simulation

This project implements a simulation for analyzing travel between cities using graph traversal techniques. It employs Breadth-First Search (BFS) for traversal and a custom shortest path algorithm to compute minimum travel days between cities.

## Features
- **Graph Representation**: Cities and routes are represented as an adjacency list.
- **BFS Traversal**: Explore the city graph level by level.
- **Shortest Path Calculation**: Calculate the minimum travel days required to reach the destination using a custom algorithm.
- **Dynamic Input Handling**: Supports multiple test cases with user-defined city counts and routes.
- **Memory Management**: Dynamically allocates and deallocates memory for graph structures.

## Code Highlights
- Custom `Queue` class for BFS traversal.
- Adjacency list representation for efficient graph operations.
- Functions for adding edges, performing BFS, and computing shortest paths.
- Interactive input handling for multiple cases.

## Input Format
1. **Number of Cases**: Enter the number of test cases.
2. For each case:
   - **Number of Cities**: Total cities in the graph.
   - **Number of Aerial Routes**: Count of direct city-to-city connections.
   - **Route Details**: Enter pairs of source and destination cities for each aerial route.

## Output
For each test case, the program outputs the minimum number of travel days required to reach the destination.

