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
    cout<<"Euler circuit possible..."<<endl;

    vector<int> eulerCircuit;
    stack<int> path;
    adjacencyListToAdjacencyMatrix(); // popunjava matricu susjedstva
    vector<vector<int>> mat = adjacencyMatrix; // kopija

    path.push(0); // ovdje bilježimo traversal

    while (!path.empty()) {
        int currentNode = path.top();
        bool hasUnusedEdge = false;

        // prolazimo matricom susjedstva
        for (size_t neighbor = 0; neighbor < mat.size(); ++neighbor) {
            if (mat[currentNode][neighbor] == 1) {
                // stavljamo susjeda na stack
                path.push(neighbor);
                // pređene grane uklanjamo (postavljamo na 0)
                mat[currentNode][neighbor] = 0;
                if(!isDirected) mat[neighbor][currentNode] = 0;
                hasUnusedEdge = true;
                break; // nastavljamo dalje od ovog susjeda
            }
        }

        // nema susjeda (sve grane iskorištene/uklonjene)
        if (!hasUnusedEdge) {
            eulerCircuit.push_back(currentNode);
            path.pop();
        }
    }

    cout << "Euler Circuit: ";
    for (int node : eulerCircuit) {
        cout << node << " ";
    }
    cout << endl<<endl;
}
