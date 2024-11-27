/*
calculate the number of cycles of length 4 in the graph

detection of cycles - via dfs - efficiency v^4, need a better way

for a pair of nodes to be a part of a cycle of length 4 we need them to share two neighbours

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

        vector<int> neighboursI = adjList[i];
        // for each neighbour of the first node we check as connected in a seperate vector
        vector<bool> connectedWithI(numNodes, false);
        for (int n : neighboursI)
            connectedWithI[n] = true;
        // we need to make sure we process each pair only once (to avoid duplicating the result)
        for (int j = i + 1; j < numNodes; j++)
        {
            int commonNeighbours = 0;
            vector<int> neighboursJ = adjList[j];
            // for each neighbour of the second node we check whether it's also connected to the first node
            // two nodes might be included in more than 1 quadrilateral
            // 2 common neighbours - 1 q
            // 3 common neighbours - 2 q
            // 4 common neighbours - 3 q
            // 5 common neighbours - 4 q
            // keeps increasing by 1
            for (int n : neighboursJ)
            {
                if (connectedWithI[n])
                    commonNeighbours++;
            }
            if(commonNeighbours<2) continue;

            // we can form one quadrilaters by choosing two common neighbours
            // increase the result by the number of different choices of two... "n choose 2 " = n*(n-1)/2

            result += commonNeighbours * (commonNeighbours - 1) / 2;
        }
    }
    return result/2;
}

int main()
{
    vector<vector<int>> exampleGraph = {
        {1, 2},
        {0, 3, 4},
        {0, 3},
        {1, 2,5},
        {1, 5},
        {3, 4}
    };

    int cycles4 = numberOfQuad(exampleGraph);
    cout << cycles4 << endl;

    return 0;
}