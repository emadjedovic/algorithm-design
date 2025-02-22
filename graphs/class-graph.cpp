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
  void DFS_recursive_helper(int start);

public:
  Graph(int n) : numberOfNodes(n)
  {
    adjacencyList.resize(n);
    adjacencyMatrix.resize(n, vector<int>(n));
    visited.resize(n);
  };

  void addEdge(Edge);
  void addNode(Node);

  void makeAdjacencyList();

  void printAdjacencyList();
  void printEdgeList();
  void printAdjacencyMatrix();

  void adjacencyListToEdgeList();
  void adjacencyListToAdjacencyMatrix();

  void DFS_classic(int start);
  void BFS_classic(int start);
  // void BFS(int start);
  void DFS_recursive(int start);
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
  // erases all elements, reducing size to zero
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
    for (size_t j = 0; j < currentNode.neighbours.size(); j++)
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
    for (size_t j = 0; j < currentNode.neighbours.size(); j++)
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
    for (size_t j = 0; j < currentNode.neighbours.size(); j++)
      cout << currentNode.neighbours[j] << " ";

    cout << endl;
  }
}

void Graph::printEdgeList()
{
  for (int i = 0; i < numberOfEdges; i++)
    edgeList[i].printEdge();
}

void Graph::printAdjacencyMatrix()
{
  // first row is node labels
  cout << " ";
  for (int i = 0; i < numberOfNodes; i++)
    cout << " " << i;
  cout << endl;
  for (int i = 0; i < numberOfNodes; i++)
  {
    cout << i << " "; // first column for labels
    for (int j = 0; j < numberOfNodes; j++)
      cout << adjacencyMatrix[i][j] << " ";
    cout << endl;
  }
}

// BFS & DFS

void Graph::DFS_classic(int start)
{
  visited.resize(numberOfNodes, false);
  // use stack
  stack<int> s;
  s.push(start);
  while (!s.empty())
  {
    int nodeLabel = s.top();
    s.pop(); // takes off the stack

    visited[nodeLabel] = true;
    // do something with the node
    cout << "Visited node: " << nodeLabel << endl;

    // push the neighbours onto the stack
    vector<int> neighbours = adjacencyList[nodeLabel].neighbours;
    for (int neighbour : neighbours)
      if (!visited[neighbour])
        s.push(neighbour);
  }
}

void Graph::DFS_recursive_helper(int start)
{
  // same as classic DFS
  visited[start] = true;
  cout << "Visited node: " << start << endl;

  // instead of pushing the neighbours onto the stack, we call the function recursively
  vector<int> neighbours = adjacencyList[start].neighbours;
  for (int neighbour : neighbours)
    if (!visited[neighbour])
    {
      cout << "Passing the edge (" << start << ", " << neighbour << ")" << endl;
      DFS_recursive_helper(neighbour);
    }

}

void Graph::DFS_recursive(int start)
{
  visited.resize(numberOfNodes, false);
  DFS_recursive_helper(start);
}

void Graph::BFS_classic(int start)
{
  visited.resize(numberOfNodes, false);
  queue<int> q;
  q.push(start);
  while (!q.empty())
  {
    int nodeLabel = q.front();
    q.pop();
    // do something with the node
    if (!visited[nodeLabel])
    {
      visited[nodeLabel] = true;
      cout << "Visited node: " << nodeLabel << endl;
      // push neighbours into queue
      vector<int> neighbours = adjacencyList[nodeLabel].neighbours;
      for (int neighbour : neighbours)
        if (!visited[neighbour])
          q.push(neighbour);
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

  cout << "\nAdjacency list\n";
  graph.printAdjacencyList();

  cout << "\nAdjacency matrix\n";
  graph.adjacencyListToAdjacencyMatrix();
  graph.printAdjacencyMatrix();

  cout << "\nEdge list\n";
  graph.adjacencyListToEdgeList();
  graph.printEdgeList();

  cout << "BFS from node 0: " << endl;
  graph.BFS_classic(0);

  return 0;
}