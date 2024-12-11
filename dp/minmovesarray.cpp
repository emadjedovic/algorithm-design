/*
Given an array of size N, the task is to find the minimum moves to the
beginning or end of the array required to make the array sorted in non-decreasing order.

given the "array" - sort it and compare
dp[i][j] where original array is analized until ith element and the sorted array until jth element

LIS modification
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// actually non-decreasing instead of increasing
// change from < to <= in element comparison
int minMovesLIS(const vector<int> &array)
{
    int n = array.size();

    vector<int> dp(n + 1, 0); // ending in ith element
    for (int i = 1; i <= n; i++)
    {
        int maxPreviousResult = 0;
        for (int j = 0; j < i; j++)
        {
            if (array[j - 1] > array[i - 1])
                continue;
            if (dp[j] > maxPreviousResult)
                maxPreviousResult = dp[j];
        }
        dp[i] = maxPreviousResult + 1;
    }

    int longestNonDecreasingSequence = 0;
    for (int i = 0; i <= n; i++)
        longestNonDecreasingSequence = max(longestNonDecreasingSequence, dp[i]);

    cout << "Longest Non-Decreasing Subsequence: " << longestNonDecreasingSequence << endl;
    // the number of elements that need moving
    return n - longestNonDecreasingSequence;
}

int main()
{
    vector<int> array1 = {4, 7, 2, 3, 9}; // 2 (move 3 to the beginning and then 2)
    // 2 3 4 7 9
    cout << "minMoves: " << minMovesLIS(array1) << endl;

    vector<int> array2 = {1, 4, 5, 7, 12}; // 0 (already sorted)
    cout << "minMoves: " << minMovesLIS(array2) << endl;

    vector<int> array3 = {8, 2, 1, 5, 4}; // 5 - 2 = 3
    // after sorting their index values will be 2,1,4,3,0 with the longest streak of 2 (1, 4)
    cout << "minMoves: " << minMovesLIS(array3) << endl;

    return 0;
}