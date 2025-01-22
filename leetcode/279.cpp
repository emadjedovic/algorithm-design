#include <iostream>
#include <vector>
using namespace std;

int numSquares(int n) {

	vector<int> perfSq;
	for(int i=1; i*i<=n; i++)
		perfSq.push_back(i*i);

	// the least number of elements from perfSq that sum up to i
	vector<int> dp(n+1,n); // the worst case 1+1+1+1... n times until we reach n
	dp[0]=0;
	for(int ps: perfSq) {
		for(int i=ps; i<n+1; i++) {
			dp[i]=min(dp[i], 1+dp[i-ps]);
		}
	}
	return dp[n];
}

int main()
{
	cout<<numSquares(1)<<endl;
	cout<<numSquares(12)<<endl;
	cout<<numSquares(13)<<endl;

	return 0;
}