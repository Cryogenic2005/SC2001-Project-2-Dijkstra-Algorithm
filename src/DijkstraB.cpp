#include <DijkstraB.hpp>

#include <vector>
#include <queue>
#include <limits>

// Custom comparator for comparing second element of two pairs.
// Returns a.second > b.second
struct CompareSecond{
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b){
        return a.second > b.second;
    }
};

void dijkstraB(int vertices, int start, std::vector<std::pair<int,int>> adj_list[], int *distance, int *parent){
    // Initialize distance
    for(int i = 0; i < vertices; i++) distance[i] = std::numeric_limits<int>::max();
    distance[start] = 0;

    // Tracks processed vertices
    int processed[vertices] = {false};
    // Tracks next node with smallest distance
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, CompareSecond> min_heap;
    min_heap.push(std::pair<int,int>(start, 0));
    // Tracks current node processing
    int node;

    while(!min_heap.empty()){
        // Repeat try getting next valid node until heap empty 
        do{
            node = min_heap.top().first;
            min_heap.pop();
        }while(processed[node] && !min_heap.empty());

        // If heap is empty and node is invalid (already processed), break
        if(min_heap.empty() && processed[node]) break;

        processed[node] = true;

        // All remaining vertices are unreachable from start
        // Hence the algorithm does not need to continue
        if(distance[node] == std::numeric_limits<int>::max()) return;

        // Update adjacent nodes
        for(int i = 0; i < adj_list[node].size(); i++){
            int neighbor = adj_list[node][i].first;
            int weight = adj_list[node][i].second;

            // If processed, we already know the
            // shortest path, so no need to double check
            if(processed[neighbor]) continue;

            // Updates shortest path
            if(distance[node] + weight < distance[neighbor]){
                distance[neighbor] = distance[node] + weight;
                parent[neighbor] = node;

                min_heap.push(std::pair<int, int>(neighbor, distance[neighbor]));
            }
        }
    }
}