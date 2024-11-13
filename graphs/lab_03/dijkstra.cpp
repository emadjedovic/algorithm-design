#include <iostream>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

struct Node
{
    int label;
    double distance; // the current shortest distance to the node being processed

    // Invert comparison for priority queue (we want min-heap)
    bool operator<(const Node& other) const
    {
        return distance > other.distance;
    }
};

struct Edge
{
    int from, to;
    double weight;
    Edge(int f, int t, double w) : from(f), to(t), weight(w) {}
};

class Graph
{
private:
    int numNodes;
    vector<vector<Edge>> adjacencyList;
    vector<double> distancesDij;
    bool isDirected;

public:
    Graph(int n, bool d) : numNodes(n), isDirected(d)
    {
        distancesDij.resize(numNodes, numeric_limits<double>::infinity());
        adjacencyList.resize(numNodes);
    }

    void addEdge(int from, int to, double weight)
    {
        adjacencyList[from].push_back(Edge(from, to, weight));
        if (!isDirected)
        {
            adjacencyList[to].push_back(Edge(to, from, weight));
        }
    }

    void Dijkstra(int start)
    {
        distancesDij[start] = 0.0;
        priority_queue<Node> heap;
        heap.push({start, 0.0});

        while (!heap.empty())
        {
            double currentDist = heap.top().distance;
            int currentLabel = heap.top().label;
            heap.pop();

            if (distancesDij[currentLabel] < currentDist)
                continue;

            for (const Edge& e : adjacencyList[currentLabel])
            {
                if (distancesDij[currentLabel] + e.weight < distancesDij[e.to])
                {
                    distancesDij[e.to] = distancesDij[currentLabel] + e.weight;
                    heap.push({e.to, distancesDij[e.to]});
                }
            }
        }
    }

    void printDistances() const
    {
        cout << "Distances from start node:" << endl;
        for (int i = 0; i < numNodes; i++)
        {
            if (distancesDij[i] == numeric_limits<double>::infinity())
                cout << "Node " << i << ": Unreachable" << endl;
            else
                cout << "Node " << i << ": " << distancesDij[i] << endl;
        }
    }
};

int main()
{
    Graph g(7, false);

    g.addEdge(0, 1, 6);
    g.addEdge(0, 2, 9);
    g.addEdge(1, 2, 6);
    g.addEdge(1, 4, 9);
    g.addEdge(2, 3, 7);
    g.addEdge(1, 5, 6);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 2);
    g.addEdge(5, 6, 1);

    g.Dijkstra(0);

    g.printDistances();

    return 0;
}
