#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> generate(int numRows)
{
    vector<vector<int>> ans(numRows, vector<int>{1});
    if (numRows == 1)
        return ans;
    ans[1].push_back(1);

    // we copy the result for ans of numRows-1 and we add one more vector
    for (int i = 2; i < numRows; i++)
    {
        for (int j = 1; j < i; j++)
        {
            ans[i].push_back(ans[i - 1][j] + ans[i - 1][j - 1]); // starting from 1 2 1
        }
        ans[i].push_back(1);
    }

    return ans;
}

int main()
{
    int numRows;
    cin >> numRows;
    vector<vector<int>> ans = generate(numRows);
    for (const vector<int> &v : ans)
    {
        cout << "[ ";
        for (int i = 0; i < v.size(); i++)
        {
            cout << v[i] << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}