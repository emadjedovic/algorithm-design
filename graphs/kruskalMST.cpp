#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int source, destination;
    double weight;
    Edge(int s, int d, double w) : source(s), destination(d), weight(w) {}
    void print() const
    {
        cout << "edge (" << source << "," << destination << ") with weight " << weight << endl;
    }
};

bool compareEdges(const Edge &a, const Edge &b)
{
    return a.weight < b.weight;
}

class Graph
{
private:
    int numberOfNodes;
    vector<Edge> edgeList;
    vector<int> parents;
    vector<int> heights;

public:
    Graph(int n) : numberOfNodes(n)
    {
        parents.resize(n);
        for (int i = 0; i < n; i++)
            parents[i] = i;
        heights.resize(n, 0);
    }
    void addEdge(int source, int dest, double weight)
    {
        edgeList.push_back(Edge(source, dest, weight));
    }

    // path compression
    int findSet(int x)
    {
        if (parents[x] != x)
            parents[x] = findSet(parents[x]);
        return parents[x];
    }

    // union
    bool unionSet(int x, int y)
    {
        int rootX = findSet(x);
        cout << "first node's parent: " << rootX << endl;
        int rootY = findSet(y);
        cout << "second node's parent: " << rootY << endl;

        // not in the same tree unite
        if (rootX != rootY)
        {
            if (heights[rootX] > heights[rootY])
            {
                parents[rootY] = rootX;
            }
            else if (heights[rootY] > heights[rootX])
            {
                parents[rootX] = rootY;
            }
            else
            {
                parents[rootY] = rootX;
                heights[rootX]++;
            }
            return true;
        }

        // not united
        return false;
    }

    /*
    The "find" function is essential for determining whether two nodes are
    in the same connected component. This helps build a MST without creating cycles.

    The worst-case time complexity of a series of find and union operations
    can be O(n) per operation if the trees are unbalanced.

    Using height reduces the height of trees, leading to almost constant time per
    operation, specifically O(α(n)), where α is the inverse Ackermann function.
    */
    double kruskal()
    {
        // sort edges
        sort(edgeList.begin(), edgeList.end(), compareEdges);

        double mstWeight = 0;
        vector<Edge> mstEdges;

        // iterate through sorted edges and select ones for mst
        for (const Edge &edge : edgeList)
        {
            // false if in the same tree (avoiding cycles)
            if (unionSet(edge.source, edge.destination))
            {
                mstEdges.push_back(edge);
                mstWeight += edge.weight;
                cout << "Added to MST: ";
                edge.print();

                if (mstEdges.size() == numberOfNodes - 1)
                    break;
            }
        }

        if (mstEdges.size() != numberOfNodes - 1)
        {
            cout << "Error, not V-1 edges in result...\n";
            return -1;
        }

        return mstWeight;
    }
};

int main()
{
    /*
    int numberOfNodes;
    cout << "Input number of nodes: ";
    cin >> numberOfNodes;
    */
    Graph graph(4);

    // source, destination, weight
    graph.addEdge(0, 1, 10);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 40);
    graph.addEdge(2, 0, 6);
    graph.addEdge(0, 3, 5);

    double totalWeight = graph.kruskal();
    if (totalWeight == -1)
    {
        cout << "Error..." << endl;
    }
    else
    {
        cout << "Total weight of MST: " << totalWeight << endl;
    }

    return 0;
}