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

  vector<bool> visited;
  vector<int> previous;
  vector<vector<int>> cycles;

public:
  Graph(int n) : numberOfNodes(n)
  {
    adjacencyList.resize(n);
    visited.resize(n, false);
    previous.resize(n, -1);
  };

  void addEdge(Edge);
  void addNode(Node);

  void makeAdjacencyList();
  void printAdjacencyList();

  void DFS_with_cycle_detection();
  void printCycles();
};

void Graph::addEdge(Edge e)
{
  adjacencyList[e.start].neighbours.push_back(e.end);
  numberOfEdges++;
}

void Graph::addNode(Node v)
{
  adjacencyList.push_back(v);
  v.label = numberOfNodes;
  numberOfNodes++;
}

void Graph::makeAdjacencyList()
{
  for (int i = 0; i < numberOfNodes; i++)
  {
    // create a node
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
    for (size_t j = 0; j < currentNode.neighbours.size(); j++)
    {
      cout << currentNode.neighbours[j] << " ";
    }

    cout << endl;
  }
}

void Graph::DFS_with_cycle_detection()
{
  // non-recursive DFS (using stack) with cycle detection
  stack<int> s;
  s.push(0); // Start from node 0
  while (!s.empty())
  {
    int nodeLabel = s.top();
    s.pop();

    // Mark the node as visited
    visited[nodeLabel] = true;
    cout << "Visited node: " << nodeLabel << endl;

    // Push the neighbors onto the stack
    for (int neighbour : adjacencyList[nodeLabel].neighbours)
    {
      if (!visited[neighbour])
      {
        s.push(neighbour);
        previous[neighbour] = nodeLabel;
      }
      else
      {
        // Detected a cycle
        cout << "\nDetected cycle... " << endl;

        vector<int> cycle;
        cycle.push_back(neighbour); // Start of the cycle
        cycle.push_back(nodeLabel);
        int currentNodeLabel = nodeLabel;

        // Trace back to form the full cycle
        while (previous[currentNodeLabel] != neighbour)
        {
          currentNodeLabel = previous[currentNodeLabel];
          cycle.push_back(currentNodeLabel);
        }
        cycle.push_back(neighbour); // End of the cycle

        // Store the detected cycle in the cycles matrix
        cycles.push_back(cycle);
      }
    }
  }
}

void Graph::printCycles()
{
  cout << "\nCycles detected:" << endl;
  int cycle_index = 1;
  for (const auto &cycle : cycles)
  {
    cout << "CYCLE #" << cycle_index << endl;
    for (int node : cycle)
    {
      cout << node << " ";
    }
    cout << endl;
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

  graph.DFS_with_cycle_detection();
  graph.printCycles();

  return 0;
};

/*
INPUT

Input number of nodes: 5
Node 0 out-degree: 1
1
Node 1 out-degree: 2
2, 3
Node 2 out-degree: 1
0
Node 3 out-degree: 1
4
Node 4 out-degree: 1
1

OUTPUT

Adjacency list
0: 1
1: 2 3
2: 0
3: 4
4: 1

Cycles detected:
0 2 1 0
1 4 3 1

*/