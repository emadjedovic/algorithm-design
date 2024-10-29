// Postoji li put od s do t i koji je to put?
#include "graph.h"
#include <algorithm>

void Graph::listNodesAlongThePath(int start, int target, const vector<int> &previous)
{
    stack<int> path_stack;
    int currentNode = target;
    while (currentNode != start)
    {
        path_stack.push(currentNode);
        currentNode = previous[currentNode];
    }
    cout<<currentNode;
    while(!path_stack.empty()){
        cout<<" -> "<<path_stack.top();
        path_stack.pop();
    }
}

// koristi dfs, klasični problem s-t single-source reachability
void Graph::pathFromTo(int start, int target)
{
    stack<int> s;
    s.push(start);
    while (!s.empty())
    {
        int nodeLabel = s.top();
        visited[nodeLabel] = true;
        s.pop();

        for (int neighbour : adjacencyList[nodeLabel].neighbours)
        {
            previous[neighbour] = nodeLabel;
            if (neighbour == target)
            {
                // dosegli smo čvor koji smo željeli
                // koristimo vektor previous da ispišemo cijeli put koji smo prešli do cilja
                listNodesAlongThePath(start, target, previous);
                return;
            }
            if (!visited[neighbour])
                s.push(neighbour);
        }
    }
    cout << "Path does not exits." << endl;
}