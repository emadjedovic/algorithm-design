#include <iostream>
#include <vector>
#include <set>
#include <limits> // For numeric limits
using namespace std;

struct Edge {
    int to;
    double weight;
    Edge(int to, double weight) : to(to), weight(weight) {}
};

// Performs a topological sort on a directed acyclic graph (DAG).
vector<int> topologicalSort(const vector<vector<Edge>>& graph) {
    int numNodes = graph.size();
    vector<int> inDegrees(numNodes, 0);

    // Calculate the indegree for each node.
    for (int i = 0; i < numNodes; i++) {
        for (const Edge& edge : graph[i]) {
            inDegrees[edge.to]++;
        }
    }

    // Add nodes with zero indegree to a set (sorted order maintained).
    set<int> zeroInDegreeNodes;
    for (int i = 0; i < numNodes; i++) {
        if (inDegrees[i] == 0) {
            zeroInDegreeNodes.insert(i);
        }
    }

    // Perform topological sort.
    vector<int> sortedOrder;
    while (!zeroInDegreeNodes.empty()) {
        int currentNode = *zeroInDegreeNodes.begin();
        zeroInDegreeNodes.erase(currentNode);
        sortedOrder.push_back(currentNode);

        // Decrease indegree of neighbors and check for new zero-indegree nodes.
        for (const Edge& edge : graph[currentNode]) {
            inDegrees[edge.to]--;
            if (inDegrees[edge.to] == 0) {
                zeroInDegreeNodes.insert(edge.to);
            }
        }
    }

    // Check for a cycle (in case the graph is not a DAG).
    if (sortedOrder.size() != numNodes) {
        cout << "Topological sort not possible (graph has a cycle)." << endl;
        return {};
    }

    return sortedOrder;
}

// Calculates the shortest distances from a given starting node in a DAG.
vector<double> shortestPathInDAG(int startNode, const vector<vector<Edge>>& graph) {
    int numNodes = graph.size();
    vector<double> distances(numNodes, numeric_limits<double>::max());
    distances[startNode] = 0;

    // Get the topological order of nodes.
    vector<int> topologicalOrder = topologicalSort(graph);

    // Find the starting position in the topological order.
    int startIndex = -1;
    for (int i = 0; i < numNodes; i++) {
        if (topologicalOrder[i] == startNode) {
            startIndex = i;
            break;
        }
    }

    // Process nodes from the starting position onwards.
    for (int i = startIndex; i < numNodes; i++) {
        int currentNode = topologicalOrder[i];
        for (const Edge& edge : graph[currentNode]) {
            if (distances[currentNode] != numeric_limits<double>::max()) {
                distances[edge.to] = min(distances[edge.to], distances[currentNode] + edge.weight);
            }
        }
    }

    return distances;
}

int main() {
    // A sample weighted directed acyclic graph (DAG).
    // Graph visualization (node -> (neighbor, weight)):
    // 0 -> (1, 2), (2, 1)
    // 1 -> (3, 3)
    // 2 -> (3, 1), (4, 6)
    // 3 -> (4, 2)
    // 4 -> {}

    vector<vector<Edge>> weightedGraph = {
        {Edge(1, 2), Edge(2, 1)}, // Node 0
        {Edge(3, 3)},             // Node 1
        {Edge(3, 1), Edge(4, 6)}, // Node 2
        {Edge(4, 2)},             // Node 3
        {}                        // Node 4
    };

    // Testing topological sort
    cout << "Testing topological sort...\n";
    vector<int> sortedOrder = topologicalSort(weightedGraph);
    for (int node : sortedOrder) {
        cout << node << " ";
    }
    cout << endl;

    // Testing shortest path in DAG
    cout << "\nTesting shortest path from node 0...\n";
    vector<double> distances = shortestPathInDAG(0, weightedGraph);
    for (int i = 0; i < distances.size(); i++) {
        if (distances[i] == numeric_limits<double>::max()) {
            cout << "Node " << i << ": No path\n";
        } else {
            cout << "Node " << i << ": " << distances[i] << endl;
        }
    }

    return 0;
}
