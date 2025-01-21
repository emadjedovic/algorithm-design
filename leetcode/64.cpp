#include <iostream>
#include <vector>
using namespace std;

int minPathSum(const vector<vector<int>>& grid) {
	int rowNum = grid.size();
	int colNum = grid[0].size();
	vector<vector<int>> dp(rowNum, vector<int>(colNum));
	dp[0][0]=grid[0][0];

	// first row
	for(int i=1; i<colNum; i++) {
		dp[0][i]=dp[0][i-1]+grid[0][i];
	}

	// first column
	for(int i=1; i<rowNum; i++) {
		dp[i][0]=dp[i-1][0]+grid[i][0];
	}

	// other cells
	for(int i=1; i<rowNum; i++) {
		for(int j=1; j<colNum; j++) {
			dp[i][j]=min(dp[i-1][j], dp[i][j-1])+grid[i][j];
		}
	}

	return dp[rowNum-1][colNum-1];
}

int main()
{
	vector<vector<int>> grid1 = {
		{1, 3, 1},
		{1, 5, 1},
		{4, 2, 1}
	};
	cout<<minPathSum(grid1)<<endl;
	vector<vector<int>> grid2 = {
		{1, 2, 3},
		{4, 5, 6}
	};
	cout<<minPathSum(grid2)<<endl;
	return 0;
}