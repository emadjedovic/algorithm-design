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
  vector<vector<int>> adjacencyMatrix;
  vector<Edge> edgeList;

  vector<bool> visited;
  vector<int> previous;
  void DFS_recursive_helper(int start);

public:
  Graph(int n) : numberOfNodes(n) {};

  void addEdge(Edge);
  void addNode(Node);

  void makeAdjacencyList();

  void printAdjacencyList();
  void printEdgeList();
  void printAdjacencyMatrix();

  void adjacencyListToEdgeList();
  void adjacencyListToAdjacencyMatrix();

  void DFS_classic(int start);
  void DFS_recursive(int start);

  bool containsCycle();
  void prepareVisited();
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
  adjacencyList.clear();

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

    adjacencyList.push_back(newNode);
  }
}

void Graph::adjacencyListToAdjacencyMatrix()
{
  adjacencyMatrix.resize(numberOfNodes);

  for (int i = 0; i < numberOfNodes; i++)
  {
    // square matrix
    adjacencyMatrix[i].resize(numberOfNodes);
  }

  for (int i = 0; i < numberOfNodes; i++)
  {
    // go through each node's neighbours
    Node currentNode = adjacencyList[i];
    for (int j = 0; j < currentNode.neighbours.size(); j++)
    {
      // boolean matrix for unweighted graph
      int neighbourLabel = currentNode.neighbours[j];
      adjacencyMatrix[i][neighbourLabel] = 1;
    }
  }
}

void Graph::adjacencyListToEdgeList()
{
  edgeList.clear();
  for (int i = 0; i < numberOfNodes; i++)
  {
    Node currentNode = adjacencyList[i];
    // for each node add its out-pointing edges
    for (int j = 0; j < currentNode.neighbours.size(); j++)
    {
      int endingNodeLabel = currentNode.neighbours[j];
      edgeList.push_back(Edge(i, endingNodeLabel));
    }
  }

  numberOfEdges = edgeList.size();
}

void Graph::printAdjacencyList()
{
  for (int i = 0; i < numberOfNodes; i++)
  {
    Node currentNode = adjacencyList[i];
    cout << currentNode.label << ": ";
    for (int j = 0; j < currentNode.neighbours.size(); j++)
    {
      cout << currentNode.neighbours[j] << " ";
    }

    cout << endl;
  }
}

void Graph::printEdgeList()
{
  for (int i = 0; i < numberOfEdges; i++)
  {
    edgeList[i].printEdge();
  }
}

void Graph::printAdjacencyMatrix()
{
  // first row is node labels
  cout << " ";
  for (int i = 0; i < numberOfNodes; i++)
  {
    cout << " " << i;
  }
  cout << endl;
  for (int i = 0; i < numberOfNodes; i++)
  {
    cout << i << " "; // first column for labels
    for (int j = 0; j < numberOfNodes; j++)
    {
      cout << adjacencyMatrix[i][j] << " ";
    }
    cout << endl;
  }
}

// BFS & DFS

void Graph::prepareVisited()
{
  visited.resize(numberOfNodes);
  previous.resize(numberOfNodes);
  for (int i = 0; i < numberOfNodes; i++)
  {
    visited[i] = false;
    previous[i] = -1; // start
  }
}

void Graph::DFS_classic(int start)
{
  prepareVisited();
  // use stack
  stack<int> s;
  s.push(start);
  while (!s.empty())
  {
    int nodeLabel = s.top();
    s.pop(); // takes off the stack
    // do something with the node
    cout << "Visited node: " << nodeLabel << endl;
    // push the neighbours onto the stack
    for (int i = 0; i < numberOfNodes; i++)
    {
      if (adjacencyMatrix[nodeLabel][i] != 0 && !visited[i])
        s.push(i);
    }
  }
}

void Graph::DFS_recursive(int start)
{
  prepareVisited();
  DFS_recursive_helper(start);
}

void Graph::DFS_recursive_helper(int start)
{
  visited[start] = true;
  cout << "Visited node: " << start << endl;

  for (int i = 0; i < numberOfNodes; i++)
  {
    // check the corresponding node's row in adj matrix
    // for neighbours
    if (adjacencyMatrix[start][i] != 0 && !visited[i])
    {
      cout << "Passing the edge (" << start << ", " << i << ")" << endl;
      // continue dfs
      DFS_recursive_helper(i);
    }

    // if already visited skip to next node not visited
  }
}

// removed BFS method

bool Graph::containsCycle()
{
  // DFS_classic with adjustments
  prepareVisited();
  // use stack
  stack<int> s;
  s.push(0); // start from node 0
  while (!s.empty())
  {
    int nodeLabel = s.top();
    s.pop(); // takes off the stack
    // check if already
    visited[nodeLabel] = true;
    cout << "Visited node: " << nodeLabel << endl;
    // push the neighbours onto the stack
    for (int i = 0; i < numberOfNodes; i++)
    {
      if (adjacencyMatrix[nodeLabel][i] != 0 && !visited[i])
        // neighbour, but is it already visited=
        if (!visited[i])
        {
          s.push(i);
          previous[i] = nodeLabel;
        }
        else
        {
          cout << "\nDetected cycle... " << endl;
          // write it out
          stack<int> cycle;
          cycle.push(i); // beginning of the cycle
          cycle.push(nodeLabel);
          int currentNodeLabel = nodeLabel;
          while (previous[currentNodeLabel] != i)
          {
            currentNodeLabel = previous[currentNodeLabel];
            cycle.push(currentNodeLabel);
          }
          cycle.push(i); // end of the cycle
          // cout the stack
          while (!cycle.empty())
          {
            {
              cout << cycle.top() << ", ";
              cycle.pop();
            }
          }
        }
    }
  }
}

int main()
{

  int numberOfNodes;
  cout << "Input number of nodes: ";
  cin >> numberOfNodes;

  Graph graph(numberOfNodes);
  graph.makeAdjacencyList();

  // graph.addEdge(Edge(1, 2));
  // graph.addEdge(Edge(2, 1));
  /*
    cout << "\nAdjacency list\n";
    graph.printAdjacencyList();

    cout << "\nAdjacency matrix\n";
    graph.adjacencyListToAdjacencyMatrix();
    graph.printAdjacencyMatrix();

    cout << "\nEdge list\n";
    graph.adjacencyListToEdgeList();
    graph.printEdgeList();*/

  graph.adjacencyListToAdjacencyMatrix();
  graph.containsCycle();

  return 0;
}