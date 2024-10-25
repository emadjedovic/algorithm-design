#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm> // for reverse
using namespace std;

class Graph
{
    int numVertices;
    bool isDirected;
    vector<list<int>> adjacencyList;

    // Helper functions for DFS traversal
    void DFSrec_timestamps(int vertex, vector<bool> &visited, vector<pair<int, int>> &timestamps, int &time);
    void DFSrec_finishingOrder(int vertex, vector<bool> &visited, stack<int> &finishingOrder);
    void DFSrec_component(int vertex, vector<bool> &visited, list<int> &component);

public:
    Graph(int vertices, bool directed = false) : numVertices(vertices), isDirected(directed)
    {
        adjacencyList.resize(vertices);
    }

    // Function prototypes
    void addEdge(int source, int destination);
    void BFS(int startVertex = 0);
    void DFS_timestamps(int startVertex = 0);
    void distancesFrom(int startVertex);
    vector<int> pathFromTo(int source, int destination);
    list<int> topologicalSort();
    void topSortRec(int vertex, vector<bool> &visited, list<int> &result);
    void printGraph();
    list<list<int>> stronglyConnectedComponents();
};

void Graph::addEdge(int source, int destination)
{
    adjacencyList[source].push_back(destination);
    if (!isDirected)
        adjacencyList[destination].push_back(source);
}

void Graph::printGraph()
{
    for (int i = 0; i < numVertices; i++)
    {
        cout << "Vertex " << i << ": ";
        for (int neighbor : adjacencyList[i])
            cout << neighbor << " ";
        cout << endl;
    }
}

void Graph::BFS(int startVertex)
{
    vector<bool> visited(numVertices, false);
    visited[startVertex] = true;
    queue<int> queue;
    queue.push(startVertex);

    while (!queue.empty())
    {
        int currentVertex = queue.front();
        cout << "Visiting vertex " << currentVertex << endl;
        queue.pop();

        for (int neighbor : adjacencyList[currentVertex])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }
}

void Graph::DFS_timestamps(int startVertex)
{
    vector<pair<int, int>> timestamps(numVertices); // discovery time and finishing time
    vector<bool> visited(numVertices, false);
    int time = 0;

    DFSrec_timestamps(startVertex, visited, timestamps, time);

    for (int i = 0; i < numVertices; i++)
    {
        cout << "Vertex " << i << ": Discovery time = " << timestamps[i].first
             << ", Finish time = " << timestamps[i].second << endl;
    }
}

void Graph::DFSrec_timestamps(int vertex, vector<bool> &visited, vector<pair<int, int>> &timestamps, int &time)
{
    visited[vertex] = true;
    timestamps[vertex].first = time++; // Record discovery time

    cout << "Visited vertex " << vertex << endl;

    for (int neighbor : adjacencyList[vertex])
    {
        if (!visited[neighbor])
        {
            DFSrec_timestamps(neighbor, visited, timestamps, time);
        }
    }
    timestamps[vertex].second = time++; // Record finishing time
}

// bfs
void Graph::distancesFrom(int startVertex)
{
    vector<int> distances(numVertices, -1);
    distances[startVertex] = 0;
    queue<int> queue;
    queue.push(startVertex);

    while (!queue.empty())
    {
        int currentVertex = queue.front();
        queue.pop();

        for (int neighbor : adjacencyList[currentVertex])
        {
            if (distances[neighbor] == -1)
            {
                distances[neighbor] = distances[currentVertex] + 1;
                queue.push(neighbor);
            }
        }
    }

    for (int i = 0; i < numVertices; i++)
    {
        cout << "Vertex " << i << ": Distance from start = " << distances[i] << endl;
    }
}

