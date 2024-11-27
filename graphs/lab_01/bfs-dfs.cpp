#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

void BFS(int start, const vector<vector<int>>& adjList, vector<bool>& queued)
{
    queued.resize(adjList.size(), false);
    queue<int> q;
    q.push(start);
    queued[start] = true;

    while(!q.empty())
    {   
        int currentNode = q.front();
        cout<<currentNode<<" ";
        q.pop();

        vector<int> neighbours = adjList[currentNode];
        // push all neighbours to the queue
        for(int n: neighbours)
        {
            if(queued[n]) continue;
            q.push(n);
            queued[n] = true;
        }
    }

}

void DFS(int node, const vector<vector<int>>& adjList, vector<bool>& visited)
{
    cout<<node<<" ";
    visited[node] = true;
    vector<int> neighbours = adjList[node];
    for(int n: neighbours)
    {
        if(!visited[n])
        DFS(n, adjList, visited);
    }
}

void DFSstack(int start, const vector<vector<int>>& adjList, vector<bool>& stacked)
{
    stacked.resize(adjList.size(), false);
    stack<int> s;
    s.push(start);
    stacked[start] = true;

    while(!s.empty())
    {
        int currentNode = s.top();
        cout<<currentNode<<" ";
        s.pop();

        vector<int> neighbours = adjList[currentNode];
        for(int n: neighbours)
        {
            if(stacked[n]) continue;
            s.push(n);
            stacked[n] = true;
        }
    }
}

int main()
{
    vector<vector<int>> adjList =
    {
        {1,2,5}, // 0
        {0,2,3}, // 1
        {0,9,6}, // 2
        {4,1}, // 3
        {3,6}, // 4
        {0}, // 5
        {2,4,7}, // 6
        {6,8}, // 7
        {7}, // 8
        {2} // 9
    };

    cout<<"\nBFS: ";
    vector<bool> bfsVisited;
    BFS(0, adjList, bfsVisited);

    vector<bool> dfsVisited;
    dfsVisited.resize(adjList.size(), false);

    cout<<"\nDFS: ";
    DFS(0, adjList, dfsVisited);

    vector<bool> dfsVisitedStack;
    cout<<"\nDFS with stack: ";
    DFSstack(0, adjList, dfsVisitedStack);

    return 0;
}


/*
BFS: 0 1 2 5 3 9 6 4 7 8 
DFS: 0 1 2 9 6 4 3 7 8 5 
DFS with stack: 0 5 2 6 7 8 4 3 9 1 
*/