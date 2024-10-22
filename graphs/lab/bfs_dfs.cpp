#include <iostream>
#include <vector>
#include <queue>
using namespace std;


void BFS(const vector<vector<int>> graph){
    // track queued
    vector<bool> queued(graph.size(), false);

    queue<int> visitingQueue;
    visitingQueue.push(0); // start
    queued[0] = true;

    // no need for helper function because this is iterative
    while(!visitingQueue.empty()) {
        int currentNode = visitingQueue.front();
        vector<int> neighbours = graph[currentNode];

        for (size_t i = 0; i < neighbours.size(); i++)
        {
            // don't add nodes that are already added
            if(!queued[neighbours[i]]){
                visitingQueue.push(neighbours[i]);
                queued[neighbours[i]] = true;
            }
        }

        // do something with the current node
        cout<<currentNode<<" ";
        visitingQueue.pop();
        

    }

}

void DFS_helper(const vector<vector<int>> graph, int start, vector<int>& visited){
    if(!visited[start]) {
        visited[start] = true;
        cout<<start<<" ";
        vector<int> neighbours = graph[start];
        for(int neighbour: neighbours){
            DFS_helper(graph, neighbour, visited);
            // no unvisited neighbours left
        }
    }

}

void DFS(const vector<vector<int>> graph){
    // track visited
    vector<int> visited(graph.size(), false);
    DFS_helper(graph, 0, visited);
    
}

int main()
{
    // using adjacency list
    vector<vector<int>> graph {
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
    BFS(graph);
    cout<<"\nDFS: ";
    DFS(graph);
    return 0;
}
