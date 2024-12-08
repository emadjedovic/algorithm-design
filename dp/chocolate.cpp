#include <iostream>
#include <vector>

using namespace std;

int MinCuts(int m, int n, vector<vector<int>> &D)
{
    if (m == n)
        return 0; // already a square
    if (D[m][n] != -1)
        return D[m][n]; // already calculated

    if (m > n)
        D[m][n] = MinCuts(m - n, n, D) + 1;
    else
        D[m][n] = MinCuts(m, n - m, D) + 1;

    return D[m][n];
}

int main()
{
    int m, n;
    cout << "Enter dimensions of the chocolate (m x n): ";
    cin >> m >> n;

    // first row and first column filled with 0s
    vector<vector<int>> D(m + 1, vector<int>(n + 1, -1));
    for (int i = 0; i <= n; i++)
        D[0][i] = 0;
    for (int i = 0; i <= m; i++)
        D[i][0] = 0;

    int result = MinCuts(m, n, D);

    cout << "Minimum number of cuts to make all pieces square: " << result << endl;

    return 0;
}