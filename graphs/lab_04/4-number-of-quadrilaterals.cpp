/*
calculate the number of cycles of length 4 in the graph

detection of cycles - via dfs - efficiency v^4, need a better way

for a pair of nodes to be a part of a cycle of length 4 we need them to share two neighbours

from all common neighbours choose 2 to form a cycle
*/

#include <iostream>
#include <vector>

using namespace std;

int numberOfQuad(const vector<vector<int>> &adjList)
{
    int result = 0;
    int numNodes = adjList.size();

    for (int i = 0; i < numNodes; i++)
    {
        vector<int> neighbours = adjList[i];
        vector<bool> neighboursBool(numNodes, false);

        for (int n : neighbours)
            neighboursBool[n] = true;

        // avoid double-processing the same node pair
        for (int j = i + 1; j < numNodes; j++)
        {
            int common = 0;
            // for each neighbour of the second node we check whether it's also connected to the first node
            // two nodes might be included in more than 1 quadrilateral
            // 2 common neighbours - 1 q
            // 3 common neighbours - 2 q
            // 4 common neighbours - 3 q
            // 5 common neighbours - 4 q
            // keeps increasing by 1
            for (int n : adjList[j])
                if (neighboursBool[n])
                    common++;

            // "n choose 2 " = n*(n-1)/2
            if (common >= 2)
                result += common * (common - 1) / 2;
        }
    }

    return result / 2;
}

int main()
{
    vector<vector<int>> exampleGraph = {
        {1, 2},
        {0, 3, 4},
        {0, 3},
        {1, 2, 5},
        {1, 5},
        {3, 4}};

    int cycles4 = numberOfQuad(exampleGraph);
    cout << cycles4 << endl;

    return 0;
}