#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <utility>
using namespace std;

class GraphWeighted
{
    bool isDirected;
    int numNodes;
    vector<list<pair<int, double>>> adjacencyList;

public:
    GraphWeighted(int n, bool d = false) : numNodes(n), isDirected(d)
    {
        adjacencyList.resize(numNodes);
    }

    void addEdge(int start, int end, double weight);
    vector<double> DijkstraSlow(int start);
    vector<double> DijkstraFast(int start);
    pair<bool, vector<double>> BellmanFord(int start);
    pair<double, vector<pair<int, int>>> Prim();
    pair<double, vector<pair<int, int>>> Kruskal();
    double maxFlow(int start, int end);
};

class DisjointSets
{
    vector<int> parent;

public:
    DisjointSets(int numElements)
    {
        for (int i = 0; i < numElements; i++)
            parent.push_back(i);
    }

    // essential for determining whether two elements are in the same set
    // helps identify the connected component (or subgraph) the node belongs to
    // also called path compression
    int findSet(int node)
    {
        if (parent[node] == node)
            return node;
        parent[node] = findSet(parent[node]);
        return parent[node];
    }

    // linking the root of one set to the root of another set, effectively connecting the two sets
    // connects two previously disconnected components of a graph by adding an edge between them
    void unionSets(int node1, int node2)
    {
        int root1 = findSet(node1);
        int root2 = findSet(node2);
        if (root1 != root2)
        {
            parent[root2] = root1; // Merge two sets by connecting their roots
        }
    }
};

void GraphWeighted::addEdge(int start, int end, double weight)
{
    adjacencyList[start].push_back({end, weight});
    if (!isDirected)
        adjacencyList[end].push_back({start, weight});
}

pair<bool, vector<double>> GraphWeighted::BellmanFord(int start)
{
    // all infinite distances
    vector<double> distances(numNodes, INT32_MAX);
    distances[start] = 0;

    int numEdges = numNodes - 1;
    // edge relaxation
    for (int i = 0; i < numEdges; i++)
    {
        for (int j = 0; j < numNodes; j++)
        {
            for (auto neighbour : adjacencyList[j])
            {
                if (distances[neighbour.first] > distances[j] + neighbour.second)
                {
                    distances[neighbour.first] = distances[j] + neighbour.second;
                }
            }
        }
    }

    for (int i = 0; i < numNodes; i++)
    {
        for (auto neighbour : adjacencyList[i])
        {
            if (distances[neighbour.first] > distances[i] + neighbour.second)
            {
                // relaxation failed
                return {false, distances};
            }
        }
    }

    return {true, distances};
}

vector<double> GraphWeighted::DijkstraSlow(int start)
{
    vector<bool> done(numNodes, false);
    vector<double> distances(numNodes, INT32_MAX);
    done[start] = true;
    distances[start] = 0;
    int current = start;

    int numEdges = numNodes - 1;
    for (int i = 0; i < numEdges; i++)
    {
        for (auto neighbour : adjacencyList[i])
        {
            // edge relaxation
            if (!done[neighbour.first] && distances[current] + neighbour.second < distances[neighbour.first])
            {
                distances[neighbour.first] = distances[current] + neighbour.second;
            }
        }

        pair<double, int> minimum = {INT32_MAX, -1};
        for (int j = 0; j < numNodes; j++)
        {
            if (!done[j] && distances[j] < minimum.first)
                minimum = {distances[j], j};
        }

        current = minimum.second;
        done[current] = true;
    }

    return distances;
}

vector<double> GraphWeighted::DijkstraFast(int start)
{
    vector<bool> done(numNodes, false);
    vector<double> distances(numNodes, INT32_MAX);
    done[start] = true;
    distances[start] = 0;
    int current = start;
    set<pair<double, int>> tree;

    int numEdges = numNodes - 1;
    for (int i = 0; i < numEdges; i++)
    {
        for (auto neighbour : adjacencyList[current])
        {
            if (!done[neighbour.first] && distances[current] + neighbour.second < distances[neighbour.first])
            {
                if (tree.find({distances[neighbour.first], neighbour.second}) != tree.end())
                {
                    tree.erase({distances[neighbour.first], neighbour.second});
                }

                distances[neighbour.first] = distances[current] + neighbour.second;
                tree.insert({distances[neighbour.first], neighbour.second});
            }
        }

        current = tree.begin()->second;
        tree.erase(tree.begin());
        done[current] = true;
    }
    return distances;
}

pair<double, vector<pair<int, int>>> GraphWeighted::Prim()
{
    return pair<double, vector<pair<int, int>>>();
}

pair<double, vector<pair<int, int>>> GraphWeighted::Kruskal()
{
    return pair<double, vector<pair<int, int>>>();
}

int main()
{

    GraphWeighted graph1(9);
    graph1.addEdge(0, 1, 4);
    graph1.addEdge(0, 7, 8);
    graph1.addEdge(1, 7, 11);
    graph1.addEdge(7, 8, 7);
    graph1.addEdge(1, 2, 8);
    graph1.addEdge(7, 6, 1);
    graph1.addEdge(2, 8, 2);
    graph1.addEdge(8, 6, 6);
    graph1.addEdge(2, 3, 7);
    graph1.addEdge(2, 5, 4);
    graph1.addEdge(6, 5, 2);
    graph1.addEdge(3, 5, 14);
    graph1.addEdge(3, 4, 9);
    graph1.addEdge(5, 4, 10);

    vector<double> shortestDistancesFrom = graph1.DijkstraSlow(0);
    for (double i : shortestDistancesFrom)
        cout << i << " ";
    cout << endl;

    shortestDistancesFrom = graph1.DijkstraFast(0);
    for (double i : shortestDistancesFrom)
        cout << i << " ";
    cout << endl;

    GraphWeighted graph2(6, true);
    graph2.addEdge(0, 1, 16);
    graph2.addEdge(1, 2, 12);
    graph2.addEdge(2, 5, 20);
    graph2.addEdge(0, 3, 13);
    graph2.addEdge(3, 4, 14);
    graph2.addEdge(4, 5, 4);
    graph2.addEdge(4, 2, 7);
    graph2.addEdge(3, 1, 4);
    graph2.addEdge(2, 3, 9);
    cout << graph2.maxFlow(0, 5);

    return 0;
}