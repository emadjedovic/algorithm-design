/*
Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
You have the following three operations permitted on a word:
1. Insert a character
2. Delete a character
3. Replace a character
*/

#include <iostream>
#include <vector>

using namespace std;

int EditDistance(const string &s1, const string &s2)
{
    int n = s1.length();
    int m = s2.length();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    // x0,x1,...,xi for s1
    // y0,y1,...,yj for s2

    for (int i = 0; i <= n; i++)
    {
        // empty s2 (remove n elements from s1)
        dp[i][0] = i;
    }
    for (int j = 0; j <= m; j++)
    {
        // empty s1 (add m elements to s1)
        dp[0][j] = j;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            // the indexes are shifted
            char s1Char = s1[i-1];
            char s2Char = s2[j-1];
            if (s1Char == s2Char)
            {
                // no operation needed, just grab the previous result
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                // the elements dont match
                // we perform the operation and add the minimum subproblem

                // insert the character to s1
                int insertCh = 1 + dp[i][j - 1];
                // delete the character from s1
                int deleteCh = 1 + dp[i - 1][j];
                // replace the character in s1 with character in s2
                int replaceCh = 1 + dp[i - 1][j - 1];
                dp[i][j] = min(min(insertCh, deleteCh), replaceCh);
            }
        }
    }

    return dp[n][m];
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

    string s7 = "horse";
    string s8 = "ros";
    cout << EditDistance(s7, s8) << endl; // 3

    string s9 = "intention";
    string s10 = "execution";
    cout << EditDistance(s9, s10) << endl; // 5

    return 0;
}
