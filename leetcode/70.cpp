#include <iostream>
#include <vector>
using namespace std;

// [1 1 1 0 1 0 1 1 0 1 0 1] - an array of size n
// used the step 1 or skipped the step 0
int climbStairs(int n)
{
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1; // [1]
    dp[2] = 2; // [0 1] or [1 1]

    /*
    dp[3]=3;
    [0 1 1] or [1 1 1] or [1 0 1] that is, dp[2] with 1 on the last
    position plus all the way the climb to the 1st step, then skip one and
    reach the 3rd that way

    dp[4]=dp[3]+dp[2];
    0111, 1111, 1011 and 0101,1101

    dp[5]=dp[4]+dp[3];
    etc...
    */
    for (int i = 3; i < n + 1; i++)
        dp[i] = dp[i - 1] + dp[i - 2];

    return dp[n];
}

int main()
{
    int n;
    cin >> n;
    cout << climbStairs(n);
    return 0;
}