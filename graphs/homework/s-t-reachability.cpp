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

  void DFS(int start, int target);
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

void listNodesAlongThePath(int start, int target, const vector<int> &path){
  int currentNode = target;
  while(currentNode != start){
    cout<<currentNode<<"<-";
    currentNode = path[currentNode];
  }
  cout<<start;
}

void Graph::DFS(int start, int target)
{
  // non-recursive DFS (using stack)
  stack<int> s;
  s.push(start);
  while (!s.empty())
  {
    int nodeLabel = s.top();

    // Mark the node as visited
    visited[nodeLabel] = true;
    cout << "Visited node: " << nodeLabel << endl;
    s.pop();

    // Push the neighbors onto the stack
    for (int neighbour : adjacencyList[nodeLabel].neighbours)
    {
      if(neighbour == target){
        // we have reached the target
        // use previous vector to list the nodes along the path
        previous[neighbour] = nodeLabel;
        listNodesAlongThePath(start, target, previous);
        return;
      }
      if (!visited[neighbour])
      {
        s.push(neighbour);
        previous[neighbour] = nodeLabel;
      }
    }
  }
  cout<<"No path found from start node to target!"<<endl;
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

  int s, t;
  cout<<"Input start node s and target node s to determine reachability: ";
  cin>>s>>t;
  graph.DFS(s,t);

  return 0;
};

