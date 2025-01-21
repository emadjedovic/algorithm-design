#include <iostream>
#include <vector>
using namespace std;

int uniquePathsWithObstacles(const vector<vector<int>>& obstacleGrid) {

	int m=obstacleGrid.size();
	int n=obstacleGrid[0].size();

	vector<vector<int>> dp(m, vector<int>(n));
	dp[0][0]=1;

	// first row
	for(int i=1; i<n; i++) {
		if(dp[0][i-1]==0 || obstacleGrid[0][i]==1) {
			dp[0][i]=0;
		} else {
			dp[0][i]=1;
		}
	}

	// first column
	for(int i=1; i<m; i++) {
		if(dp[i-1][0]==0 || obstacleGrid[i][0]==1) {
			dp[i][0]=0;
		} else {
			dp[i][0]=1;
		}
	}

	for(int i=1; i<m; i++) {
		for(int j=1; j<n; j++) {
			if(obstacleGrid[i][j]==1 || (dp[i-1][j]==0 && dp[i][j-1]==0))
				dp[i][j]=0;
			else {
				dp[i][j]=dp[i-1][j]+dp[i][j-1];
			}
		}
	}

	return dp[m-1][n-1];
}

int main()
{
	vector<vector<int>> obstacleGrid1 = {
		{0,0,0},{0,1,0},{0,0,0}
	};
	cout<<uniquePathsWithObstacles(obstacleGrid1)<<endl;
	vector<vector<int>> obstacleGrid2 = {
		{0,1},{0,0}
	};
	cout<<uniquePathsWithObstacles(obstacleGrid2)<<endl;
	return 0;
}