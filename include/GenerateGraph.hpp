#pragma once

#include <filesystem>

/// @brief Function to generate a directed, weighted graph with random edges and output to a .dat file
/// @param number_of_vertices Number of vertices in the graph
/// @param number_of_edges Number of edges in the graph, -1 for random count
/// @param max_weight Maximum weight of a generated edge
/// @param file_path Path to the .dat file
void generateGraph(int number_of_vertices, int number_of_edges, int max_weight, const std::filesystem::path& file_path);

/// @brief Function to read a directed, weighted graph from a .dat file
/// @param number_of_vertices Number of vertices in the graph
/// @param adj_matrix Adjacency matrix to store the graph
/// @param file_path Path to the .dat file
/// @return Number of vertices in the graph
int readGraph(int number_of_vertices, int **adj_matrix, const std::filesystem::path& file_path);
