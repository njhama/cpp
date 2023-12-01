#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// A structure to represent a connected, undirected and weighted graph
struct Graph {
    int V, E;
    vector<Edge> edges;

    // Constructor
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    // Function to add an edge to the graph
    void addEdge(int src, int dest, int weight) {
        Edge edge = {src, dest, weight};
        edges.push_back(edge);
    }
};

// A structure to represent a subset for union-find
struct subset {
    int parent;
    int rank;
};

// A utility function to find set of an element i (uses path compression technique)
int find(subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// A function that does union of two sets of x and y (uses union by rank)
void Union(subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare two edges according to their weights
bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// The main function to construct MST using Kruskal's algorithm
void KruskalMST(Graph& graph) {
    vector<Edge> result; // This will store the resultant MST

    // Step 1: Sort all the edges in non-decreasing order of their weight
    sort(graph.edges.begin(), graph.edges.end(), compareEdges);

    // Allocate memory for creating V subsets
    subset *subsets = new subset[graph.V];

    // Create V subsets with single elements
    for (int v = 0; v < graph.V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int e = 0; // Index used to pick next edge

    // Number of edges to be taken is equal to V-1
    while (result.size() < graph.V - 1 && e < graph.E) {
        // Step 2: Pick the smallest edge. And increment the index for next iteration
        Edge next_edge = graph.edges[e++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge doesn't cause cycle, include it in result
        if (x != y) {
            result.push_back(next_edge);
            Union(subsets, x, y);
        }
    }

    // print the contents of result[] to display the built MST
    cout << "Following are the edges in the constructed MST\n";
    for (auto &edge : result)
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;

    delete[] subsets; // Clean up the dynamic memory allocation
}

int main() {
    /* Let us create following weighted graph
             10
        0--------1
        |  \     |
       6|   5\   |15
        |      \ |
        2--------3
            4       */
    int V = 4;  // Number of vertices in graph
    int E = 5;  // Number of edges in graph
    Graph graph(V, E);

    // add edge 0-1
    graph.addEdge(0, 1, 10);

    // add edge 0-2
    graph.addEdge(0, 2, 6);

    // add edge 0-3
    graph.addEdge(0, 3, 5);

    // add edge 1-3
        // ... [previous code] ...

    // add edge 1-3
    graph.addEdge(1, 3, 15);

    // add edge 2-3
    graph.addEdge(2, 3, 4);

    // Function call
    KruskalMST(graph);

    return 0;
}

