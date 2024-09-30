#pragma once

#include <vector>

/// @brief Performs Dijkstra algorithm with the input graph as an
/// adjencency list and a minimizing heap for the priority queue
/// @param vertices Number of vertices in the graph
/// @param start Starting node
/// @param adj_list Adjacency list of graph (weighted, directed). Stores pairs of ints.
/// First value is the node, second value is the edge weight
/// @param distance returns shortest distance between start and all other nodes
/// @param parents returns predecessor of selected node to backtrack shortest path
void dijkstraB(int vertices, int start, std::vector<std::pair<int,int>> adj_list[], int *distance, int *parent);