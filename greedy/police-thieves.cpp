#include <iostream>
#include <vector>
using namespace std;

int policeThief(const vector<char>& v, int k){
   int caught = 0;
   int n=v.size();

   // track police and thief indices
   vector<int> thieves;
   vector<int> policemen;

   for (int i = 0; i < n; i++) {
      if (v[i] == 'P')
         policemen.push_back(i);
      else if (v[i] == 'T')
         thieves.push_back(i);
   }

   // thief and police indices (positions)
   int thief = 0, police = 0;
   while (thief < thieves.size() && police < policemen.size()) {
      if (abs(thieves[thief] - policemen[police]) <= k) {
        // this thief can be caught by this policeman
         caught++;
         thief++;
         police++;
      }
      else if (thieves[thief] < policemen[police]){
        // distance too large, move to next thief
         thief++;
      }
      else{
        // distance too large, move to next policeman
         police++;
      }
   }

   return caught;
}

int main()
{
	vector<char> v1 = { 'P', 'T', 'T', 'P', 'T' };
	cout << "Maximum thieves caught: "
		<< policeThief(v1, 2) << endl; // 2

	vector<char> v2 = { 'T', 'T', 'P', 'P', 'T', 'P' };
	cout << "Maximum thieves caught: "
		<< policeThief(v2, 2) << endl; // 2

	vector<char> v3 = { 'P', 'T', 'P', 'T', 'T', 'P' };
	cout << "Maximum thieves caught: "
		<< policeThief(v3, 3) << endl; // 3
	return 0;
}
