// Neusmjereni graf
// Detekcija ciklusa (čuvati ih u vektoru vektora) i njihovo ispisivanje.
#include "graph.h"

void Graph::printCycles()
{
    int cycle_index = 1;
    for (const auto &cycle : cycles)
    {
        cout << "CYCLE #" << cycle_index << ": { ";
        for (int node : cycle)
        {
            cout << node << " ";
        }
        cout << "}\n";
        cycle_index++;
    }
}

// koristi dfs s tim da vodi evidenciju prethodnih čvorova
void Graph::cycle_detection_undirected()
{
    cycles.clear();
    visited.assign(numberOfNodes, false);
    previous.assign(numberOfNodes, -1); 

    stack<int> s;
    s.push(0);
    while (!s.empty())
    {
        int nodeLabel = s.top();
        s.pop();

        visited[nodeLabel] = true;
        //cout << "Visited node: " << nodeLabel << endl;

        // stavljamo susjede na stack i updateujemo vektor prethodnika
        for (int neighbour : adjacencyList[nodeLabel].neighbours)
        {
            if (!visited[neighbour])
            {
                s.push(neighbour);
                previous[neighbour] = nodeLabel;
            }
            else
            {
                if(neighbour==previous[nodeLabel]) continue;
                // naišli na već posjećen čvor
                //cout << "Encountered already visited node: " << neighbour<<endl;
                set<int> cycle;
                cycle.insert(neighbour);
                cycle.insert(nodeLabel);
                int currentNodeLabel = nodeLabel;

                while (previous[currentNodeLabel] != neighbour)
                {
                    currentNodeLabel = previous[currentNodeLabel];
                    cycle.insert(currentNodeLabel);
                }
                cycles.insert(cycle);
            }
        }
    }
}