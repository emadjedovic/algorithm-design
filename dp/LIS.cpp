/*
For a given array, find the length of the longest possible subsequence
in which the elements of the subsequence are sorted in increasing order.
*/

#include <iostream>
#include <vector>

using namespace std;

int LIS(const vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    // an array which stored the LIS length ending with element i (inclusive)
    vector<int> d(n, 0);
    d[0] = 1; // the first element

    for (int i = 1; i < n; i++)
    {
        // for each element i we take the maximum of previous results where previous element j is smaller than i
        int maxPrevious = 0;
        for (int j = 0; j < i; j++)
        {
            if (nums[j] >= nums[i])
                continue;
            if (d[j] > maxPrevious)
            {
                maxPrevious = d[j];
            }
        }
        // if no sequence is formed with previous elements then maxPrevious=0 and we store LIS=1 for that element only
        d[i] = maxPrevious + 1;
    }

    // the subsequence could end at any elements so we find the max of subproblem resuls, not necessarily d[n-1]
    // if n>=1 then result is at least 1
    int result = 0;
    for (int i = 0; i < n; i++)
    {
        if (d[i] > result)
            result = d[i];
    }

    return result;
}

int main()
{
    vector<int> example1 = {3, 10, 2, 1, 20}; // 3
    vector<int> example2 = {30, 20, 10};      // 1
    vector<int> example3 = {2, 2, 2};         // 1
    vector<int> example4 = {10, 20, 35, 80};  // 4

    cout << "Example 1: " << LIS(example1) << endl;
    cout << "Example 2: " << LIS(example2) << endl;
    cout << "Example 3: " << LIS(example3) << endl;
    cout << "Example 4: " << LIS(example4) << endl;
    return 0;
}