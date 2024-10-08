#include <DijkstraA.hpp>
#include <DijkstraB.hpp>
#include <GenerateGraph.hpp>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int DEFAULT_NUM_VERTICES = 1000;
const int DEFAULT_NUM_EDGES = -1; // Unused, number of edges is random
const std::string DEFAULT_ALGORITHM = "AB";
const bool DEFAULT_GENERATE_GRAPH = true;
const int DEFAULT_MAX_WEIGHT = 1000;

// Function prototypes
void convertToAdjList(int number_of_vertices, int **adj_matrix, std::vector<std::pair<int,int>> adj_list[]);
void outputResults(int number_of_vertices, int distance[], int parent[], const std::filesystem::path& file_path, const std::string& file_name_append);

int main(int argc, char* argv[]) {
    // Parse command line arguments
    int num_vertices = (argc > 1) ? std::stoi(argv[1]) : DEFAULT_NUM_VERTICES;
    int num_edges = (argc > 2) ? std::stoi(argv[2]) : DEFAULT_NUM_EDGES;
    std::string algorithm = (argc > 3) ? argv[3] : DEFAULT_ALGORITHM;
    bool generate_graph_flag = (argc > 4) ? (argv[4][0] == '1') : DEFAULT_GENERATE_GRAPH;
    int max_weight = (argc > 5) ? std::stoi(argv[5]) : DEFAULT_MAX_WEIGHT;

    // Construct path to graph file
    std::filesystem::path file_path;
    file_path /= "data";
    file_path /= "graph_" + std::to_string(num_vertices) + ".dat";

    // Initialize adjacency matrix
    int** adj_matrix = new int*[num_vertices];
    for (int i = 0; i < num_vertices; ++i) {
        adj_matrix[i] = new int[num_vertices];
    }

    // Generate graph if flag is set
    std::cout << "Generating graph... ";
    if (generate_graph_flag) {
        generateGraph(num_vertices, num_edges, max_weight, file_path);
    }
    std::cout << "Done!" << std::endl;

    // Read graph from file
    try {
        std::cout << "Reading graph... ";
        readGraph(num_vertices, adj_matrix, file_path);
        std::cout << "Done!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error reading graph file: " << e.what() << std::endl;
        return 1;
    }

    // Set precision for floating-point output
    std::cout << std::fixed << std::setprecision(2);

    // Run Dijkstra's algorithm version A
    if (algorithm == "A" || algorithm == "AB") {
        // Initialize distance and parent arrays
        int distance[num_vertices];
        int parent[num_vertices];

        // Run Dijkstra's algorithm version A
        auto start = std::chrono::steady_clock::now();
        long long comparisons = dijkstraA(num_vertices, 0, adj_matrix, distance, parent);
        auto end = std::chrono::steady_clock::now();

        std::cout << "DijkstraA used " << comparisons << " comparisons" << std::endl;

        std::cout << "DijkstraA took " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0l << "ms" << std::endl;

        // Output algorithm's result to file
        outputResults(num_vertices, distance, parent, file_path, "_a");
    }

    // Run Dijkstra's algorithm version B
    if (algorithm == "B" || algorithm == "AB") {
        // Convert adjacency matrix to adjacency list
        std::vector<std::pair<int,int>> adj_list[num_vertices];
        convertToAdjList(num_vertices, adj_matrix, adj_list);

        // Initialize distance and parent arrays
        int distance[num_vertices];
        int parent[num_vertices];

        // Run Dijkstra's algorithm version B
        auto start = std::chrono::steady_clock::now();
        long long comparisons = dijkstraB(num_vertices, 0, adj_list, distance, parent);
        auto end = std::chrono::steady_clock::now();

        std::cout << "DijkstraB used " << comparisons << " comparisons" << std::endl;

        std::cout << "DijkstraB took " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0l << "ms" << std::endl;

        // Output algorithm's result to file
        outputResults(num_vertices, distance, parent, file_path, "_b");
    }

    // Clean up dynamically allocated memory
    for (int i = 0; i < num_vertices; ++i) {
        delete[] adj_matrix[i];
    }
    delete[] adj_matrix;

    return 0;
}

void convertToAdjList(int number_of_vertices, int **adj_matrix, std::vector<std::pair<int,int>> adj_list[]) {
    for (int i = 0; i < number_of_vertices; i++) {
        for (int j = 0; j < number_of_vertices; j++) {
            if (adj_matrix[i][j] != -1) {
                adj_list[i].push_back(std::pair<int,int>(j, adj_matrix[i][j]));
            }
        }
    }
}

void outputResults(int number_of_vertices, int distance[], int parent[], const std::filesystem::path& file_path, const std::string& file_name_append) {
    std::filesystem::path output_file_path = file_path;
    output_file_path.replace_extension(""); // Remove the file extension
    output_file_path += file_name_append;
    output_file_path.replace_extension(".out"); // Add new file extension

    std::ofstream output_file(output_file_path);
    if (!output_file) {
        std::cerr << "Error opening output file" << std::endl;
        return;
    }

    for (int i = 0; i < number_of_vertices; ++i) {
        output_file << "v = " << i 
            << ", d = " << distance[i] 
            << ", p = " << parent[i] << std::endl;
    }
}