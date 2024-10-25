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

  return 0;
}