vector<int> Graph::pathFromTo(int source, int destination)
{
    vector<pair<int, int>> distanceAndPrevious(numVertices, {-1, -1});
    distanceAndPrevious[source].first = 0;
    distanceAndPrevious[source].second = -2;

    queue<int> queue;
    queue.push(source);

    while (!queue.empty())
    {
        int currentVertex = queue.front();
        queue.pop();

        for (int neighbor : adjacencyList[currentVertex])
        {
            if (distanceAndPrevious[neighbor].first == -1)
            { // Not visited
                distanceAndPrevious[neighbor].first = distanceAndPrevious[currentVertex].first + 1;
                queue.push(neighbor);
                distanceAndPrevious[neighbor].second = currentVertex;
                if (neighbor == destination)
                    break;
            }
        }
    }

    // Reconstruct the path from destination to source
    vector<int> path;
    path.push_back(destination); // we will reverse this later
    int currentVertex = destination;

    while (currentVertex != source)
    {
        currentVertex = distanceAndPrevious[currentVertex].second;
        path.push_back(currentVertex);
    }

    reverse(path.begin(), path.end()); // iterators
    return path;
}

list<int> Graph::topologicalSort()
{
    list<int> sortedOrder;
    vector<bool> visited(numVertices, false);

    for (int i = 0; i < numVertices; i++)
    {
        if (!visited[i])
            topSortRec(i, visited, sortedOrder);
    }

    return sortedOrder;
}

void Graph::topSortRec(int vertex, vector<bool> &visited, list<int> &result)
{
    visited[vertex] = true;

    for (int neighbor : adjacencyList[vertex])
    {
        if (!visited[neighbor])
        {
            topSortRec(neighbor, visited, result);
        }
    }
    result.push_front(vertex);
}

// finishing order is related to postorder
void Graph::DFSrec_finishingOrder(int vertex, vector<bool> &visited, stack<int> &finishingOrder)
{
    visited[vertex] = true;

    for (int neighbor : adjacencyList[vertex])
    {
        if (!visited[neighbor])
        {
            DFSrec_finishingOrder(neighbor, visited, finishingOrder);
        }
    }

    finishingOrder.push(vertex); // Push the vertex to the stack based on its finishing time
}

void Graph::DFSrec_component(int vertex, vector<bool> &visited, list<int> &component)
{
    visited[vertex] = true;
    component.push_back(vertex);

    for (int neighbor : adjacencyList[vertex])
    {
        if (!visited[neighbor])
        {
            DFSrec_component(neighbor, visited, component);
        }
    }
}

list<list<int>> Graph::stronglyConnectedComponents()
{
    stack<int> finishingOrder; // postorder
    vector<bool> visited(numVertices, false);

    for (int i = 0; i < numVertices; i++)
    {
        if (!visited[i])
        {
            DFSrec_finishingOrder(i, visited, finishingOrder);
        }
    }

    // Create the transpose graph (reverse graph)
    Graph transposeGraph(numVertices, true);
    for (int i = 0; i < numVertices; i++)
    {
        for (int neighbor : adjacencyList[i])
        {
            transposeGraph.addEdge(neighbor, i);
        }
    }

    // Perform DFS on the transpose graph in the order of finishing times
    list<list<int>> components;
    visited = vector<bool>(numVertices, false); // Reset visited array

    while (!finishingOrder.empty())
    {
        int currentVertex = finishingOrder.top();
        finishingOrder.pop();

        if (!visited[currentVertex])
        {
            list<int> component;
            // starting from current vertex, push it into the newly created component, as well as all its neighbours etc.
            // this is a strong component
            transposeGraph.DFSrec_component(currentVertex, visited, component);
            components.push_back(component);
        }
    }

    return components;
}

// Test the graph implementation with a small example
int main()
{
    Graph graph(6, true); // Create a directed graph with 6 vertices

    // Add edges
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(1, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(5, 3);

    cout << "Graph structure:" << endl;
    graph.printGraph();

    cout << "\nBFS starting from vertex 0:" << endl;
    graph.BFS(0);

    cout << "\nDFS starting from vertex 0 (timestamps):" << endl;
    graph.DFS_timestamps(0);

    cout << "\nTopological Sort:" << endl;
    list<int> topSortOrder = graph.topologicalSort();
    for (int vertex : topSortOrder)
    {
        cout << vertex << " ";
    }
    cout << endl;

    cout << "\nStrongly Connected Components:" << endl;
    list<list<int>> components = graph.stronglyConnectedComponents();
    int i = 1;
    for (const list<int> &component : components)
    {
        cout << "Component " << i++ << ": ";
        for (int vertex : component)
        {
            cout << vertex << " ";
        }
        cout << endl;
    }

    return 0;
}
