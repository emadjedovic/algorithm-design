#include <iostream>
#include <vector>
using namespace std;

vector<int> countBits(int n)
{
    vector<int> ans(n + 1); // ans[i] is the number of 1's in the binary representation of i
    for (int i = 1; i < n + 1; i++)
    {
        if (i % 2 == 1)
            ans[i] = ans[i - 1] + 1;
        else
            ans[i] = ans[i / 2];
    }
    return ans;
}

int main()
{
    int n;
    cin >> n;
    vector<int> ans = countBits(n);
    for (int a : ans)
        cout << a << " ";
    cout << endl;

    return 0;
}