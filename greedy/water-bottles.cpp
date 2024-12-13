/*
You are given container full of water.
Container can have limited amount of water.
You also have N bottles to fill.
You need to find the maximum numbers of bottles you can fill.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxBottles(int L, const vector<int> &b)
{
    vector<int> bottles = b;
    sort(bottles.begin(), bottles.end());
    int num = 0;
    int remainingCapacity = L;
    for (int i = 0; i < bottles.size(); i++)
    {
        if (bottles[i] > remainingCapacity)
            break;
        num++;
        remainingCapacity -= bottles[i];
    }

    return num;
}

int main()
{
    int liters = 20;
    vector<int> bottles = {1, 2, 3, 4, 5, 5, 7, 8, 9, 10};
    cout << maxBottles(liters, bottles) << endl;
    return 0;
}