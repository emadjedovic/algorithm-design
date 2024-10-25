// Izlistati komponente povezanosti (napraviti za svaku komponentu zaseban graf).
#include "graph.h"
#include <algorithm>

// Modificiramo vektor visited i direktno kreiramo podgraf
void Graph::assignComponentToNeighbours(int start, vector<bool> &visited, Graph &currentComponentGraph)
{
    visited[start] = true;

    for (int neighbour : adjacencyList[start].neighbours)
    {

        if (!visited[neighbour])
        {
            currentComponentGraph.addEdge(start, neighbour); // dodaje se u oba smjera
            assignComponentToNeighbours(neighbour, visited, currentComponentGraph);
        }
    }
}

// Koristi DFS
void Graph::findComponents()
{
    vector<bool> visited(numberOfNodes, false);
    vector<Graph> componentGraphs;

    for (int i = 0; i < numberOfNodes; i++)
    {
        if (!visited[i])
        {
            Graph currentComponentGraph(numberOfNodes, false);

            assignComponentToNeighbours(i, visited, currentComponentGraph);

            componentGraphs.push_back(currentComponentGraph);
            // cout << "New component added!" << endl;
        }
    }

    // Ispisivanje komponenti
    for (size_t i = 0; i < componentGraphs.size(); i++)
    {
        cout << "Component " << i + 1 << ": { ";
        set<int> labels;
        for (Node node : componentGraphs[i].adjacencyList)
        {
            for (int neighbour : node.neighbours)
                labels.insert(neighbour);
        }
        for (int label : labels)
            cout << label << " ";
        cout<<"}\n";

        // componentGraphs[i].printAdjacencyList();
    }
}
