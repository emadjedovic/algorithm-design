#include <iostream>
#include <vector>
#include <string>
#include <cassert>

int minPalPartition(const std::string& s) {
    int n = s.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 100000));
    std::vector<std::vector<bool>> isPal(n, std::vector<bool>(n, false));

    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
        isPal[i][i] = true;
    }

    for (int currentSubstringLen = 2; currentSubstringLen <= n; currentSubstringLen++) {
        for (int i = 0; i < n - currentSubstringLen + 1; i++) {
            int j = i + currentSubstringLen - 1;

            if (currentSubstringLen == 2) {
                isPal[i][j] = (s[i] == s[j]);
            } else {
                isPal[i][j] = (s[i] == s[j]) && isPal[i + 1][j - 1];
            }

            if (isPal[i][j]) {
                dp[i][j] = 0;
            } else {
                for (int k = i; k <= j - 1; k++) {
                    dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k + 1][j] + 1);
                }
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    std::vector<std::string> testCases = {
        "a",        // Already a palindrome, 0 partitions
        "aa",       // Already a palindrome, 0 partitions
        "ab",       // Needs 1 partition: "a" | "b"
        "aab",      // Needs 1 partition: "aa" | "b"
        "abc",      // Needs 2 partitions: "a" | "b" | "c"
        "abba",     // Already a palindrome, 0 partitions
        "aabb",     // Needs 1 partition: "aa" | "bb"
        "racecar",  // Already a palindrome, 0 partitions
        "abcbm",    // Needs 2 partitions: "a" | "bcb" | "m"
        "banana"    // Needs 1 partition: "b" | "anana"
    };

    for (const auto& test : testCases) {
        std::cout << "minPalPartition(\"" << test << "\") = " << minPalPartition(test) << std::endl;
    }

    return 0;
}
