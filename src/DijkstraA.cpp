#include <DijkstraA.hpp>

#include <limits>

long long dijkstraA(int vertices, int start, int **adj_matrix, int *distance, int *parent){
    long long comparisons = 0;

    // Initialize distance
    for(int i = 0; i < vertices; i++) distance[i] = std::numeric_limits<int>::max();
    distance[start] = 0;

    // Tracks processed vertices
    int processed[vertices] = {false};
    // Tracks current node to process
    int node = start;

    // If node is already processed, it means unable to find next node to process
    // Equivalently, all nodes are processed
    while(!processed[node]){
        processed[node] = true;

        // All remaining vertices are unreachable from start
        // Hence the algorithm does not need to continue
        if(distance[node] == std::numeric_limits<int>::max()) break;

        // Update adjacent nodes shortest distances
        for(int i = 0; i < vertices; i++){
            // If processed, we already know it is the
            // shortest path, so no need to double check
            if(processed[i]) continue;

            // If node not adjacent, skip
            if(adj_matrix[node][i] == -1) continue;

            // Updates shortest path
            comparisons++;
            if(distance[node] + adj_matrix[node][i] < distance[i]){
                distance[i] = distance[node] + adj_matrix[node][i];
                parent[i] = node;
            }
        }

        // Finds next node to process, if can't find any then node is not changed
        int curr_dist = std::numeric_limits<int>::max();
        for(int i = 0; i < vertices; i++){
            // Skip if processed already
            if(processed[i]) continue;
            
            // Find next unprocessed node with lowest distance
            comparisons++;
            if(distance[i] >= curr_dist) continue;

            // Updates node variable to next (potential) node to process
            node = i;
            curr_dist = distance[node]; // Updates new lowest distance found in remaining nodes
        }
    }

    return comparisons;
}