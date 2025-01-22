#include <iostream>
#include <vector>
using namespace std;

int minimumTotal(const vector<vector<int>>& triangle) {
	int rowNum = triangle.size();
	vector<vector<int>> dp(rowNum, vector<int>(rowNum,10000000));
	dp[0][0]=triangle[0][0];
	// first column
	for(int i=1; i<rowNum; i++) {
		dp[i][0]=dp[i-1][0]+triangle[i][0];
	}
	// last column
	for(int i=1; i<rowNum; i++) {
		int colNum = triangle[i].size();
		dp[i][colNum-1]=dp[i-1][colNum-2]+triangle[i][colNum-1];
	}
	// others
	for(int i=1; i<rowNum; i++) {
		int colNum = triangle[i].size();
		for(int j=1; j<colNum; j++) {
			dp[i][j]=min(dp[i-1][j], dp[i-1][j-1])+triangle[i][j];
		}
	}

	int result=10000000;
	int lastRowSize=triangle[rowNum-1].size();
	for(int i=0; i<lastRowSize; i++) {
		if(dp[rowNum-1][i]<result) {
			result = dp[rowNum-1][i];
		}
	}
	return result;
}

int main()
{
	vector<vector<int>> triangle = {
		{2},
		{3, 4},
		{6, 5, 7},
		{4, 1, 8, 3}
	};
	cout<<minimumTotal(triangle)<<endl;

	/*
	2
	3 4
	6 5 7
	4 1 8 3
	*/
	triangle = {{-10}};
	cout<<minimumTotal(triangle)<<endl;

	return 0;
}