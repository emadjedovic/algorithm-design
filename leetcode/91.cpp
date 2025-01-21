#include <iostream>
#include <vector>
using namespace std;

bool validTwoDigitNum(const string& num) {
	if(num[0]=='1') return true;
	if(num[0]=='2' && num[1]>='1' && num[1]<='6') return true;
	return false;
}

int numDecodings(const string& s) {
	int n=s.length();
	if(n==1) return 1;
	vector<int> dp(n);
	if(s[0]=='0') return 0; // invalid
	dp[0]=1; // one way to decode string of length 1
	dp[1]=1; // two letters
	if(validTwoDigitNum(s.substr(0,2))) {
		dp[1]++; // add two-digit decode
	}
	for(int i=2; i<n; i++) {
		dp[i]=dp[i-1]; // the ith number is decoded with one letter
		if(validTwoDigitNum(s.substr(i-1,2))) {
			dp[i]+=dp[i-2]; // add two-digit decode for the last two numbers
		}
	}
	return dp[n-1];
};

int main()
{
	string s="12";
	cout<<numDecodings(s)<<endl;
	s="226";
	cout<<numDecodings(s)<<endl;
	s="06";
	cout<<numDecodings(s)<<endl;
	return 0;
}