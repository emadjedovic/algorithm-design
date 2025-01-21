#include <iostream>
#include <vector>
using namespace std;

// insert, delete, replace
int minDistance(const string& word1, const string& word2) {
	int m=word1.length();
	int n=word2.length();
	if(m==0 || n==0) return max(m,n); // all insert or all delete

	vector<vector<int>> dp(m+1, vector<int>(n+1));
	for(int i=0; i<n+1; i++) {
		// word1 is empty, word2 has i amount of chars
		dp[0][i]=i; // insert
	}
	for(int i=0; i<m+1; i++) {
		// word1 has i amount of chars, word2 is empty
		dp[i][0]=i; // delete
	}
	// if word1[i-1] == word2[j-1] then dp[i][j]=dp[i-1][j-1] -- no action needed
	for(int i=1; i<m+1; i++) {
		for(int j=1; j<n+1; j++) {
			if(word1[i-1]==word2[j-1])
				dp[i][j]=dp[i-1][j-1];
			else {
				dp[i][j]=1+min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]));
			}
		}
	}
	return dp[m][n];
}

int main()
{
	string word1 = "horse";
	string word2="ros";
	cout<<minDistance(word1, word2)<<endl;
	word1="intention";
	word2="execution";
	cout<<minDistance(word1, word2)<<endl;

	return 0;
}