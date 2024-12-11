/*
Given two strings s1 and s2 of lengths m and n respectively and below operations that can be performed on s1. Find the minimum number of edits (operations) to convert ‘s1‘ into ‘s2‘.

    Insert: Insert any character before or after any index of s1
    Remove: Remove a character of s1
    Replace: Replace a character at any index of s1 with some other character.

Note: All of the above operations are of equal cost.
*/

#include <iostream>
#include <vector>

using namespace std;

int LCS(const string &s1, const string &s2)
{
    int n = s1.length();
    int m = s2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (s1[i] == s2[j])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }

    return dp[n][m];
}

int EditDistance(const string &s1, const string &s2)
{
    int remainSame = LCS(s1, s2);
    if (s2.length() > s1.length())
    {
        int toAdd = s2.length() - s1.length();
        int toReplace = s1.length() - remainSame;
        return toAdd + toReplace;
    }
    else
    {
        int toRemove = s1.length() - s2.length();
        int toReplace = s2.length() - remainSame;
        return toRemove + toReplace;
    }
}

int main()
{
    string s1 = "geek";
    string s2 = "gesek";
    cout << EditDistance(s1, s2) << endl; // 1

    string s3 = "cat";
    string s4 = "cut";
    cout << EditDistance(s3, s4) << endl; // 1

    string s5 = "sunday";
    string s6 = "saturday";
    cout << EditDistance(s5, s6) << endl; // 3

    return 0;
}