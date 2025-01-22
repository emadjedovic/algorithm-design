#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int nthUglyNumber(int n) {
	vector<int> dp(n+1);
	dp[1] = 1;
	int multiples2 = 1;
	int multiples3 = 1;
	int multiples5 = 1;

	for (int i = 2; i < n+1; i++) {
		int nextUgly = min({dp[multiples2] * 2, dp[multiples3] * 3, dp[multiples5] * 5}); // take the smallest not-yet-generated multiple
		dp[i] = nextUgly;

		if (nextUgly == dp[multiples2] * 2) multiples2++;
		if (nextUgly == dp[multiples3] * 3) multiples3++;
		if (nextUgly == dp[multiples5] * 5) multiples5++;
	}

	return dp[n];
}


int main()
{
	cout<<nthUglyNumber(10)<<endl; // 12
	cout<<nthUglyNumber(1)<<endl; // 1
	return 0;
}