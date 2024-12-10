/*
Given a rod of length n inches and an array price[].
price[i] denotes the value of a piece of length i.
The task is to determine the maximum value obtainable by cutting up the rod and selling the pieces.
*/

#include <iostream>
#include <vector>

using namespace std;

int cutRod(const vector<int> &prices)
{
    int n = prices.size(); // rode length
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    /*
    For each rod of length i from 1 to n,
    find the maximum value that can obtained
    by cutting it into two pieces of length j and (i-j).
    */

    vector<int> dp(n + 1, 0);
    // dp[0] means the rod of length 0
    dp[1] = prices[0];

    for (int i = 2; i <= n; i++)
    {
        int maxProfit = 0;
        for (int j = 0; j < i; j++)
        {
            int leftPartProfit = dp[j];
            int singleCutMade = prices[i - j - 1];
            maxProfit = max(maxProfit, singleCutMade + leftPartProfit);
        }
        dp[i] = maxProfit;
    }

    int result = 0;
    for (size_t i = 0; i < dp.size(); i++)
        if (dp[i] > result)
            result = dp[i];

    return result;
}

int main()
{
    vector<int> prices1 = {1, 5, 8, 9, 10, 17, 17, 20}; // 22
    // The maximum obtainable value is 22 by cutting in two pieces of lengths 2 and 6, i.e., 5 + 17 = 22.
    cout << "For prices1: " << cutRod(prices1) << endl;

    vector<int> prices2 = {3, 5, 8, 9, 10, 17, 17, 20}; // 24
    // The maximum obtainable value is 24 by cutting the rod into 8 pieces of length 1, i.e, 8*price[1]= 8*3 = 24.
    cout << "For prices2: " << cutRod(prices2) << endl;

    vector<int> prices3 = {3}; // 3
    // There is only 1 way to pick a piece of length 1.
    cout << "For prices3: " << cutRod(prices3) << endl;

    return 0;
}