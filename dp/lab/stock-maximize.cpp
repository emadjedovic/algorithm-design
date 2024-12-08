// www.hackerrank.com/challenges/stockmax/problem

/*
Each day, you can either buy one share of WOT,
sell any number of shares of WOT that you own,
or not make any transaction at all.

What is the maximum profit you can obtain with an optimum strategy?
*/

#include <iostream>
#include <vector>

using namespace std;

// prices - predicted daily stock prices
int stockmax(const vector<int> &prices)
{
    int n = prices.size();
    if (n == 0)
        return 0; // No prices, no profit
    if (n == 1)
        return 0; // Only one day, no opportunity to buy and sell

    int max_future_price = 0;
    int profit = 0;

    // traverse backwards
    for (int i = n - 1; i >= 0; i--)
    {
        if (prices[i] >= max_future_price)
        {
            max_future_price = prices[i];
            // this ensures we never sell anything once we enter a descending share-price sequence
        }
        else
        {
            // buy shares because we can sell them later at a price higher than current
            profit += max_future_price - prices[i];
            // compare with examples down below, it makes sense
        }
    }
    return profit;
}

int main()
{
    vector<int> prices1 = {1, 2}; // 1
    cout << "Example 1: " << stockmax(prices1) << endl;
    // Buy one share day one, and sell it day two for a profit of 1.

    vector<int> prices2 = {2, 1}; // 0
    cout << "Example 2: " << stockmax(prices2) << endl;
    // No profit can be made so you do not buy or sell stock those days.

    vector<int> prices3 = {5, 3, 2}; // 0
    cout << "Example 3: " << stockmax(prices3) << endl;
    // There is no profit because the share price never rises.

    vector<int> prices4 = {1, 2, 100}; // 197
    cout << "Example 4: " << stockmax(prices4) << endl;
    // Buy one share on the first two days and sell both of them on the third day.

    vector<int> prices5 = {1, 3, 1, 2}; // 3
    cout << "Example 5: " << stockmax(prices5) << endl;
    // Buy one share on day 1, sell one on day 2, buy one share on day 3, and sell one share on day 4.

    return 0;
}