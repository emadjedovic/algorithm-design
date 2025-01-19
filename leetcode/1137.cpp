#include <iostream>
#include <vector>
using namespace std;

int tribonacci(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    if (n == 2)
        return 1;

    int prev3 = 0;
    int prev2 = 1;
    int prev1 = 1;

    int currentRes = prev3 + prev2 + prev1;
    int currentN = 3;
    while (currentN != n)
    {
        int temp = currentRes;
        currentRes += prev1 + prev2;
        prev3 = prev2;
        prev2 = prev1;
        prev1 = temp;
        currentN++;
    }

    return currentRes;
}

int main()
{
    int n;
    cin >> n;
    cout << tribonacci(n);
    return 0;
}