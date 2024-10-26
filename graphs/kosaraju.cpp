// STRONG COMPONENTS
// KOSARAJU ALGORITHM
// post order on original graph
// reverse post order on reversed graph

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Node
{
	int label;
	vector<int> neighbours;
	Node(int l = -1) : label(l) {}
};

class Graph
{
private:
	int numberOfNodes;
	vector<Node> adjacencyList;
	vector<bool> visited;
	vector<int> postOrderVector;
	vector<int> assignedComponents;

	void postOrder(int start)
	{
		visited[start] = true; // visited but add last
		vector<int> neighbours = adjacencyList[start].neighbours;
		for (int neighbour : neighbours)
		{
			if (!visited[neighbour])
			{
				postOrder(neighbour);
			}
		}
		// no left neighbours
		postOrderVector.push_back(start);
	}

	// out-pointing edges from a node in reversed graph
	void assignComponentInReversed(int nodeLabel, int componentNum, const vector<Node> &reversedGraphAdjList)
	{
		assignedComponents[nodeLabel] = componentNum;
		vector<int> neighbours = reversedGraphAdjList[nodeLabel].neighbours;
		for (int neighbour : neighbours)
		{
			if (assignedComponents[neighbour] == -1)
			{
				assignComponentInReversed(neighbour, componentNum, reversedGraphAdjList);
			}
		}
	}

	vector<Node> reverseGraph()
	{
		vector<Node> reversedGraphAdjList(numberOfNodes);
		for (int i = 0; i < numberOfNodes; i++)
		{
			reversedGraphAdjList[i].label = i;
		}
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

public:
	Graph(int n) : numberOfNodes(n)
	{
		adjacencyList.resize(n);
		for (int i = 0; i < n; i++)
		{
			// label the nodes
			adjacencyList[i].label = i;
		}
		visited.resize(n, false);
		postOrderVector.resize(n);
		assignedComponents.resize(n, -1);
	}

	void addEdge(int start, int end)
	{
		// update adjacency list
		adjacencyList[start].neighbours.push_back(end);
	}

	void makeAdjacencyList()
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

	// Kosaraju in 3 steps
	void findStronglyConnectedComponents()
	{
		// Step 1: post-order on original graph
		// single-reachability from original graph
		for (int i = 0; i < numberOfNodes; i++)
		{
			if (!visited[i])
			{
				postOrder(i);
			}
		}

		// Step 2: reverse the graph
		vector<Node> reversedGraphAdjList = reverseGraph();

		// Step 3: reverse post-order on reversed graph
		int componentNum = 0;
		// process nodes in reverse
		for (int i = postOrderVector.size() - 1; i >= 0; i--)
		{
			int nodeIndex = postOrderVector[i];
			// single-reachability in other way
			if (assignedComponents[nodeIndex] == -1)
			{
				assignComponentInReversed(nodeIndex, componentNum, reversedGraphAdjList);
			}
		}

		// display results
		for (int i = 0; i < numberOfNodes; i++)
		{
			cout << "Node " << i << " is in the component " << assignedComponents[i] << endl;
		}
	}

	void printAdjacencyList()
	{
		for (int i = 0; i < numberOfNodes; i++)
		{
			cout << "Node " << i << ": ";
			vector<int> neighbours = adjacencyList[i].neighbours;
			for (int neighbour : neighbours)
			{
				cout << neighbour << " ";
			}
			cout << endl;
		}
	}
};

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
