#include <iostream>
#include <vector>
using namespace std;

int maxProfit(const vector<int>& prices) {
	int n=prices.size();
	vector<int> sellNextDay;
	for(int i=0; i<n-1; i++) {
		sellNextDay.push_back(prices[i+1]-prices[i]);
	}
	sellNextDay.push_back(0-prices[n-1]); // cannot sell the last one
	// for {7,1,5,3,6,4}; we have {-6,4,-2,3,-2,-4}
	int profit = 0;
	for(int i=0; i<n; i++) {
		if(sellNextDay[i]>0) profit+=sellNextDay[i];
	}
	return profit;
}

int main()
{
	vector<int> prices = {7,1,5,3,6,4};
	cout<<maxProfit(prices)<<endl;
	prices = {1,2,3,4,5};
	cout<<maxProfit(prices)<<endl;
	prices = {7,6,4,3,1};
	cout<<maxProfit(prices)<<endl;
	return 0;
}