#include <GenerateGraph.hpp>

#include <fstream>
#include <filesystem>
#include <random>

void generateGraph(int number_of_vertices, int number_of_edges, int maximum_weight, const std::filesystem::path& file_path)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> weight_distribution(1, maximum_weight);

    // Initialize adjacency matrix to generate edge weights into
    int** adj_matrix = new int*[number_of_vertices];
    for (int i = 0; i < number_of_vertices; ++i)
        adj_matrix[i] = new int[number_of_vertices];
        
    for (int i = 0; i < number_of_vertices; i++)
        for (int j = 0; j < number_of_vertices; j++)
            adj_matrix[i][j] = -1;

    number_of_edges = std::min(
        number_of_edges, 
        number_of_vertices * (number_of_vertices - 1)
    );

    // Random count of edges to generate
    if (number_of_edges <= -1)
        number_of_edges = rd() % ((number_of_vertices * (number_of_vertices - 1)) / 2) + 1;

    // Generate random edges
    for (int i = 0; i < number_of_edges; i++)
    {
        // Choose 2 distinct vertices with no edge between them
        int u, v;
        do
        {
            u = rd() % number_of_vertices;
            v = rd() % number_of_vertices;
        } while (u == v || adj_matrix[u][v] != -1);

        // Assign random weight to edge
        adj_matrix[u][v] = weight_distribution(gen);
    }

    // Write to file at designated path
    std::ofstream output_file(file_path, std::ios::binary);
    if(!output_file){
        throw std::runtime_error("Error opening file");
    }

    // Write number of vertices and adjacency matrix to file
    output_file.write(reinterpret_cast<char*>(&number_of_vertices), sizeof(int));
    for (int i = 0; i < number_of_vertices; i++)
        output_file.write(reinterpret_cast<char*>(adj_matrix[i]), number_of_vertices * sizeof(int));

    // Output to text file for human readability
    std::filesystem::path text_file_path = file_path;
    text_file_path.replace_extension(".txt");
    
    std::ofstream text_file(text_file_path);
    if(!text_file){
        throw std::runtime_error("Error opening file");
    }

    // Write number of vertices, edge count, and edges to text file
    text_file << number_of_vertices << std::endl;
    text_file << number_of_edges << std::endl;
    for (int i = 0; i < number_of_vertices; i++)
    {
        for (int j = 0; j < number_of_vertices; j++)
        {
            if (adj_matrix[i][j] != -1)
                text_file << i << " " << j << " " << adj_matrix[i][j] << std::endl;
        }
    }
}

int readGraph(int number_of_vertices, int** adj_matrix, const std::filesystem::path& file_path)
{
    // Read from file at designated path
    std::ifstream input_file(file_path, std::ios::binary);
    if(!input_file){
        throw std::runtime_error("Error opening file");
    }

    // Read number of vertices and adjacency matrix from file
    int n;
    input_file.read(reinterpret_cast<char*>(&n), sizeof(int));
    if(n != number_of_vertices){
        throw std::runtime_error("Number of vertices in file does not match input");
    }

    for (int i = 0; i < number_of_vertices; i++)
        input_file.read(reinterpret_cast<char*>(adj_matrix[i]), number_of_vertices * sizeof(int));

    return number_of_vertices;
}
