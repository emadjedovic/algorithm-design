/*
Given an array of N positive integers, we need to return the maximum sum
of the subsequence such that no two elements of the subsequence
are adjacent elements in the array.
*/

#include <iostream>
#include <vector>

using namespace std;

int maxSumNonAdjacent(const vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return nums[0];

    vector<int> dp_picked(n);
    dp_picked[0] = nums[0];
    dp_picked[1] = nums[1];

    // dp[i] means the result up to ith element, whether we picked it or not
    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[1], nums[0]);

    for (int i = 2; i < n; i++)
    {
        dp_picked[i] = nums[i] + dp[i - 2];
        if (dp_picked[i] > dp_picked[i - 1])
        {
            dp[i] = dp_picked[i];
        }
        else
        {
            // not picking it (doenst mean we pick (i-1)-th element, though)
            dp[i] = dp[i-1];
        }
    }
    return dp[n - 1];
}

int main()
{
    vector<int> example1 = {1, 2, 4};                   // 5
    vector<int> example2 = {2, 1, 4, 9};                // 11
    vector<int> example3 = {1, 2, 3, 1, 3, 5, 8, 1, 9}; // 24
    vector<int> example4 = {5, 5, 10, 100, 10, 5};      // 110
    vector<int> example5 = {3, 2, 7, 10};               // 13
    vector<int> example6 = {3, 2, 5, 10, 7};            // 15
    vector<int> example7 = {6, 7, 1, 3, 8, 2, 4};       // 19

    cout << "Example 1: " << maxSumNonAdjacent(example1) << endl;
    cout << "Example 2: " << maxSumNonAdjacent(example2) << endl;
    cout << "Example 3: " << maxSumNonAdjacent(example3) << endl;
    cout << "Example 4: " << maxSumNonAdjacent(example4) << endl;
    cout << "Example 5: " << maxSumNonAdjacent(example5) << endl;
    cout << "Example 6: " << maxSumNonAdjacent(example6) << endl;
    cout << "Example 7: " << maxSumNonAdjacent(example7) << endl;

    return 0;
}