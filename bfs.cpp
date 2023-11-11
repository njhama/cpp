#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Node {
public:
    int value;
    vector<Node*> adj;

    Node(int val) : value(val) {}

    void addEdge(Node* node) {
        adj.push_back(node);
    }
};

class Graph {
    unordered_map<int, Node*> nodes;

public:
    ~Graph() {
        for (auto& pair : nodes) {
            delete pair.second;
        }
    }

    Node* createNode(int value) {
        if (nodes.find(value) == nodes.end()) {
            nodes[value] = new Node(value);
        }
        return nodes[value];
    }

    void addEdge(int src, int dest) {
        Node* srcNode = createNode(src);
        Node* destNode = createNode(dest);
        srcNode->addEdge(destNode);
    }

    Node* getNode(int value) {
        if (nodes.find(value) != nodes.end()) {
            return nodes[value];
        }
        return nullptr;
    }
};

void BFS(Node* startNode) {
    if (!startNode) return;

    queue<Node*> queue;
    unordered_map<Node*, bool> visited;

    visited[startNode] = true;
    queue.push(startNode);

    while (!queue.empty()) {
        Node* current = queue.front();
        queue.pop();
        cout << "Visited Node: " << current->value << endl;

        for (Node* nextNode : current->adj) {
            if (!visited[nextNode]) {
                visited[nextNode] = true;
                queue.push(nextNode);
            }
        }
    }
}

int main() {
    Graph g;

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    cout << "Breadth First Traversal starting from vertex 2:" << endl;
    BFS(g.getNode(2));

    return 0;
}
