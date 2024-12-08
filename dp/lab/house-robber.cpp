// leetcode.com/problems/house-robber/description/?envType=problem-list-v2&envId=dynamic-programming

/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
*/

#include <iostream>
#include <vector>

using namespace std;

int rob(const vector<int> &nums)
{
}

int main()
{
    vector<int> nums1 = {1, 2, 3, 1};
    // 4: rob house 1 and then house 3
    cout << "Example 1: " << rob(nums1) << endl;

    vector<int> nums2 = {2, 7, 9, 3, 1};
    // 12: rob house 1, house 3 and then house 5
    cout << "Example 2: " << rob(nums2) << endl;

    return 0;
}