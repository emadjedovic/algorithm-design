// https://codeforces.com/gym/105646/problem/H

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

/*
We have temperature for the next n days (positive integers).
Divide those n days into k non-empty intervals so that
each day belongs to exactly one interval and the average temperature in the coldest of the periods is maximized (we call a period of days the coldest if none of the remaining periods has a strictly lower average temperature).

Then, output the average temperature in the coldest of the periods (the minimum of the maximized averages).
*/

double coldestInterval(const vector<int> &temperatures, int k)
{
    int n = temperatures.size();

    // rows are days, columns are intervals
    // dp[i][j] - j intervals used for days up until ith day
    vector<vector<double>> dp(n + 1, vector<double>(k + 1, 0));

    // Prefix sum for efficient interval sum calculations
    vector<int> prefixSum(n + 1, 0);
    for (int i = 1; i <= n; i++)
        prefixSum[i] = prefixSum[i - 1] + temperatures[i - 1];

    // Base case: one interval only
    for (int days = 1; days <= n; days++)
    {
        dp[days][1] = double(prefixSum[days]) / days;
    }

    // Iterate over the number of intervals (j = 2, ..., k)
    for (int j = 2; j <= k; j++)
    {
        // Iterate over the total number of days (totalDays = j, ..., n)
        for (int totalDays = j; totalDays <= n; totalDays++)
        {
            double maxMinAverage = 0;

            // Iterate over possible divisions of `totalDays` into the last interval
            for (int leftDays = totalDays - 1; leftDays >= j - 1; leftDays--)
            {
                int rightDays = totalDays - leftDays; // Number of days in the last interval
                double rightIntervalAverage = double(prefixSum[totalDays] - prefixSum[leftDays]) / rightDays;

                // The coldest temperature between previous intervals and the last interval
                double result = min(dp[leftDays][j - 1], rightIntervalAverage);

                // Maximize the coldest temperature
                maxMinAverage = max(maxMinAverage, result);
            }

            dp[totalDays][j] = maxMinAverage;
        }
    }

    return dp[n][k];
}

int main()
{
    // n - the number of days for which we have the temperature forecast
    // k - the number of intervals
    int n, k;
    cin >> n >> k;

    // Input temperature for each day
    vector<int> temperatures(n);
    for (int i = 0; i < n; i++)
    {
        cin >> temperatures[i];
    }

    double result = coldestInterval(temperatures, k);

    // Print the result with 10^-4 precision
    cout << fixed << setprecision(10) << result << endl;

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
