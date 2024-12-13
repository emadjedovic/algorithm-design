// spoj.com/problems/BYTESM2/
/*
compute the maximum possible number of philosopher’s stones Harry can grab
in one single trip from the first row to the last row...

He starts by choosing any tile in the first row, and collects the philosopher’s stones on that tile. Then, he moves to a tile in the next row, collects the philosopher’s stones on the tile, and so on until he reaches the last row.
When he moves from one tile to a tile in the next row, he can only move to the tile just below it or diagonally to the left or right.
*/

#include <iostream>
#include <vector>

using namespace std;

int maxStones(const vector<vector<int>> &mat, int rows, int cols)
{
    vector<vector<int>> dp(rows, vector<int>(cols));

    for (int j = 0; j < cols; j++)
        dp[0][j] = mat[0][j]; // first row

    for (int i = 1; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            int upStraight = dp[i - 1][j];
            int upLeft = -1;
            int upRight = -1;
            if (j >= 1)
                upLeft = dp[i - 1][j - 1];
            if (j <= cols - 2)
                upRight = dp[i - 1][j + 1];
            dp[i][j] = mat[i][j] + max(max(upLeft, upRight), upStraight);
        }

    int result = 0;
    for (int j = 0; j < cols; j++)
        result = max(result, dp[rows - 1][j]);

    return result;
}

int main()
{
    int rows = 6;
    int cols = 5;
    vector<vector<int>> mat(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            cin >> mat[i][j];

    cout << maxStones(mat, rows, cols) << endl;
    return 0;
}

/*
3 1 7 4 2
2 1 3 1 1
1 2 2 1 8
2 2 1 5 3
2 1 4 4 4
5 2 7 5 1

-- result 32
*/