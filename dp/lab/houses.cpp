/*
Given a series of houses located at different positions along a road,
with each house having a specific value associated with it, determine
the maximum possible value you can collect from the houses,
under the condition that you cannot pick values from two houses
if the distance between them is less than k.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int collectedValue(const vector<int> &positions, const vector<int> &values, int k)
{
    int numHouses = positions.size();
    vector<int> maxValueIncluded(numHouses, 0);
    vector<int> maxValueEitherIncluded(numHouses, 0);

    // first house is always included
    maxValueIncluded[0] = values[0];
    maxValueEitherIncluded[0] = values[0];

    for (int i = 1; i < numHouses; i++)
    {
        // find the first house to the left that is too close
        int border = positions[i] - k;
        auto firstHouseTooClose = lower_bound(positions.begin(), positions.begin() + i, border);
        int firstHouseIndex = firstHouseTooClose - positions.begin();

        if (firstHouseIndex > 0)
        {
            maxValueIncluded[i] = values[i] + maxValueEitherIncluded[firstHouseIndex - 1];
        }
        else
        {
            //  no houses to the left available
            maxValueIncluded[i] = values[i];
        }

        maxValueEitherIncluded[i] = max(maxValueIncluded[i], maxValueEitherIncluded[i - 1]);
    }

    return maxValueEitherIncluded[numHouses - 1];
}

int main()
{
    vector<int> position = {1, 3, 6, 10};
    vector<int> value = {5, 10, 15, 20};
    int k = 3;

    cout << "Maximum collected value from houses: "
         << collectedValue(position, value, k) << endl;

    return 0;
}
