#include <iostream>
#include <vector>
using namespace std;

// greedy again
bool canJump(const vector<int>& nums) {
    int n=nums.size();
    if(n==0) return true;
    int maxReached = 0;
    
    for(int i=0; i<n; i++){
        if(i>maxReached) return false; // surpassed the last one reachable
        maxReached=max(maxReached, i+nums[i]);
        if(maxReached==n-1) return true;
    }
    return true;
}

int main()
{
	vector<int> nums= {2,3,1,1,4};
	vector<int> nums2= {3,2,1,0,4};
	cout<<canJump(nums)<<endl;
	cout<<canJump(nums2)<<endl;
	return 0;
}