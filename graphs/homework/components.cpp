#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct Node
{
    int label;
    vector<int> neighbours;
};

struct Edge
{
    int start, end;
    Edge(int s, int e) : start(s), end(e) {};
    void printEdge()
    {
        cout << "(" << start << ", " << end << ")" << endl;
    }
};

class Graph
{
private:
    int numberOfNodes;
    int numberOfEdges;

    vector<Node> adjacencyList;

    void DFS(int start, vector<bool> &visited, vector<int> &currentComponent)
    {
        visited[start] = true;
        currentComponent.push_back(start);

        vector<int> neighbours = adjacencyList[start].neighbours;
        for (int neighbour : neighbours)
        {
            if (!visited[neighbour])
            {
                visited[neighbour] = true;
                DFS(neighbour, visited, currentComponent);
            }
        }
    }

public:
    Graph(int n) : numberOfNodes(n), numberOfEdges(0)
    {
        adjacencyList.resize(n);
        for (int i = 0; i < n; i++)
        {
            adjacencyList[i].label = i;
        }
    };

    void addEdge(Edge);
    void makeAdjacencyList();
    void printAdjacencyList();
    void findComponents(); // uses dfs
};

void Graph::addEdge(Edge e)
{
    adjacencyList[e.start].neighbours.push_back(e.end);
    numberOfEdges++;
}

void Graph::makeAdjacencyList()
{
    for (int i = 0; i < numberOfNodes; i++)
    {
        Node newNode;
        newNode.label = i;

        // add neighbours
        int outDegree;
        cout << "Node out-degree: ";
        cin >> outDegree;
        newNode.neighbours.clear();

        for (int j = 0; j < outDegree; j++)
        {
            int label;
            cout << "Add neighbour with label: ";
            cin >> label;
            newNode.neighbours.push_back(label);
        }

        adjacencyList[i] = newNode;
    }
}

void Graph::printAdjacencyList()
{
    for (int i = 0; i < numberOfNodes; i++)
    {
        Node currentNode = adjacencyList[i];
        cout << currentNode.label << ": ";
        for (int neighbour : currentNode.neighbours)
        {
            cout << neighbour << " ";
        }

        cout << endl;
    }
}

void Graph::findComponents()
{
    vector<bool> visited(numberOfNodes, false);
    vector<Graph> componentGraphs;

    for (int i = 0; i < numberOfNodes; i++)
    {
        if(!visited[i]) {
            vector<int> currentComponent;
            DFS(i, visited, currentComponent);
            Graph currentComponentGraph(currentComponent.size());

            // treat nodes 4, 7, 9 as 0, 1, 2...
            vector<int> localNodes(numberOfNodes, -1);
            for (size_t j = 0; j < currentComponent.size(); j++) {
                int node = currentComponent[j];
                localNodes[node] = j;
            }

            // Add nodes and edges to the component graph
            for (int node : currentComponent) {
                vector<int> neighbours = adjacencyList[node].neighbours;
                for (int neighbour : neighbours) {
                    int localStartNode = localNodes[node];
                    int localEndNode = localNodes[neighbour];

                    if (localEndNode != -1) {
                        currentComponentGraph.addEdge(Edge(localStartNode, localEndNode));
                    }
                }
            }

            // Store the component graph
            componentGraphs.push_back(currentComponentGraph);
        }
    }

    // Print adjacency lists of each component
    for (size_t i = 0; i < componentGraphs.size(); i++) {
        cout << "\nComponent " << i + 1 << " adjacency list:\n";
        componentGraphs[i].printAdjacencyList();
    }
    
    
}

int main()
{

    int numberOfNodes;
    cout << "Input number of nodes: ";
    cin >> numberOfNodes;

    Graph graph(numberOfNodes);
    graph.makeAdjacencyList();

    cout << "\nAdjacency list\n";
    graph.printAdjacencyList();

    cout << "\nConnected Components:\n";
    graph.findComponents();

    return 0;
}

/*
Input number of nodes: 7
Node 0 out-degree: 1
Add neighbour with label: 1
Node 1 out-degree: 2
Add neighbour with label: 0
Add neighbour with label: 2
Node 2 out-degree: 1
Add neighbour with label: 1
Node 3 out-degree: 1
Add neighbour with label: 4
Node 4 out-degree: 1
Add neighbour with label: 3
Node 5 out-degree: 1
Add neighbour with label: 6
Node 6 out-degree: 1
Add neighbour with label: 5

0: 1
1: 0 2
2: 1
3: 4
4: 3
5: 6
6: 5

Component 1 adjacency list:
0: 1
1: 0 2
2: 1

Component 2 adjacency list:
0: 1
1: 0

Component 3 adjacency list:
0: 1
1: 0

*/