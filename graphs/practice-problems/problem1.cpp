/*
 Dat je put, odrediti je li taj put pripada grafu (jesu li svaka dva susjedna povezana).
 Implementirati graf sa matricom susjedstva i tu rijesiti zadatak
*/

#include <iostream>
#include <vector>
using namespace std;

class Graph
{
    int numNodes;

public:
    vector<vector<int>> adjMat;
    Graph(int n) : numNodes(n)
    {
        adjMat.resize(n, vector<int>(n));
    }
    void setAdjMat(vector<vector<int>> newMat)
    {
        for (int i = 0; i < numNodes; i++)
            for (int j = 0; j < numNodes; j++)
                adjMat[i][j] = newMat[i][j];
    }
};

bool belongsToGraph(const vector<int> &path, const Graph &graph)
{
    // for each node in the path check whether it has an edge to its right node
    int i=0;
    while (i<path.size()-1)
    {
        // we don't have to check for the last node
        int currentNode = path[i];

        int neighbourRight = path[i + 1];
        // check the adjMat if those two are neighbours in our graph
        int weight = graph.adjMat[currentNode][neighbourRight];
        if (weight == 0){
            // not connected
            return false;
        }
        i++;
    }
    return true;
};

int main()
{
    Graph g(6);
    vector<vector<int>> matrix =
        {
            {0, 0, 0, 0, 0, 0}, // 0
            {1, 0, 0, 0, 0, 0}, // 1
            {0, 0, 0, 0, 0, 1}, // 2
            {0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 1, 0, 0, 0}, // 4
            {0, 1, 0, 0, 0, 0}}; // 5
    g.setAdjMat(matrix);
    vector<int> path = {4, 2, 5, 1, 0};
    bool result = belongsToGraph(path, g);
    if(result==1){
        cout<<"Legal path."<<endl;
    } else {
        cout<<"Illegal path."<<endl;
    }

    Graph g1(6);
    vector<vector<int>> matrix1 =
        {
            {0, 0, 0, 0, 0, 1}, // 0
            {0, 0, 0, 0, 0, 1}, // 1
            {0, 0, 0, 0, 0, 0}, // 2
            {0, 0, 1, 0, 0, 0}, // 3
            {0, 0, 0, 1, 0, 0}, // 4
            {0, 0, 0, 0, 0, 0}}; // 5
    g1.setAdjMat(matrix1);
    vector<int> path1 = {0,5};
    bool result1 = belongsToGraph(path1, g1);
    if(result1==1){
        cout<<"Legal path."<<endl;
    } else {
        cout<<"Illegal path."<<endl;
    }

    return 0;
}