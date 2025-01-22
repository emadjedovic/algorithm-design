#include <iostream>
#include <vector>
using namespace std;

int rob(const vector<int>& nums) {
	int n=nums.size();
	if(n==0) return 0;
	if(n==1) return nums[0];
	if(n==2) return max(nums[0], nums[1]);

	vector<int> dp(n);
	dp[0]=nums[0];
	dp[1]=nums[1];
	dp[2]=nums[2]+nums[0];

	for(int i=3; i<n; i++)
		dp[i]=nums[i]+max(dp[i-2], dp[i-3]);

	return max(dp[n-1], dp[n-2]);
}

int main()
{
	vector<int> nums = {1,2,3,1};
	cout<<rob(nums)<<endl;

	nums= {2,7,9,3,1};
	cout<<rob(nums)<<endl;

	nums= {2,1,1,2};
	cout<<rob(nums)<<endl;

	nums= {100, 10, 1, 10, 100};
	cout<<rob(nums)<<endl;

	return 0;
}