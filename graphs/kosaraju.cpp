// STRONG COMPONENTS
// KOSARAJU ALGORITHM
// reverse post order on reversed graph
// dfs (standard preorder) on original graph

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Node
{
	int label;
	vector<int> neighbours;
};

class Graph
{
private:
	int numberOfNodes;
	vector<Node> adjacencyList;
	vector<bool> visited;
	vector<int> postOrderVector;
	vector<int> assignedComponents;

	void postOrder(int);
	void assignComponentToNode(int, int, const vector<Node> &);
	vector<Node> reverseGraph();

public:
	Graph(int n) : numberOfNodes(n)
	{
		adjacencyList.resize(n);
		for (int i = 0; i < n; i++)
			adjacencyList[i].label = i;
		visited.resize(n, false);
		postOrderVector.resize(n);
		assignedComponents.resize(n, -1);
	}

	void addEdge(int start, int end)
	{
		adjacencyList[start].neighbours.push_back(end);
	}

	void makeAdjacencyList();
	void findStronglyConnectedComponents();
	void printAdjacencyList();
};


void Graph::makeAdjacencyList()
{
	for (int i = 0; i < numberOfNodes; i++)
	{
		int outDegree;
		cout << "Out-degree of node #" << i << ": ";
		cin >> outDegree;
		// add neighbours prompt
		for (int j = 0; j < outDegree; j++)
		{
			int neighbourLabel;
			cout << "Add neighbour: ";
			cin >> neighbourLabel;
			addEdge(i, neighbourLabel);
		}
	}
}



void Graph::printAdjacencyList()
{
	for (int i = 0; i < numberOfNodes; i++)
	{
		cout << "Node " << i << ": ";
		vector<int> neighbours = adjacencyList[i].neighbours;
		for (int neighbour : neighbours)
			cout << neighbour << " ";
		cout << endl;
	}
}

// dfs (recursive) but push_back at the end
void Graph::postOrder(int start)
{
	visited[start] = true; // visited but add last
	vector<int> neighbours = adjacencyList[start].neighbours;
	for (int neighbour : neighbours)
	{
		if (!visited[neighbour])
			postOrder(neighbour);
	}
	// no left neighbours
	postOrderVector.push_back(start);
}

void Graph::assignComponentToNode(int node, int componentNum, const vector<Node> &adjList)
{
	assignedComponents[node] = componentNum;
	vector<int> neighbours = adjList[node].neighbours;
	for (int neighbour : neighbours)
	{
		// component not assigned yet
		if (assignedComponents[neighbour] == -1)
			assignComponentToNode(neighbour, componentNum, adjList);
	}
}

vector<Node> Graph::reverseGraph()
{
	vector<Node> reversedGraphAdjList(numberOfNodes);
	for (int i = 0; i < numberOfNodes; i++)
		reversedGraphAdjList[i].label = i;

	// add neighbours but reverse edges
	for (int i = 0; i < numberOfNodes; i++)
	{
		vector<int> neighbours = adjacencyList[i].neighbours;
		for (int neighbour : neighbours)
		{
			// go to that neighbour's index in our reversed graph's adjacency list and update there
			reversedGraphAdjList[neighbour].neighbours.push_back(i);
		}
	}
	return reversedGraphAdjList;
}


// Kosaraju in 3 steps
void Graph::findStronglyConnectedComponents()
{
	// Step 1: reverse post-order on reversed graph
	Graph reversed(numberOfNodes);
	reversed.adjacencyList = reverseGraph();
	for(int i=0; i<numberOfNodes; i++){
		if(!reversed.visited[i]){
			reversed.postOrder(i);
		}
	}
	reverse(reversed.postOrderVector.begin(), reversed.postOrderVector.end());
	
	// Step 2: dfs on original graph (standard preorder or postorder)
	int componentNum = 0;
	for (size_t i = 0; i<reversed.postOrderVector.size(); i++)
	{
		int currentNode = reversed.postOrderVector[i];
		// single-reachability in other way
		if (assignedComponents[currentNode] == -1)
		{
			assignComponentToNode(currentNode, componentNum, adjacencyList);
			componentNum++;
		}
	}

	// display results
	for (int i = 0; i < numberOfNodes; i++)
		cout << "Node " << i << " is in the component " << assignedComponents[i] << endl;
}

int main()
{
	int n;
	cout << "Number of nodes in a graph: ";
	cin >> n;

	Graph graph(n);
	graph.makeAdjacencyList();

	cout << "\nAdjacency List:" << endl;
	graph.printAdjacencyList();

	cout << "\nStrongly Connected Components:" << endl;
	graph.findStronglyConnectedComponents();

	return 0;
}
