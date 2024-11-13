#include <iostream>
#include <vector>

using namespace std;

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
    vector<Edge> edgeList;
    vector<double> distancesBF;
    bool isDirected;

public:
    Graph(int n, int d) : numNodes(n), isDirected(d)
    {
        distancesBF.resize(numNodes, INT32_MAX);
    }

    void addEdge(int from, int to, double weight)
    {
        edgeList.push_back(Edge(from, to, weight));
        if(!isDirected){
            edgeList.push_back(Edge(to, from, weight));
        }
    }

    // weighted graph with possible negative weights
    bool BellmanFord(int start)
    {
        distancesBF[start] = 0;
        for (int i = 0; i < numNodes; i++)
            for (const Edge &e : edgeList)
                // relaxation of every edge
                if (distancesBF[e.from] + e.weight < distancesBF[e.to])
                    distancesBF[e.to] = distancesBF[e.from] + e.weight;

        // further relaxation shouldn't be possible
        // this final pass detects negative-weight cycles
        for (const Edge &e : edgeList)
            if (distancesBF[e.from] + e.weight < distancesBF[e.to])
                return false;

        return true;
    }

    void printDistances() const
    {
        cout << "Distances from start node:" << endl;
        for (int i = 0; i < numNodes; i++)
        {
            if (distancesBF[i] == INT32_MAX)
                cout << "Node " << i << ": Unreachable" << endl;
            else
                cout << "Node " << i << ": " << distancesBF[i] << endl;
        }
    }
};

int main()
{
    Graph g(6, true);

    g.addEdge(4, 5, 20);
    g.addEdge(4, 3, 10);
    g.addEdge(3, 1, 50);
    g.addEdge(3, 2, 10);
    g.addEdge(5, 1, 20);
    g.addEdge(5, 2, 33);
    g.addEdge(1, 2, -20);
    g.addEdge(2, 0, 1);
    g.addEdge(1, 0, -2);

    if (g.BellmanFord(4))
    {
        cout << "No negative-weight cycle detected." << endl;
        g.printDistances();
    }
    else
    {
        cout << "Negative-weight cycle detected!" << endl;
    }

    return 0;
}
