#include <iostream>
#include <vector>
using namespace std;

// climb either one or two steps
// reach the top of the floor
int minCostClimbingStairs(const vector<int> &cost)
{
    int stairNum = cost.size();
    vector<int> dp(stairNum);
    if (stairNum == 0)
        return 0;
    if (stairNum == 1)
        return 0; // skip the step
    // dp[i] is min{dp[i-1]+cost[i], dp[i-2]+cost[i]}
    // step i is included
    dp[0] = cost[0];
    dp[1] = cost[1]; // skip the first one
    for (int i = 2; i < stairNum - 1; i++)
        dp[i] = min(dp[i - 1] + cost[i], dp[i - 2] + cost[i]);
    int skipTheLast = dp[stairNum - 2];
    int skipThePrevious = dp[stairNum - 3] + cost[stairNum - 1];
    return min(skipTheLast, skipThePrevious);
}

int main()
{
    vector<int> cost = {10, 15, 20};
    cout << minCostClimbingStairs(cost);
    cout << endl;
    vector<int> cost2 = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    cout << minCostClimbingStairs(cost2);
    return 0;
}