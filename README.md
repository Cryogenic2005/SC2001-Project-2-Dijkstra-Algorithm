# SC2001 Project 2

This is the repository for the second project of NTU's SC2001 ALGORITHM DESIGN AND ANALYSIS.

Team Members:
- Le Nguyen Bao Huy
- Loke Yongen, Gabriel
- Madhumita Thiruppathi
- Manikandan Yuvana

## About the program

The program is intended to compare 2 implementations of Dijkstra's algorithm:
- **Implementation 1:** The graph is stored as an *adjacency matrix* & the algorithm uses an *array* for the priority queue.
- **Implementation 2:** The graph is stored as an *adjacency list* & the algorithm uses a *minimizing heap* for the priority queue.

Other things to note:
- Optional arguments can be used to adjust the graph generated or which algorithm to run on.
- The program will output the number of comparisons between node distances and CPU time used for each algorithm to help with the comparison.

## Compilation

To compile the project, change the working directory to this project's. 

Run the following command on the command line:

Windows:

```
    g++ -g -std=c++17 main.cpp src\*.cpp -I include -o bin\Dijkstra.exe
```

Linux:

```
    g++ -g -std=c++17 main.cpp src/*.cpp -I include -o bin/Dijkstra
```

## Running the program

Execute the program by calling it through the command line. The program accepts up to five optional arguments:

Windows:

```
    .\bin\Dijkstra.exe [NO_OF_VERTICES] [NO_OF_EDGES] [ALGORITHM] [GENERATE_NEW_GRAPH] [MAX_WEIGHT]
```

Linux & MacOS:

```
    ./bin/Dijkstra [NO_OF_VERTICES] [NO_OF_EDGES] [ALGORITHM] [GENERATE_NEW_GRAPH] [MAX_WEIGHT]
```

Arguments:
- *NO_OF_VERTICES*: The number of vertices in the graph, defaults to 1000.
- *NO_OF_EDGES*: The number of edges in the graph, defaults to -1, which means a random number of edges will be generated.
- *ALGORITHM*: The algorithm to be used, values can be **A**, **B** or **AB**. The corresponding implementation of Dijkstra's algorithm will be used for first 2 option, while both will be used for the last option. Defaults to **AB**.
- *GENERATE_NEW_GRAPH*: Specify whether to generate a new random graph (1 for yes, 0 for no), defaults to 1.
- *MAX_WEIGHT*: The maximum weight for the edges in the generated graph, defaults to 1000. Avoid making the number too high or there is risk of integer overflow.



























































