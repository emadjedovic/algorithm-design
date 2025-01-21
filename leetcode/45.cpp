#include <iostream>
#include <vector>
using namespace std;

// greedy works!
int jump(const vector<int>& nums) {
    
    if(nums.size()<=1) return 0;
	
	int jumps=0;
	int currentEnd=0;
	int farthersReached = 0;
	
	// we compare currentEnd with nums[i] to determine farthersReached
	// repeat until currentEnd==nums.size();
	
	for(int i=0; i<nums.size()-1; i++){
	    if(i+nums[i]>farthersReached)
	    farthersReached=i+nums[i]; // we do not immediately jump farthersReached
	    // we wait until we've reached the end of the range for the current jump
	    if(i==currentEnd){
	        // update the currentEnd
	        currentEnd = farthersReached;
	        // now we jump to the farthersReached
	        jumps++;
	        if(currentEnd>=nums.size()-1) break;
	    }
	}
	
	return jumps;
}

int main()
{
	vector<int> nums= {2,3,1,1,4};
	vector<int> nums2= {2,3,1,1,4};
	vector<int> nums3= {5, 1, 8, 1, 1, 1, 1, 1, 1, 1, 1};
	cout<<jump(nums)<<endl;
	cout<<jump(nums2)<<endl;
	cout<<jump(nums3)<<endl;
	return 0;
}