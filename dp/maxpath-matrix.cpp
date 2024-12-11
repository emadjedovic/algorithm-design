/*
Given an n*m matrix, find the maximum sum of elements of cells starting
from the cell (0, 0) to cell (n-1, m-1).
The allowed moves are right, downwards or diagonally right,
i.e, from location (i, j) next move can be (i+1, j), or, (i, j+1), or (i+1, j+1).
*/

#include <iostream>
#include <vector>

using namespace std;

int maxPath(const vector<vector<int>> &mat)
{
    int n = mat.size();
    int m = mat[0].size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            int left = dp[i][j - 1];
            int up = dp[i - 1][j];
            int dia = dp[i - 1][j - 1];
            dp[i][j] = max(max(left, up), dia) + mat[i - 1][j - 1];
        }

    return dp[n][m];
}

int main()
{
    vector<vector<int>> mat1 = {{100, -350, -200},
                                {-100, -300, 700}};
    cout << "maxPath: " << maxPath(mat1) << endl; // 500

    vector<vector<int>> mat2 = {{500, 100, 230},
                                {1000, 300, 100},
                                {200, 1000, 200}};
    cout << "maxPath: " << maxPath(mat2) << endl; // 3000
    return 0;
}