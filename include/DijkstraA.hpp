#pragma once

/// @brief Performs Dijkstra algorithm with the input graph as an
/// adjencency matrix and an array for the priority queue
/// @param vertices Number of vertices in the graph
/// @param start Starting node
/// @param adj_matrix Adjacency matrix of graph (weighted, directed). 
/// Non-adjacent nodes should be set to -1. Format: adj_matrix[start_node][end_node].
/// @param distance returns shortest distance between start and all other nodes
/// @param parents returns predecessor of selected node to backtrack shortest path
void dijkstraA(int vertices, int start, int **adj_matrix, int *distance, int *parent);