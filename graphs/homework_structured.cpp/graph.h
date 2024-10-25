/*

ZADAĆA (PREDAVANJA 1-3)

1. Postoji li put od s do t i koji je to put?

2. Detekcija ciklusa (čuvati ih u vektoru vektora) i njihovo ispisivanje.

3. Izlistati komponente povezanosti (napraviti za svaku komponentu zaseban graf).

4. Topološko sortiranje. O(E+V). Čuvati queue čvorova izlaznog stepena 0.

NAPOMENA: Korišten šablon grafa data na predavanjima, s tim da su izbačene neke stvari koje
nisu od važnosti ovdje i smatram da je bez njih kod čitljiviji. Npr. izbačena je struktura Edge,
izbačene su matrica susjedstva i lista grana, kao i njihove pripadajuće konverzije i printanje.

Djedović Ema, 6009/M

*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
using namespace std;

struct Node
{
    int label;
    vector<int> neighbours;
    int indegree = 0; // za topološko sortiranje
};

class Graph
{
private:
    int numberOfNodes;
    int numberOfEdges;
    bool isDirected;
    vector<Node> adjacencyList;

    vector<bool> visited;
    vector<int> previous;
    set<set<int>> cycles; // da izbjegnemo ponavljanja

     // ZADATAK 3 (pomoćna funkcija)
    void assignComponentToNeighbours(int start, vector<bool> &visited, Graph &currentComponentGraph);

public:
    Graph(int n, bool d=false);
    void addEdge(int start, int end);
    void makeAdjacencyList();
    void printAdjacencyList();

    void pathFromTo(int start, int target);                                     // ZADATAK 1
    void listNodesAlongThePath(int start, int target, const vector<int> &path); // ZADATAK 1
    void cycle_detection_undirected();                                          // ZADATAK 2
    void printCycles();                                                         // ZADATAK 2
    void findComponents();                                                      // ZADATAK 3
    void topologicalSort();                                                     // ZADATAK 4
};

Graph::Graph(int n, bool d) : numberOfNodes(n), numberOfEdges(0), isDirected(d)
{
    adjacencyList.resize(n);
    visited.resize(n, false);
    previous.resize(n, -1);
    for (int i = 0; i < n; i++)
    {
        adjacencyList[i].label = i;
        adjacencyList[i].indegree = 0;
    }
};

void Graph::addEdge(int start, int end)
{
    adjacencyList[start].neighbours.push_back(end);
    adjacencyList[end].indegree++;
    if(!isDirected){
        adjacencyList[end].neighbours.push_back(start);
        adjacencyList[start].indegree++;
    }
    numberOfEdges++;
}
void Graph::makeAdjacencyList()
{
    for (int i = 0; i < numberOfNodes; i++)
    {
        Node newNode;
        newNode.label = i;

        int outDegree;
        cout << "Node out-degree: ";
        cin >> outDegree;
        newNode.neighbours.clear();
        for (int j = 0; j < outDegree; j++)
        {
            int label;
            cout << "Add neighbour with label: ";
            cin >> label;
            newNode.neighbours.push_back(label);
            adjacencyList[label].indegree++;
        }
        adjacencyList[i] = newNode;
    }
}

void Graph::printAdjacencyList()
{
    for (int i = 0; i < numberOfNodes; i++)
    {
        Node currentNode = adjacencyList[i];
        cout << currentNode.label << ": ";
        for (int neighbour : currentNode.neighbours)
        {
            cout << neighbour << " ";
        }
        cout << endl;
    }
}

#endif