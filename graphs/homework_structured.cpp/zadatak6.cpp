// Implementirati ispis Eulerove ture (ciklusa). Prvo provjeriti parnost čvorova. Koristiti matricu susjedstva.
#include "graph.h"

// kod usmjerenog grafa za svaku ulaznu granu mora bit jedna izlazna
bool Graph::hasEulerCircuit() {
    if (isDirected) {
        // jednaki ulazni i izlazni stepen
        for (const Node &node : adjacencyList) {
            int outDegree = node.neighbours.size();
            int inDegree = node.indegree;
            if (inDegree != outDegree) {
                return false;
            }
        }
    } else {
        // svi parnog stepena za neusmjerene grafove
        for (const Node &node : adjacencyList) {
            if (node.neighbours.size() % 2 != 0) {
                return false;
            }
        }
    }
    return true;
}

void Graph::findEulerCircuit() {
    if (!hasEulerCircuit()) {
        cout << "No Euler circuit possible." << endl;
        return;
    }

    vector<int> eulerCircuit;
    stack<int> path;
    adjacencyListToAdjacencyMatrix();
    vector<vector<int>> mat = adjacencyMatrix; // Copy of the adjacency matrix

    // Start from the first node that has an outgoing edge
    path.push(0);

    while (!path.empty()) {
        int currentNode = path.top();
        bool hasUnusedEdge = false;

        for (size_t neighbor = 0; neighbor < mat.size(); ++neighbor) {
            if (mat[currentNode][neighbor] == 1) {
                // Found an unused edge
                path.push(neighbor);
                mat[currentNode][neighbor] = 0; // Mark the edge as used
                if(!isDirected)
                mat[neighbor][currentNode] = 0;
                hasUnusedEdge = true;
                break; // Go to this neighbor
            }
        }

        if (!hasUnusedEdge) {
            // If no unused edges, add to Euler circuit and pop the stack
            eulerCircuit.push_back(currentNode);
            path.pop();
        }
    }

    cout << "Euler Circuit: ";
    for (int node : eulerCircuit) {
        cout << node << " ";
    }
    cout << endl;
}
