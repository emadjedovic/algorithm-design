#include <iostream>
#include <vector>
using namespace std;

bool isSubsequence(string s, string t)
{
    int positionS = 0;
    int positionT = 0;
    while (true)
    {
        if (s[positionS] == t[positionT])
        {
            positionS++;
            positionT++;
            if (positionS == s.length())
                return true;
        }
        else
        {
            positionT++;
            if (positionT >= t.length())
                return false;
        }
    }
}

int main()
{
    string s, t;
    cin >> s >> t;
    cout << isSubsequence(s, t);
    return 0;
}