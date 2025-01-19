#include <iostream>
#include <vector>
using namespace std;

int fib(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    int prevprev = 0;
    int prev = 1;
    int current = 1; // 0+1 (result for n=2)
    int counter = 2;

    while (counter != n)
    {
        int temp = current;
        current += prev;
        prevprev = prev;
        prev = temp;
        counter++;
    }

    return current;
}

int main()
{
    int n;
    cin >> n;
    cout << fib(n);
    return 0;
}