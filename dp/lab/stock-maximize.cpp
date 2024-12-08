// www.hackerrank.com/challenges/stockmax/problem

/*
Your algorithms have become so good at predicting the market that you now know what the share price of Wooden Orange Toothpicks Inc. (WOT) will be for the next number of days.

Each day, you can either buy one share of WOT, sell any number of shares of WOT that you own, or not make any transaction at all. What is the maximum profit you can obtain with an optimum trading strategy?
*/

#include <iostream>
#include <vector>

using namespace std;

// prices - predicted daily stock prices
int stockmax(const vector<int> &prices)
{
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