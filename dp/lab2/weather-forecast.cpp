// https://codeforces.com/gym/105646/problem/H

#include <iostream>
#include <vector>
using namespace std;

/*
Radewoosh is a meteorologist. Thanks to his research station, he has learned the
predicted temperature for the next n days. The temperature for each day,
expressed in Bytenheit degrees, is always a positive integer.

He has decided to divide the next n days into k non-empty intervals so that
each day belongs to exactly one interval. Then, in the weather forecast,
Radewoosh will only provide k numbers - the arithmetic averages of the
temperatures from the days belonging to the respective intervals.

Make a division that maximizes the average temperature in the coldest of the
periods he provides (we call a period of days the coldest if none of the
remaining periods has a strictly lower average temperature).
*/

// The answer will be accepted if its absolute error does not exceed 10^{−4}.
double maxAverageTemp()
{
}

int main()
{

    // n -  the number of days for which Radewoosh has the temperature forecast
    // k - the number of periods into which he wants to divide it
    int n, k;
    cin >> n >> k;
    //  the temperature on consecutive days, expressed in Bytenheit degrees
    vector<int> temperatures;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        temperatures.push_back(a);
    }

    if (false)
        cout << "impossible" << endl;
    else
        cout << maxAverageTemp() << endl;

    return 0;
}

/*
7 3
1 3 1 2 2 2 1

1.666666666667

Note: The days can be divided into periods as follows: [1,3,1],[2],[2,2,1].
The average temperature in the consecutive intervals will be 5/3, 2, and 5/3,
respectively, resulting in a minimum temperature of 5/3.
This division maximizes the minimum average temperature in a single period.
*/