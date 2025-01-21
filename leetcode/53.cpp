#include <iostream>
#include <vector>
using namespace std;

// similar to stocks where we try to find the subarray with the largest sum
int maxSubArray(const vector<int>& nums) {
	int n=nums.size(); // greater than 0

	vector<int> dp(n);
	// dp[i] - max sum of elements ending at index i (element i included in the sum)
	dp[0]=nums[0];

	int maxSumSoFar = max(0, dp[0]);
	for(int i=1; i<n; i++) {
		dp[i]=max(0,dp[i-1])+nums[i]; // include the last element or start over from the current
		maxSumSoFar=max(maxSumSoFar, dp[i]);
	}

	return maxSumSoFar;
}

int main()
{
	vector<int> nums= {-2,1,-3,4,-1,2,1,-5,4};
	vector<int> nums2= {5,4,-1,7,8};
	vector<int> nums3= {1};
	cout<<maxSubArray(nums)<<endl; // 6
	cout<<maxSubArray(nums2)<<endl; // 23
	cout<<maxSubArray(nums3)<<endl; // 1
	return 0;
}