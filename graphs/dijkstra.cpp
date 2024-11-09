#include <iostream>
#include <vector>
#include <cfloat> // For DBL_MAX
using namespace std;

struct Node
{
    int label;
    bool known;
    double distance;
    vector<int> neighbours;
    vector<double> weights; // to neighbours
    int previous;

    Node(int l = -1) : label(l), known(false), distance(DBL_MAX), previous(-1) {}
};

class Graph
{
private:
    vector<Node> adjacencyList;
    int numNodes;

public:
    Graph() : numNodes(0) {}

    void addNode(Node v)
    {
        adjacencyList.push_back(v);
        numNodes++;
    }
    void printPathTo(int destination);
    int getSmallestDistanceIndex();
    void dijkstra(int start);
};

void Graph::printPathTo(int destination)
{
    if (adjacencyList[destination].previous != -1)
    {
        printPathTo(adjacencyList[destination].previous);
        cout << "-";
    }
    cout << destination;
}

int Graph::getSmallestDistanceIndex()
{
    int minIndex = -1;
    for (int i = 0; i < numNodes; i++)
    {
        if (adjacencyList[i].distance != DBL_MAX && !adjacencyList[i].known &&
            (minIndex < 0 || adjacencyList[i].distance < adjacencyList[minIndex].distance))
            minIndex = i;
    }
    return minIndex;
}

void Graph::dijkstra(int start)
{
    adjacencyList[start].distance = 0;
    for (int i = 0; i < numNodes; i++)
    {
        int smallestIndex = getSmallestDistanceIndex();
        if (smallestIndex == -1)
            break;

        adjacencyList[smallestIndex].known = true;
        vector<int> neighbours = adjacencyList[smallestIndex].neighbours;
        for (size_t j = 0; j < neighbours.size(); j++)
        {
            int neighbour = neighbours[j];
            if (!adjacencyList[neighbour].known)
            {
                double edgeWeight = adjacencyList[smallestIndex].weights[j];
                double currentNodeDistance = adjacencyList[smallestIndex].distance;

                if (adjacencyList[neighbour].distance == DBL_MAX ||
                    currentNodeDistance + edgeWeight < adjacencyList[neighbour].distance)
                {
                    adjacencyList[neighbour].distance = currentNodeDistance + edgeWeight;
                    adjacencyList[neighbour].previous = smallestIndex;
                }
            }
        }
    }
}

int main()
{
    int numNodes;
    cout << "Enter a number of nodes: ";
    cin >> numNodes;

    Graph g;

    for (int i = 0; i < numNodes; i++)
    {
        Node newNode;
        newNode.label = i;
        int outDegree;
        cout << "Enter out-degree: ";
        cin >> outDegree;
        for (int j = 0; j < outDegree; j++)
        {
            cout << "Add neighbour: ";
            int label;
            cin >> label;
            newNode.neighbours.push_back(label);
            cout << "Add edge weight: ";
            double weight;
            cin >> weight;
            newNode.weights.push_back(weight);
        }
        g.addNode(newNode);
    }

    int startNode;
    cout << "Dijkstra from (enter a start node): ";
    cin >> startNode;
    g.dijkstra(startNode);

    cout << "... and an end node: ";
    int endNode;
    cin >> endNode;
    g.printPathTo(endNode);
    cout << endl;

    return 0;
}
