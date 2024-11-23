/*
find the number of components (connected parts) of a graph

standard dfs
*/

#include <iostream>
#include <vector>

using namespace std;

void DFS(int node, const vector<vector<int>> &adjList, vector<bool> &visited)
{
    if (visited[node])
        return;
    visited[node] = true;
    vector<int> neighbours = adjList[node];
    for (int n : neighbours)
        DFS(n, adjList, visited);
}

int numComponents(const vector<vector<int>> &adjList)
{
    int result = 0;
    vector<bool> visited(adjList.size(), false);
    for (size_t i = 0; i < adjList.size(); i++)
    {
        if (!visited[i])
        {
            // call dfs
            DFS(i, adjList, visited);
            // no more unvisited neighbours
            result++;
        }
        // in case not all nodes are processed the loop continues
    }
    return result;
}

int main()
{
    vector<vector<int>> test = {
        {1,2},
        {0},
        {0},
        {},
        {}
    };
    int x = numComponents(test);
    cout<<x<<endl;
    return 0;
}