/*
Given an array arr[] of non-negative integers and a value sum,
check if there is a subset of the given array whose sum is equal to the given sum.
*/

#include <iostream>
#include <vector>

using namespace std;

// similar to knapsack
// iterate through both integers and sum
// use dp matrix for memoization
bool subsetSum(const vector<int> &integers, int sum)
{
    int numIntegers = integers.size();

    // dp[i][j] will be true if there exists a subset of elements from 0 to i with sum = j.
    vector<vector<bool>> dp(numIntegers + 1, vector<bool>(sum + 1, false));

    for (int i = 0; i < numIntegers; i++)
    {
        dp[i][0] = true; // target sum is 0, we have a solution for any amount of integers given to us because we can always take an empty set
    }

    // traverse by integers first so to skip the sums that are smaller than that integers (optimization)
    for (int i = 1; i <= numIntegers; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            if (integers[i - 1] > j)
            {
                // we dont account current element in the sum
                dp[i][j] = dp[i - 1][j]; // does there exist solution without element i?
            }
            else
            {
                // include or exclude
                bool exclude = dp[i - 1][j];
                int sumWithCurrentIncluded = j - integers[i - 1];
                bool include = dp[i - 1][sumWithCurrentIncluded];
                dp[i][j] = exclude || include;
            }
        }
    }

    return dp[numIntegers][sum];
}

int main()
{
    vector<int> integers = {3, 34, 4, 12, 5, 2};
    cout << "Sum of 9: " << subsetSum(integers, 9) << endl;   // 1
    cout << "Sum of 30: " << subsetSum(integers, 30) << endl; // 0

    return 0;
}