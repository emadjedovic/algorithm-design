#include <iostream>
#include <vector>
using namespace std;

// true if the first player loses the game
bool divisorGame(int n)
{
    vector<bool> dp(n + 1);
    dp[0] = false;
    dp[1] = false;
    dp[2] = true; // bob has no legal moves left

    // dp[3]=not dp[3-divisor] (because bob plays the dp[3-divisor])
    for (int i = 3; i <= n; i++)
    {
        dp[i] = false; // lose by default
        // traverse through divisors
        for (int x = 1; x * x <= i; x++)
        {
            if (i % x != 0)
                continue;
            bool win = !dp[i - x]; // the other player loses
            if (win)
            {
                dp[i] = true;
                break; // choosing this x is sufficient to continue the game
            }
        }
    }

    return dp[n];
}

int main()
{
    int n;
    cin >> n;
    cout << divisorGame(n);
    return 0;
}