#include <iostream>
#include <vector>
using namespace std;

bool wordBreak(const string& s, const vector<string>& wordDict) {
	int n=s.length();
	vector<bool> dp(n+1, false);
	dp[n]=true;

	// traverse the string backwards
	for (int i = n - 1; i >= 0; i--) {
		for (const string& w: wordDict) {
			int len=w.length();
			if (i+len<=n && (w == s.substr(i, len))) {
				dp[i] = dp[i+len];
				if (dp[i])
					break;
			}
		}
	}

	return dp[0];
}

int main()
{
	string s="leetcode";
	vector<string> wordDict= {"leet","code"};
	cout<<wordBreak(s,wordDict)<<endl;

	s="applepenapple";
	wordDict= {"apple","pen"};
	cout<<wordBreak(s,wordDict)<<endl;

	s="catsandog";
	wordDict= {"cats","dog","sand","and","cat"};
	cout<<wordBreak(s,wordDict)<<endl;

	return 0;
}