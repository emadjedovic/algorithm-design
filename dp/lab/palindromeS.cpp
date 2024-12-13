/*
Given a string str, the task is to find the longest substring which is a palindrome.

if we know the status (i.e., palindrome or not) of the substring ranging [i, j],
we can find the status of the substring ranging [i-1, j+1] by only matching the character str[i-1] and str[j+1]

*/

#include <iostream>
#include <vector>

using namespace std;

int maxSubstring(const string &str) {
    int n = str.length();
    if (n == 0) return 0;

    vector<vector<bool>> dp(n, vector<bool>(n, false)); // dp[i][j] = true if str[i..j] is a palindrome

    int maxLength = 1; // single characters are palindromes
    for (int i = 0; i < n; i++) dp[i][i] = true; // diagonal

    // initialize for substrings of length 2
    for (int i = 0; i < n - 1; i++) {
        if (str[i] == str[i + 1]) {
            dp[i][i + 1] = true; // one step above the diagonal
            maxLength = 2;
        }
    }

    // substrings of length >= 3
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            // the main logic
            if (dp[i + 1][j - 1] && str[i] == str[j]) {
                dp[i][j] = true;
                maxLength = len;
            }
        }
    }

    return maxLength;
}

int main() {
    string S1 = "BBABCBCAB";
    cout << "Max Palindrome Length: " << maxSubstring(S1) << endl;

    string S2 = "ACGTGTCAAAATCG";
    cout << "Max Palindrome Length: " << maxSubstring(S2) << endl;

    return 0;
}
