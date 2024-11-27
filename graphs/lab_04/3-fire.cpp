/* codeforces.com/problemset/problem/35/C

N rows with M trees each were planted. The j-th tree in the i-th row would have the coordinates of (i, j). However, the young forest caught fire. We must find the coordinates of the tree that will catch fire last.

The burning began in K points simultaneously. Every minute the fire gets from the burning trees to the ones that aren’t burning and that the distance from them to the nearest burning tree equals to 1.

Find the tree that will be the last to start burning. If there are several such trees, output any.

-- use bfs (fire spreading via layers) and keep track of distances
-- the farthest distance is our answer
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

pair<int,int> theLastOneBurning(vector<pair<int,int>> &burning_trees_init, int N, int M)
{
    pair<int,int> treeResult;
    
    // matrix of visited trees (the ones caught on fire)
    vector<vector<bool>> visited(N, vector<bool>(M, false));

    // start bfs from any burning tree
    queue<pair<int,int>> q;
    for(auto tree: burning_trees_init)
    {
        q.push(tree);
        visited[tree.first][tree.second] = true;
    }

    // the last one in this queue is the result
    while(!q.empty())
    {
        pair<int,int> currentBurningTree = q.front();
        treeResult = currentBurningTree;

        q.pop();

        // spread fire
        vector<vector<int>> moves = {
            {-1,0}, // up
            {1,0}, // down
            {0,-1}, // left
            {0,1} // right
        };
        for(int i=0; i<4; i++)
        {
            int newCol = currentBurningTree.first + moves[i][1];
            int newRow = currentBurningTree.second + moves[i][0];

            // are these coordinates legal?
            if(newCol < 0 || newCol >= M || newRow < 0 || newRow >= N || visited[newRow][newCol])
            {
                // not legal
                continue;
            }

            // contaminate the tree
            visited[newRow][newCol] = true;
            q.push(make_pair(newRow, newCol));

            // cout<<"Contaminated: "<<newRow+1<<", "<<newCol+1<<endl;
        } 
    }

    // the queue is empty - all trees are burning
    return treeResult;
}

int main()
{
    int N, M; // [1,2000]
    cout<<"Size of the forest (row and column number): ";
    cin>>N>>M;

    int K; // [1,10]
    cout<<"Amount of trees burning in the beginning: ";
    cin>>K;
    vector<pair<int,int>> burning_trees_init;
    for(int i=0; i<K; i++)
    {
        int x, y;
        cout<<"Enter burning tree: ";
        cin>>x>>y;
        burning_trees_init.push_back(make_pair(x-1,y-1));
    }
    
    pair<int,int> result = theLastOneBurning(burning_trees_init, N, M);
    cout<<"The last-burning tree is: "<<result.first+1<<" "<<result.second+1<<endl;
    
    return 0;
}