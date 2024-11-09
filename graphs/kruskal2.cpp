#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class DisjointSet
{
private:
    vector<int> setIndex;

public:
    DisjointSet(int numberOfElements) : setIndex(numberOfElements, -1) {}
    int findSet(int elementLabel)
    {
        if (setIndex[elementLabel] < 0)
            return elementLabel;
        else
        {
            setIndex[elementLabel] = findSet(setIndex[elementLabel]);
            return setIndex[elementLabel];
        }
    }
    void setUnion(int firstElement, int secondElement);
};

void DisjointSet::setUnion(int elementA, int elementB)
{
    int setOfA = findSet(elementA);
    int setOfB = findSet(elementB);
    if (setOfA != setOfB)
    {
        if (setIndex[setOfA] < setIndex[setOfB])
        {
            setIndex[setOfA] += setIndex[setOfB];
            setIndex[setOfB] = setOfA;
        }
        else
        {
            setIndex[setOfB] += setIndex[setOfA];
            setIndex[setOfA] = setOfB;
        }
    }
}

struct Node
{
    int label;
    bool known;
    vector<double> weight;
    vector<int> neighbours;
    Node(int l = -1) : label(l), known(false) {}
};

struct Edge
{
    int from, to;
    double weight;
    Edge(int f = -1, int t = -1, double w = -1) : from(f), to(t), weight(w) {}

    // default is max-heap, correct comparator for min-heap
    bool operator<(const Edge &rhs) const
    {
        return weight > rhs.weight;
    }
};

void printEdge(int i, int j, double w)
{
    cout << "(" << i << "," << j << "," << w << ")"<<endl;
}

class Graph
{
private:
    int numberOfNodes;
    vector<Node> adjacencyList;
    priority_queue<Edge> edges;

public:
    Graph(int n) : numberOfNodes(n)
    {
        adjacencyList.resize(n);
    }

    void addEdge(int start, int dest, double weight)
    {
        adjacencyList[start].neighbours.push_back(dest);
        edges.push(Edge(start, dest, weight));
    }

    vector<Edge> kruskal(); // mst
};

vector<Edge> Graph::kruskal()
{
    DisjointSet subgraphs(numberOfNodes);
    vector<Edge> mst;

    Edge currentEdge = edges.top();
    edges.pop();
    int endNode = currentEdge.to;
    int startNode = currentEdge.from;
    mst.push_back(currentEdge);
    subgraphs.setUnion(endNode, startNode);

    while (!edges.empty() && mst.size() < numberOfNodes - 1)
    {
        // take the lightest edge
        Edge currentEdge = edges.top();
        edges.pop();

        int endNode = currentEdge.to;
        int startNode = currentEdge.from;

        if (subgraphs.findSet(startNode) != subgraphs.findSet(endNode))
        {
            subgraphs.setUnion(startNode, endNode);
            mst.push_back(currentEdge);
        }
    }
    return mst;
}

int main()
{
    int n(4);
    Graph graph(n);
    graph.addEdge(0, 3, 5);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(2, 3, 4);
    graph.addEdge(1, 3, 15);

    vector<Edge> mst = graph.kruskal();

    for (const Edge &e : mst)
        printEdge(e.from, e.to, e.weight);

    return 0;
}
