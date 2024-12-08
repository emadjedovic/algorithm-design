// leetcode.com/problems/house-robber/description/?envType=problem-list-v2&envId=dynamic-programming

// can't rob two adjacent houses

#include <iostream>
#include <vector>

using namespace std;

int rob(const vector<int> &nums)
{
    int numHouses = nums.size();
    if (numHouses == 0)
        return 0;
    if (numHouses == 1)
        return nums[0];

    // maximum worth robbed if we have also robbed house number i
    vector<int> D_lastRobbed(10000, 0);
    D_lastRobbed[0] = nums[0];
    D_lastRobbed[1] = nums[1];

    // we might have robbed house i or not
    // our final solution will be on index numHouses-1
    vector<int> D_robbedOrNot(10000, 0);
    D_robbedOrNot[0] = nums[0];
    D_robbedOrNot[1] = max(nums[0], nums[1]);

    for (int i = 2; i < numHouses; i++)
    {
        // must skip the house before if we want to rob this one
        D_lastRobbed[i] = nums[i] + D_robbedOrNot[i - 2];
        // D_lastRobbed[3] = nums[3]+D_robbedOrNot[1]; might be nums[3]+nums[1] or nums[3]+nums[0]
        if (D_lastRobbed[i] > D_lastRobbed[i - 1])
        {
            // robbing house i pays off more than robbing house i-1
            D_robbedOrNot[i] = D_lastRobbed[i];
        }
        else
        {
            D_robbedOrNot[i] = D_lastRobbed[i - 1];
        }
    }

    return D_robbedOrNot[numHouses - 1];
}

int main()
{
    vector<int> nums1 = {1, 2, 3, 1};
    // 4: rob house 1 and then house 3
    cout << "Example 1: " << rob(nums1) << endl;

    vector<int> nums2 = {2, 7, 9, 3, 1};
    // 12: rob house 1, house 3 and then house 5
    cout << "Example 2: " << rob(nums2) << endl;

    vector<int> nums3 = {2, 1, 1, 2};
    cout << "Example 3: " << rob(nums3) << endl;

    return 0;
}