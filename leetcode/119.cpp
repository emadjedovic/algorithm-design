#include <iostream>
#include <vector>
using namespace std;

vector<int> getRow(int rowIndex)
{
    vector<vector<int>> all(rowIndex + 1, vector<int>{1});
    if (rowIndex == 0)
        return all[0];
    all[1].push_back(1); // 2nd row -- 1 1
    if (rowIndex == 1)
        return all[1];

    for (int i = 2; i < rowIndex + 1; i++)
    {
        for (int j = 1; j < i; j++)
        {
            all[i].push_back(all[i - 1][j - 1] + all[i - 1][j]);
        }
        all[i].push_back(1); // 3rd row -- 1 2 1 (i=2, the last 1 is on the index i)
    }
    return all[rowIndex];
}

int main()
{
    int rowIndex;
    cin >> rowIndex;
    vector<int> res = getRow(rowIndex);
    cout << "[ ";
    for (int i : res)
        cout << i << " ";
    cout << "]";
    return 0;
}