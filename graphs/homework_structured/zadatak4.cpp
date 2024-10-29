// Topološko sortiranje. O(E+V). Čuvati queue čvorova izlaznog stepena 0.
#include "graph.h"

void Graph::topologicalSort()
{
    queue<int> zeroIndegreeNodes;
    vector<int> order;

    // kreiramo kopiju jer ne želimo izmijeniti originalni graf
    vector<int> tempIndegree(numberOfNodes);
    for (int i = 0; i < numberOfNodes; ++i)
        tempIndegree[i] = adjacencyList[i].indegree;

    // naći sve čvorove ulaznog stepena 0
    for (int i = 0; i < numberOfNodes; i++)
        if (tempIndegree[i] == 0)
            zeroIndegreeNodes.push(i);

    // konstruiramo topološki redoslijed
    while (!zeroIndegreeNodes.empty())
    {
        int currentNode = zeroIndegreeNodes.front();
        order.push_back(currentNode);
        zeroIndegreeNodes.pop();

        // smanjujemo ulazne stepene susjeda jer uklanjamo čvor koji smo upravo dodali u poredak
        for (int neighbour : adjacencyList[currentNode].neighbours)
        {
            tempIndegree[neighbour]--;
            if (tempIndegree[neighbour] == 0)
                zeroIndegreeNodes.push(neighbour);
        }
    }

    // izašli smo iz while petlje jer nemamo više čvorova ulaznog stepena nula,
    // ali neki čvorovi ostali neobrađeni, znači nemamo DAG
    if (order.size() != numberOfNodes)
    {
        cout << "Topological sort detected a cycle (sorting not possible)." << endl;
        return;
    }

    for (int i : order)
        cout << i << " ";
    cout << endl;
}
