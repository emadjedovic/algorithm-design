/*
find all nodes that can be visited by the path from the initial node so that each subsequent node has a higher index than the previous one

use dfs, store path, but consider only nodes with higher index
*/

#include <iostream>
#include <vector>

using namespace std;

void modifiedDFS(int node, const vector<vector<int>> &adjList, vector<bool>& visited)
{
    visited[node] = true;
    vector<int> neighbours = adjList[node];
    for(int n: neighbours)
    {
        if(!visited[n] && n>node)
        modifiedDFS(n, adjList, visited);
    }
}

vector<int> ascendingPath(int startNode, const vector<vector<int>> &adjList)
{
    vector<bool> visited(adjList.size(), false);
    modifiedDFS(startNode, adjList, visited);
    // we need only extract nodes from visited...
    
    vector<int> result;
    for(size_t i=0; i<adjList.size(); i++)
    {
        if(visited[i])
        result.push_back(i);
    }

    return result;
}

int main()
{
    vector<vector<int>> test=
    {
        {1,2,3},
        {2,3},
        {3},
        {}
    };

    vector<int> result = ascendingPath(0, test);
    for(int x: result)
    {
        cout<<x<<" ";
    }
    return 0;
}