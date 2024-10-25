#include "graph.h"

Graph::Graph(int n, bool d) : numberOfNodes(n), numberOfEdges(0), isDirected(d)
{
    adjacencyList.resize(n);
    visited.resize(n, false);
    previous.resize(n, -1);
    for (int i = 0; i < n; i++)
    {
        adjacencyList[i].label = i;
        adjacencyList[i].indegree = 0;
    }
}

void Graph::addEdge(int start, int end)
{
    adjacencyList[start].neighbours.push_back(end);
    adjacencyList[end].indegree++;
    if (!isDirected)
    {
        adjacencyList[end].neighbours.push_back(start);
        adjacencyList[start].indegree++;
    }
    numberOfEdges++;
}

void Graph::makeAdjacencyList()
{
    for (int i = 0; i < numberOfNodes; i++)
    {
        Node newNode;
        newNode.label = i;

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
            adjacencyList[label].indegree++;
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

void Graph::adjacencyListToAdjacencyMatrix()
{
  adjacencyMatrix.resize(numberOfNodes, vector<int>(numberOfNodes));

  for (int i = 0; i < numberOfNodes; i++)
    adjacencyMatrix[i].resize(numberOfNodes);

  for (int i = 0; i < numberOfNodes; i++)
  {
    Node currentNode = adjacencyList[i];
    for (size_t j = 0; j < currentNode.neighbours.size(); j++)
    {
      int neighbourLabel = currentNode.neighbours[j];
      adjacencyMatrix[i][neighbourLabel] = 1;
    }
  }
}

void Graph::printAdjacencyMatrix()
{
  // first row is node labels
  cout << " ";
  for (int i = 0; i < numberOfNodes; i++) cout << " " << i;
  cout << endl;
  for (int i = 0; i < numberOfNodes; i++)
  {
    cout << i << " "; // first column for labels
    for (int j = 0; j < numberOfNodes; j++) cout << adjacencyMatrix[i][j] << " ";
    cout << endl;
  }
}