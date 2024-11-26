// https://codeforces.com/problemset/problem/28/B

#include <iostream>
#include <vector>
using namespace std;

/*
Initially each cell array contains a number which is equal to it's ordinal number (starting from 1). Also each cell determined it's favourite number. On it's move i-th cell can exchange it's value with the value of some other j-th cell, if |i - j| = di, where di is a favourite number of i-th cell. Cells make moves in any order, the number of moves is unlimited.
*/

/*
We have a directed graph where nodes are cells:

There is an edge from node i to node j if i + fav[i] = j or i - fav[i] = j.
There is an edge from node j to node i if j + fav[j] = i or j - fav[j] = i.

if i+fav[i]>length then return (i+fav[i])-length
if i-fav[i]<0 then return length-(fav[i]-i)

-- determine reachability on this graph from label init[node] to label permutation[node]
for example, if we can get 5 in the position of 1 at the end, that means we have a directed path (maybe via other nodes) from init[0]=1 to perm[0]=5.

If each perm[i] is reachable from init[i] (use dfs) then the answer is YES.
*/

void DFS(int node, vector<bool> &visited, const vector<vector<int>> &adjList)
{
    visited[node] = true;
    vector<int> neighbours = adjList[node];
    for (int n : neighbours)
    {
        if (!visited[n])
            DFS(n, visited, adjList);
    }
}

bool firstReachableFromSecond(int dest, int start, const vector<vector<int>> &adjList)
{
    // dfs traversal
    vector<bool> visited(adjList.size(), false);
    DFS(start, visited, adjList); // populates the visited vector

    if (visited[dest])
        return true;
    else
        return false;
}

bool permutationReachable(const vector<int> &init, const vector<int> &perm, const vector<int> &fav)
{
    int numCells = init.size();
    vector<vector<int>> adjList(numCells);
    // add neighbours to adjacency list (directed edges) using fav

    for (int i = 0; i < numCells; i++)
    {
        // add two directed edges...
        cout<<"...Index "<<i<<endl;
        cout<<"fav[i]: "<<fav[i]<<endl;

        // moving forward
        if (i + fav[i] < numCells)
        {
            adjList[i].push_back(i + fav[i]);
        }
        else
        {
            adjList[i].push_back((i + fav[i]) - numCells);
            cout<<"Pushed: "<< (i + fav[i]) - numCells<<endl;
        }

        // moving backward
        if (i - fav[i] >= 0)
        {

            adjList[i].push_back(i - fav[i]);
        }
        else
        {

            adjList[i].push_back(numCells - (fav[i] - i));
            cout<<"Pushed: "<< numCells - (fav[i] - i)<<endl;
        }
    }

    // we have a directed binary tree now

    // for all permutation cells check if they are reachable from
    // the same index starting from initial cells
    for (int i = 0; i < numCells; i++)
    {
        bool isReachable = firstReachableFromSecond(perm[i], init[i], adjList);
        if (!isReachable)
            return false;
    }

    // all perm[i] are reachable...
    return true;
}

int main()
{
    int numCells;
    cout << "Enter numCells: " << endl;
    cin >> numCells;

    vector<int> initArray(numCells);
    for (int i = 0; i < numCells; i++)
        initArray[i] = i;

    vector<int> permutation(numCells);
    cout << "Enter permutation: " << endl;
    for (int i = 0; i < numCells; i++)
    {
        cin >> permutation[i];
        permutation[i]--;
    }

    vector<int> favNums(numCells);
    cout << "Enter favNums: " << endl;
    for (int i = 0; i < numCells; i++)
        cin >> favNums[i];

    bool result = permutationReachable(initArray, permutation, favNums);
    if (result == true)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}

/*
5
5 4 3 2 1
1 1 1 1 1
-- YES

7
4 3 5 1 2 7 6
4 6 6 1 6 6 1
-- NO

7
4 2 5 1 3 7 6
4 6 6 1 6 6 1
-- YES

*/