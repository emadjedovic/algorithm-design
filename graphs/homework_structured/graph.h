/*

ZADAĆA (PREDAVANJA 1-3)

1. Postoji li put od s do t i koji je to put?

2. Detekcija ciklusa (čuvati ih u vektoru vektora) i njihovo ispisivanje.

3. Izlistati komponente povezanosti (napraviti za svaku komponentu zaseban graf).

4. Topološko sortiranje. O(E+V). Čuvati queue čvorova izlaznog stepena 0.

5. Implementirati crtanje grafa. Dati čvorovima koordinate. Linije simulirati recimo sa +++++.

6. Implementirati ispis Eulerove ture (ciklusa). Prvo provjeriti parnost čvorova. Koristiti matricu susjedstva.

7. Implementirati detekciju grana - mostova (grane pretvoriti u čvorove i onda naći artikulacione čvorove).

NAPOMENA: Korišten šablon grafa data na predavanjima, s tim da su izbačene neke stvari koje
nisu od važnosti ovdje i smatram da je bez njih kod čitljiviji. Npr. izbačena je struktura Edge,
 lista grana, neke konverzije iz jedne reprezentacije u drugu itd. Korišten chatGPT za smislenije
 imenovanje varijabli i metoda, generisanje testnih primjera i slično.

Djedović Ema, 6009/M

*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
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
    vector<vector<int>> adjacencyMatrix;

    vector<bool> visited;
    vector<int> previous;
    set<set<int>> cycles;               // da izbjegnemo ponavljanja
    vector<pair<int, int>> coordinates; // za crtanje grafa

    void assignComponentToNeighbours(int start, vector<bool> &visited, Graph &currentComponentGraph);

    // za artikulacione čvorove
    vector<int> num;    // redni broj posjete
    vector<int> low;    // najniži čvor do kojeg možemo doći
    vector<int> parent; // parent vertices in DFS tree
    set<int> articulationPoints;
    void assignNum(int v, int &counter);
    void assignLow(int v);
    // mostovi (zadatak 7)
    map<pair<int, int>, int> edgeToNode;
    set<pair<int, int>> bridges;

public:
    Graph(int n, bool d = false);
    void addEdge(int start, int end);
    void makeAdjacencyList();
    void printAdjacencyList();

    void adjacencyListToAdjacencyMatrix(); // euler
    void printAdjacencyMatrix();           // euler

    void pathFromTo(int start, int target);                                     // ZADATAK 1
    void listNodesAlongThePath(int start, int target, const vector<int> &path); // ZADATAK 1
    void cycle_detection_undirected();                                          // ZADATAK 2
    void printCycles();                                                         // ZADATAK 2
    void findComponents();                                                      // ZADATAK 3
    void topologicalSort();                                                     // ZADATAK 4

    // ZADATAK 5
    Graph convertToUndirected() const;
    void assignCoordinatesUsingBFS();
    void printCoordinates();
    void drawGraph();
    void drawInstantly(); // sve metode u jednom

    // ZADATAK 6
    bool hasEulerCircuit();
    void findEulerCircuit();

    // ZADATAK 7
    Graph switchEdgesNodes();
    void findArticulationPoints();
    void findBridges();
};

#endif