// Implementirati ispis Eulerove ture (ciklusa). Prvo provjeriti parnost čvorova. Koristiti matricu susjedstva.
#include "graph.h"

// kod usmjerenog grafa za svaku ulaznu granu mora bit jedna izlazna
bool Graph::hasEulerCircuit()
{
    if (isDirected)
    {
        // jednaki ulazni i izlazni stepen
        for (const Node &node : adjacencyList)
        {
            int outDegree = node.neighbours.size();
            int inDegree = node.indegree;
            if (inDegree != outDegree)
                return false;
        }
    }
    else
    {
        // svi parnog stepena za neusmjerene grafove
        for (const Node &node : adjacencyList)
            if (node.neighbours.size() % 2 != 0)
                return false;
    }
    return true;
}

void Graph::findEulerCircuit()
{
    if (!hasEulerCircuit())
    {
        cout << "No Euler circuit possible." << endl;
        return;
    }
    cout << "Euler circuit possible..." << endl;

    vector<int> eulerCircuit;
    stack<int> path_stack;
    adjacencyListToAdjacencyMatrix();          // popunjava matricu susjedstva
    vector<vector<int>> mat = adjacencyMatrix; // kopija

    path_stack.push(0); // ovdje bilježimo traversal

    while (!path_stack.empty())
    {
        int currentNode = path_stack.top();
        bool hasUnusedEdge = false;

        // prolazimo matricom susjedstva
        for (size_t column = 0; column < mat[0].size(); column++)
        {
            if (mat[currentNode][column] == 1)
            {
                // stavljamo susjeda na stack
                path_stack.push(column);
                // pređene grane uklanjamo (postavljamo na 0)
                mat[currentNode][column] = 0;
                if (!isDirected)
                    mat[column][currentNode] = 0;

                hasUnusedEdge = true; // nepređena grana
                break; // nastavljamo dalje od ovog susjeda
            }
        }

        // ako su sve grane iskorištene onda se vraćamo nazad
        if (!hasUnusedEdge)
        {
            eulerCircuit.push_back(currentNode);
            path_stack.pop(); // backtrack na prethodni čvor
        }
    }

    cout << "Euler Circuit: ";
    for (int node : eulerCircuit)
        cout << node << " ";
    cout << endl << endl;
}
