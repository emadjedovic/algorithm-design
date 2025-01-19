#include <iostream>
#include <vector>
using namespace std;

// choose a single day to purchase and another day in future to sell the purchased stock
// go backwards
int maxProfit(const vector<int> &prices)
{
    int n = prices.size();
    int maxFromBack = prices[n - 1];
    int result = 0;
    int i = n - 2;
    while (i >= 0)
    {
        if (prices[i] > maxFromBack)
        {
            maxFromBack = prices[i];
            i--;
            continue;
        }
        if (prices[i] < maxFromBack)
        {
            int candidate = maxFromBack - prices[i];
            if (candidate > result)
                result = candidate;
            // max stays the same
            i--;
        }
    }
    return result;
}

// another way is to calculate for each day the profit if sold the next day
// for 7,1,5,3,6,4 this calculation would result in -6,+4,-2,+3,-2 which
// kind of represents the "state" of one's profit at each point in time
// by adding subsequent values we can try and find the maximum sum, that is
// from which point in time until some other point in time is the sum largest
// its clearly +4,-2,+3=5 (we should stop at +3 - sell the stock)

int main()
{
    vector<int> prices = {7, 1, 5, 3, 6, 4}; // 5
    cout << maxProfit(prices);
    cout << endl;
    vector<int> prices2 = {7, 6, 4, 3, 1}; // 0
    cout << maxProfit(prices2);
    cout << endl;
    vector<int> prices3 = {2, 4, 1}; // 2
    cout << maxProfit(prices3);
    return 0;
}