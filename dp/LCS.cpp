/*
Given two strings, s1 and s2, the task is to find the length
of the Longest Common Subsequence. If there is no common subsequence, return 0.
*/

#include <iostream>
#include <vector>

using namespace std;

int LCS(const string &s1, const string &s2)
{
    // d[i][j] - subproblem, s1 from 1...i, s2 from 1...j
    // final solution is d[m][n]

    int m = s1.length();
    int n = s2.length();

    vector<vector<int>> d(m + 1, vector<int>(n + 1));
    // if s1[i] == s2[j] then we take that element in LCS
    // otherwise we take the max of d[i-1][j] and d[i][j-1]

    // base cases
    for (int j = 0; j <= n; j++)
        d[0][j] = 0;
    for (int i = 0; i <= m; i++)
        d[i][0] = 0;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            // adjust the index
            bool sameCharacter = s1[i - 1] == s2[j - 1];
            if (sameCharacter)
                d[i][j] = d[i - 1][j - 1] + 1;
            else
                d[i][j] = max(d[i - 1][j], d[i][j - 1]);
        }

    return d[m][n];
}

int main()
{
    string s1 = "ABC";
    string s2 = "ACD";
    // 2 AC
    cout << "Example 1: " << LCS(s1, s2) << endl;

    string s3 = "AGGTAB";
    string s4 = "GXTXAYB";
    // 4 GTAB
    cout << "Example 2: " << LCS(s3, s4) << endl;

    string s5 = "ABC";
    string s6 = "CBA";
    // 1 A, B or C
    cout << "Example 3: " << LCS(s5, s6) << endl;

    return 0;
}