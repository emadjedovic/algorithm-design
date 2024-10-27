// Implementirati detekciju grana - mostova (grane pretvoriti u čvorove i onda naći artikulacione čvorove).
#include "graph.h"
#include <map>

Graph Graph::switchEdgesNodes()
{
    // koristimo atribut map<pair<int, int>, int> edgeToNode
    // mapa grana - čvor, neophodno prije nego nađemo koje grane dijele čvor u originalnom grafu

    int edgesMappedToNodes = 0; // indeksi čvorova u edgeToNode

    // za svaku granu u originalnom grafu...
    for (int i = 0; i < numberOfNodes; i++)
    {
        vector<int> neighbours = adjacencyList[i].neighbours;
        for (int neighbor : neighbours)
        {
            if (i < neighbor || isDirected)
            {
                edgeToNode[{i, neighbor}] = edgesMappedToNodes++;
            }
        }
    }

    // dodajemo grane i čvorove u instancu klase Graph
    Graph result(numberOfEdges, isDirected);

    for (int i = 0; i < numberOfNodes; i++)
    {
        const vector<int> &neighbours = adjacencyList[i].neighbours;
        // npr. u 3-5-6 nalazimo se u 5 i gledamo oba susjeda lijevo i desno,
        // kako bismo čvor 5 pretvorili u granu
        for (size_t j = 0; j < neighbours.size(); j++)
        {
            for (size_t k = j + 1; k < neighbours.size(); k++)
            {
                int neighbor1 = neighbours[j]; // susjed 3
                int neighbor2 = neighbours[k]; // susjed 6

                // koji čvor reprezentira granu (3,5) u edgeToNode
                int node1 = edgeToNode[{min(i, neighbor1), max(i, neighbor1)}];
                // koji čvor reprezentira granu (5,6) u edgeToNode
                int node2 = edgeToNode[{min(i, neighbor2), max(i, neighbor2)}];
                // dodajemo granu koja reprezentira čvor 5
                result.addEdge(node1, node2);
            }
        }
    }
    return result;
}

// redoslijed kojim obilazimo čvorove dfsom
void Graph::assignNum(int v, int& counter) {
    num[v] = counter++;
    visited[v] = true;

    
    for (int w : adjacencyList[v].neighbours) {
        if (!visited[w]) {
            parent[w] = v;
            assignNum(w, counter);
            
            low[v] = min(low[v], low[w]);
            
            if (parent[v] != -1 && low[w] >= num[v]) {
                articulationPoints.insert(v);
            }
            
            if (parent[v] == -1) {
                articulationPoints.insert(v);
            }
        } else if (w != parent[v]) { 
            // Update `low` for back edges
            low[v] = min(low[v], num[w]);
        }
    }
}

// najniži reachable čvorovi (koristeći maksimalno jednu back-edge)
void Graph::assignLow(int v)
{
    low[v] = num[v]; // prvo pravilo

    for (int w : adjacencyList[v].neighbours)
    {
        if (num[w] > num[v])
        { // forward edge
            assignLow(w);
            if (low[w] >= num[v])
                articulationPoints.insert(v);
            low[v] = min(low[v], low[w]); // treće pravilo
        }
        else if (parent[v] != w)
        {                                 // back edge
            low[v] = min(low[v], num[w]); // drugo pravilo
        }
    }
}

void Graph::findArticulationPoints()
{
    // inicijalizacije
    num.resize(numberOfNodes, -1);
    low.resize(numberOfEdges, -1);
    visited.resize(numberOfNodes, false);
    parent.resize(numberOfNodes, -1);
    articulationPoints.clear();

    int counter = 0;
    for (int v = 0; v < numberOfNodes; ++v)
    {
        if (!visited[v])
        {
            assignNum(v, counter);
            assignLow(v);
        }
    }

    /*
        cout<<"\nnums: ";
        for(int i: num)  cout<<i<<" ";

         cout<<"\nlows: ";
        for(int i: low) cout<<i<<" ";
    */

    // ispisujemo sve
    cout << "Articulation points: { ";
    for (int ap : articulationPoints)
    {
        cout << ap << " ";
    }
    cout << "}"<<endl;
}

void Graph::findBridges() {
    bridges.clear();
    Graph convertedGraph = switchEdgesNodes();

    convertedGraph.findArticulationPoints();

    for (int ap : convertedGraph.articulationPoints) {
        for (const auto& edge : edgeToNode) {
            if (edge.second == ap) {
                bridges.insert(edge.first);
            }
        }
    }

    cout << "Bridges:\n";
    for (const auto& edge : bridges) {
        cout << "(" << edge.first << ", " << edge.second << ")" << endl;
    }
}

