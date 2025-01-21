#include <iostream>
#include <vector>
using namespace std;

// s3.length() = s1.length()+s2.length()
bool isInterleave(const string& s1, const string& s2, const string& s3) {
	int n1 = s1.length();
	int n2 = s2.length();
	if(s3.length()!=(n1+n2)) return false;

	// dp[i][j] represents whether the first i characters of s1 and the first j characters of s2 can interleave to form the first i + j characters of s3
	vector<vector<bool>> dp(n1+1, vector<bool>(n2+1, false));
	dp[0][0]=true; // both strings empty

	// s1 empty - s2 must exactly match s3
	for(int i=1; i<n2; i++) {
		dp[0][i]=(s2[i-1]==s3[i-1])&&dp[0][i-1];
	}

	// s2 empty - s1 must exactly match s3
	for(int i=1; i<n1; i++) {
		dp[i][0]=(s1[i-1]==s3[i-1])&&dp[i-1][0];
	}

	// the rest cases
	for (int i = 1; i <= n1; i++) {
		for (int j = 1; j <= n2; j++) {
			int k = i+j; // in s3
			bool takeLetterFromS1 = s1[i - 1] == s3[k - 1];
			bool takeLetterFromS2 = s2[j - 1] == s3[k - 1];
			dp[i][j] = (takeLetterFromS1 && dp[i - 1][j]) ||
			           (takeLetterFromS2 && dp[i][j - 1]);
		}
	}

	return dp[n1][n2];
}

int main()
{
	string s1="aabcc";
	string s2="dbbca";
	string s3="aadbbcbcac";
	cout<<isInterleave(s1,s2,s3)<<endl; // true
	s1="aabcc";
	s2="dbbca";
	s3="aadbbbaccc";
	cout<<isInterleave(s1,s2,s3)<<endl; // false
	s1="";
	s2="";
	s3="";
	cout<<isInterleave(s1,s2,s3)<<endl; // true
	s1 = "XXY";
	s2 = "XXZ";
	s3 = "XXZXXXY";
	cout<<isInterleave(s1,s2,s3)<<endl; // false
	return 0;
}