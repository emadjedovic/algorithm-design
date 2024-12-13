/*
A subsequence is palindromic if it is the same whether read left to right or right to left.
Devise an algorithm that takes a sequence and returns the longest palindromic subsequence.
(not the same as substring)
*/

#include <iostream>
#include <vector>

using namespace std;

int LPS(const string &s)
{
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n));

    // lets consider substrings ai...aj
    for (int i = 0; i < n; i++)
        dp[i][i] = 1; // diagonally

    // ensuring that smaller substrings are processed before larger substrings
    for (int i = n - 2; i >= 0; i--)
    {                  // Start from second-to-last row
        int j = i + 1; // start one step ahead
        while (j < n)
        {
            // until the end of string
            if (s[i] == s[j])
            {
                if (j - i == 1)
                    dp[i][j] = 2;
                else
                    dp[i][j] = dp[i + 1][j - 1] + 2; // Extend the palindrome
            }
            else
            {
                // either exclude i or j
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]); // Take the max of excluding i or j
            }
            j++;
        }
    }

    return dp[0][n - 1];
}

int main()
{
    string S1 = "BBABCBCAB";
    cout << LPS(S1) << endl; // 7
    string S2 = "ACGTGTCAAAATCG";
    cout << LPS(S2) << endl; // 8
    return 0;
}