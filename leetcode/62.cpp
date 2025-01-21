#include <iostream>
#include <vector>
using namespace std;

int uniquePaths(int m, int n) {

	// either down or right one step at a time
	vector<vector<int>> dp(m, vector<int>(n));
	// dp[i][j]=dp[i-1][j]+dp[i][j-1]; -- number of way to come from the top square and the left square

	// first row
	for(int j=0; j<n; j++) {
		dp[0][j]=1;
	}
	// first column
	for(int i=0; i<m; i++) {
		dp[i][0]=1;
	}

	// using recurrence relation
	for(int i=1; i<m; i++) {
		for(int j=1; j<n; j++) {
			dp[i][j]=dp[i-1][j]+dp[i][j-1];
		}
	}

	return dp[m-1][n-1];
}

int main()
{
	int m,n;
	cin>>m>>n;
	cout<<uniquePaths(m,n)<<endl;
	cin>>m>>n;
	cout<<uniquePaths(m,n)<<endl;
	return 0;
}