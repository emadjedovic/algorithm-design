#include <iostream>
#include <vector>
#include <list>
#include <stack>
using namespace std;

class Graph
{
    int numNodes;
    bool isDirected;
    vector<list<int>> adjacencyList;

    void DFSrec_times(int start, vector<bool> &visited, vector<pair<int, int>> &times, int &time);
    void DFSrec_finishingOrder(int start, vector<bool> &visited, stack<int> &finishingOrder);
    void DFSrec_components(int start, vector<bool> &visited, list<int> &components);

public:
    Graph(int n, bool d = false) : numNodes(n), isDirected(d)
    {
        adjacencyList.resize(n);
    }

    void addEdge(int start, int end);
    void BFS(int start = 0);
    void DFS(int start = 0);
    void distancesFrom(int start);
    vector<int> pathFromTo(int from, int to);
    list<int> topSort();
    void topSortRec(int node, vector<bool> &visited, list<int> &result);
    void printGraph();
    list<list<int>> SCC();
};

int main()
{
    Graph G(8);
    G.addEdge(0, 1);
    G.addEdge(0, 3);
    G.addEdge(3, 1);
    G.addEdge(2, 3);
    G.addEdge(2, 5);
    G.addEdge(3, 7);
    G.addEdge(7, 6);
    G.addEdge(6, 5);
    G.addEdge(4, 7);
    G.addEdge(6, 4);
    G.addEdge(2, 0);
    G.printGraph();
    G.BFS();
    G.DFS();
    return 0;
}

void Graph::addEdge(int start, int end)
{
    adjacencyList[start].push_back(end);
    if (!isDirected)
        adjacencyList[end].push_back(start);
}

void Graph::printGraph()
{
    for (int i = 0; i < numNodes; i++)
    {
        cout << "Node " << i << ": ";
        for (int neighbour : adjacencyList[i])
            cout << neighbour << " ";
        cout << endl;
    }
}

void Graph::DFSrec_times(int start, vector<bool> &visited, vector<pair<int, int>> &times, int &time)
{
}

void Graph::DFSrec_finishingOrder(int start, vector<bool> &visited, stack<int> &finishingOrder)
{
}

void Graph::DFSrec_components(int start, vector<bool> &visited, list<int> &components)
{
}

void Graph::BFS(int start)
{
}

void Graph::DFS(int start)
{
}

void Graph::distancesFrom(int start)
{
}

vector<int> Graph::pathFromTo(int from, int to)
{
    return vector<int>();
}

list<int> Graph::topSort()
{
    return list<int>();
}

void Graph::topSortRec(int node, vector<bool> &visited, list<int> &result)
{
}

list<list<int>> Graph::SCC()
{
    return list<list<int>>();
}
