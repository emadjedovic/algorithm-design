#include <iostream>
#include <vector>
using namespace std;

int paintFence(int postNum, int colNum) {
	if(postNum==0 || colNum==0) return 0;
	if(postNum==1) return colNum;
	if(postNum==2) return colNum*colNum;
	vector<vector<int>> dp(postNum, vector<int>(2));
	// dp[i][0] - number of way to color the first i+1 posts if the ith post has color different from the previous post
	// dp[i][1] - ith post has the color same as the previous post
	dp[0][0]=colNum;
	dp[0][1]=colNum; // no previous posts exist
	dp[1][0]=dp[0][1]*(colNum-1);
	dp[1][1]=dp[0][0];
	for(int i=2; i<postNum; i++) {
		dp[i][0]=(dp[i-1][1]+dp[i-1][0])*(colNum-1); // does not matter whether the previous one has a "repeated" color or a unique one, we take into account both cases
		dp[i][1]=dp[i-1][0]; // only the case where the previous post has a non-repeating color
	}

	return dp[postNum-1][1]+dp[postNum-1][0];
}

int main()
{
	int n=3;
	int k=2;
	cout<<paintFence(n,k)<<endl; // 6
	n=1;
	k=1;
	cout<<paintFence(n,k)<<endl; // 1
	n=7;
	k=2;
	cout<<paintFence(n,k)<<endl; // 42
	n=2;
	k=4;
	cout<<paintFence(n,k)<<endl; // 16

	return 0;
}