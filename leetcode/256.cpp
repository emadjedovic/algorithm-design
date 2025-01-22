#include <iostream>
#include <vector>
using namespace std;

// colors: red, blue, green
// no two adjacent houses have the same color
// Find the minimum cost to paint all houses.
// all positive integers
int paintHouse(const vector<vector<int>>& costMatrix) {
	int numHouses = costMatrix.size();
	vector<vector<int>> dp(numHouses, vector<int>(3, 0));
	for(int i=0; i<3; i++)
		dp[0][i]=costMatrix[0][i];
	for(int i=1; i<numHouses; i++) {
		dp[i][0]=dp[i-1][1]+costMatrix[i][0]; // no other choice
		dp[i][1]=min(dp[i-1][0], dp[i-1][2])+costMatrix[i][1];
		dp[i][2]=dp[i-1][1]+costMatrix[i][2]; // again, no other choice
	}
	int minCost = min(dp[numHouses-1][0], min(dp[numHouses-1][1], dp[numHouses-1][2]));
	return minCost;
}

int main()
{
	vector<vector<int>> costMatrix = {
		{17, 2, 17},
		{16, 16, 5},
		{14, 3, 19}
	};
	cout<<paintHouse(costMatrix)<<endl; // 10

	costMatrix = {{7,6,2}};
	cout<<paintHouse(costMatrix)<<endl; // 2

	return 0;
}