/*
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Each "island" is a connected component of adjacent '1's, where adjacency is defined as either horizontally or vertically neighboring cells.

*/

#include <iostream>
#include <vector>
using namespace std;

void DFS(vector<vector<char>> &grid, int row, int col)
{
    // do dfs recursively on 1's
    int numRows = grid.size();
    int numCols = grid[0].size();

    if (row >= numRows || col >= numCols || row < 0 || col < 0 || grid[row][col] == '0')
        return;

    // legit '1' (on the island)
    // instead of keeping a vector of visited nodes, just mark '1' as '0'
    grid[row][col] = '0';

    // explore neighbours
    DFS(grid, row - 1, col);
    DFS(grid, row + 1, col);
    DFS(grid, row, col - 1);
    DFS(grid, row, col + 1);
}

int numIslands(const vector<vector<char>> &grid)
{
    // copy because we change 1's to 0's as we traverse
    vector<vector<char>> gridCopy = grid;
    int componentCounter = 0;
    int numRows = grid.size();
    int numCols = grid[0].size();

    for (int i = 0; i < numRows; i++)
        for (int j = 0; j < numCols; j++)
            if (gridCopy[i][j] == '1')
            {
                componentCounter++;
                DFS(gridCopy, i, j);
                // dfs ends when the component ends
                // it changed appropriate fields from '1' to '0'
            }

    return componentCounter;
}

int main()
{
    vector<vector<char>> grid = {
        {'1', '1', '0', '1', '1'},
        {'1', '1', '0', '0', '1'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}};

    cout << "Number of islands: " << numIslands(grid) << endl;
    return 0;
}
