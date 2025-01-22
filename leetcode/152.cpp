#include <iostream>
#include <vector>
using namespace std;

int maxProduct(const vector<int>& nums) {
	int n=nums.size();
	vector<vector<int>> dp(n, vector<int>(n));
	// dp[i][j] - the product of numbers starting from nums[i] up to nums[j] (inclusive)
	int maxValue = nums[0];

	for(int i=0; i<n; i++) {
		dp[i][i]=nums[i]; // one-factor products
		maxValue = max(dp[i][i], maxValue);
	}

	for(int i=0; i<n-1; i++) {
		for(int j=i+1; j<n; j++) {
			dp[i][j]=dp[i][j-1]*nums[j];
			maxValue = max(dp[i][j], maxValue);
		}
	}

	return maxValue;
}

int main()
{
	vector<int> nums= {2,3,-2,4};
	cout<<maxProduct(nums)<<endl;

	nums= {-2,0,-1};
	cout<<maxProduct(nums)<<endl;

	return 0;
}