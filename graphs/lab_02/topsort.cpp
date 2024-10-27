#include <iostream>
#include <vector>
#include <set>
#include <limits>
using namespace std;

vector<int> topologicalSort(vector<vector<int>> adjList)
{
    int numberOfNodes = adjList.size();
    vector<int> result;

    vector<int> indegrees(numberOfNodes, 0);
    // for each node go through its neighbours
    for (vector<int> node : adjList)
    {
        // increment each neighbour's indegree
        for (int neighbour : node)
            indegrees[neighbour]++;
    }

    set<int> zeroIndegreeNodes;
    for (int i = 0; i < numberOfNodes; i++)
    {
        if (indegrees[i] == 0)
            zeroIndegreeNodes.insert(i);
    }

    // push nodes with indegree of 0 to result...
    while (!zeroIndegreeNodes.empty())
    {
        int nodeToAdd = *zeroIndegreeNodes.begin();
        result.push_back(nodeToAdd);
        zeroIndegreeNodes.erase(nodeToAdd);
        // decrease indegree of its neighbours
        for (int neighbour : adjList[nodeToAdd])
        {
            indegrees[neighbour]--;
            if (indegrees[neighbour] == 0)
                zeroIndegreeNodes.insert(neighbour);
        }
    }

    if (result.size() != numberOfNodes)
    {
        // did not reach all nodes
        cout << "Topological sort not possible." << endl;
    }
    return result;
}

void adjListFromWeighted(const vector<vector<pair<int, double>>> &adjListWeighted, vector<vector<int>> &result)
{

    result.resize(adjListWeighted.size());
    for (size_t i = 0; i < adjListWeighted.size(); i++)
    {
        vector<pair<int, double>> neighbours = adjListWeighted[i];
        for (const pair<int, double> &neighbour : neighbours)
        {
            result[i].push_back(neighbour.first);
        }
    }
}

// very large number
double M = numeric_limits<double>::max();

vector<double> distanceFrom(int node, const vector<vector<pair<int, double>>> &adjListWeighted)
{

    int numberOfNodes = adjListWeighted.size();
    vector<double> distances(numberOfNodes, M);
    distances[node] = 0; // start node

    vector<vector<int>> adjListUnweighted;
    adjListFromWeighted(adjListWeighted, adjListUnweighted);

    // slice this vector so it starts from int node...
    vector<int> topOrderAll = topologicalSort(adjListUnweighted);
    int startIndex = -1;
    for (size_t i = 0; i < topOrderAll.size(); i++)
    {
        if (topOrderAll[i] == node)
        {
            startIndex = i;
            break;
        }
    }
    vector<int> topOrder;
    for (size_t i = startIndex; i < topOrderAll.size(); i++)
        topOrder.push_back(topOrderAll[i]);

    for (int currentNode : topOrder)
    {
        // visit neighbours - distance 1 from currentNode
        vector<pair<int, double>> neighbours = adjListWeighted[currentNode];
        for (pair<int, double> neighbour : neighbours)
        {
            distances[neighbour.first] = distances[currentNode] + neighbour.second;
        }
    }
    return distances;
}

int main()
{
    vector<vector<int>> testingTopSort({{5, 4}, {8}, {}, {7, 1}, {2, 3}, {6}, {}, {}, {}});
    vector<int> result1 = topologicalSort(testingTopSort);
    cout << "Testing topological sort...\n";
    for (int node : result1)
        cout << node << " ";
    cout << endl;

    vector<vector<pair<int, double>>> weightedGraph{
        {make_pair(4, 0.5),
         make_pair(5, 1.5)},
        {},
        {},
        {
            make_pair(1, 2),
        },
        {make_pair(2, 1.5),
         make_pair(3, 0.5)},
        {
            make_pair(6, 1.6),
        },
        {}};

    vector<double> result2 = distanceFrom(4, weightedGraph);
    cout << "Testing shortest distance with weights...\n";
    cout<< "Printing distances from node 4:\n";
    for (double d : result2)
        cout << d <<endl;

    cout << endl;

    return 0;
}
