#include <iostream>
#include <vector>
using namespace std;

string longestPalindrome(const string& s) {
	int n=s.length();
	vector<vector<bool>> dp(n, vector<bool>(n, false)); // string from index i to index j is a palindrome
	int maxDistance = 1;
	int startIndex=0;

	// each individual letter is palindromic
	for(int i=0; i<n; i++) {
		dp[i][i]=true;
		maxDistance=1;
		startIndex=i;
	}
	// two-letter palindromes
	for(int i=0; i<n-1; i++) {
		if(s[i]==s[i+1]) {
			dp[i][i+1]=true;
			maxDistance=2;
			startIndex=i;
		}
	}

	// palindromes of length >= 3
	for(int len=3; len<n; len++) {
		int start=0;
		int end=start+len-1;
		// moving window of size "len" until the end of string is reached
		while(end<=n-1) {
			if(dp[start+1][end-1] && s[start]==s[end]) {
				dp[start][end]=true;
				if(len>maxDistance) {
					maxDistance=len;
					startIndex=start;
				}
			}
			// move one step to the right
			start++;
			end=start+len+1;
		}
	}

	// we want the dp[i][j] where the difference j-i is the largest
	return s.substr(startIndex,maxDistance);
}

int main()
{
	string s="babad";
	string t="cbbd";
	cout<<longestPalindrome(s)<<endl;
	cout<<longestPalindrome(t)<<endl;

	return 0;
}