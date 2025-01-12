// https://codeforces.com/gym/105646/problem/H

#include <iostream>
#include <vector>
using namespace std;

/*
We have temperature for the next n days (positive integers).
Divide those n days into k non-empty intervals so that
each day belongs to exactly one interval and the average temperature in the coldest of the periods is maximized (we call a period of days the coldest if none of the remaining periods has a strictly lower average temperature).
Then, output the average temperature in the coldest of the periods (the minimum of the maximized averages).
*/

// The answer will be accepted if its absolute error does not exceed 10^{−4}.
double err = 0.0001;

double coldestInterval(const vector<int> &temperatures, int k)
{
    int n = temperatures.size();

    // rows are days, columns are intervals
    // dp[i][j] - j intervals used for days up until ith day
    // our result is dp[n-1][k] -- why not dp[n][k]??
    vector<vector<double>> dp(n, vector<double>(k + 1));
}

int main()
{

    // n -  the number of days for which we have the temperature forecast
    // k - the number of intervals
    int n, k;
    cin >> n >> k;

    // input temperature for each day
    vector<int> temperatures;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        temperatures.push_back(a);
    }

    double result = coldestInterval(temperatures, k);

    if (result == -1)
        cout << "impossible" << endl;
    else
        cout << result << endl;

    return 0;
}

/*
7 3
1 3 1 2 2 2 1

1.666666666667 (that is, 5/3)

Note: The days can be divided into periods as follows: [1,3,1],[2],[2,2,1].
The average temperature in the consecutive intervals will be 5/3, 2, and 5/3,
respectively, resulting in a minimum temperature of 5/3.
This division maximizes the minimum average temperature in a single period.
*/