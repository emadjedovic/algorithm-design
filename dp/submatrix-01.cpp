/*
Given a binary matrix mat of size n*m, find the maximum length
of a side of a square sub-matrix with all 1s.
*/

#include <iostream>
#include <vector>

using namespace std;

int maxSquareDim1(const vector<vector<int>> &mat)
{
    int n = mat.size();
    int m = mat[0].size();
    // max 1-submatrix ending with element mat[i][j]
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (mat[i - 1][j - 1] == 0)
            {
                dp[i][j] = 0;
            }
            else
            {
                int leftResult = dp[i][j - 1];
                int diaResult = dp[i - 1][j - 1];
                int upResult = dp[i - 1][j];
                dp[i][j] = min(min(leftResult, diaResult), upResult) + 1;
            }
        }

    // the optimal submatrix could have an ending point at any field
    int result = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            result = max(result, dp[i][j]);

    return result;
}

int main()
{
    vector<vector<int>> mat1 = {
        {0, 1, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0}};
    cout << "Maximal square submatrix dimension: " << maxSquareDim1(mat1) << endl; // 3

    vector<vector<int>> mat2 = {{1, 1},
                                {1, 1}};
    cout << "Maximal square submatrix dimension: " << maxSquareDim1(mat2) << endl; // 2

    return 0;
}