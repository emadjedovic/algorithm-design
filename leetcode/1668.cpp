#include <iostream>
#include <vector>
using namespace std;

int maxRepeating(const string &sequence, const string &word)
{
    int counter = 0;
    int positionS = 0;
    int positionW = 0;
    while (positionS < sequence.length())
    {
        if (sequence[positionS] == word[positionW])
        {
            positionS++;
            positionW++;
            if (positionW == word.length())
            {
                counter++;
                positionW = 0;
            }
        }
        else
        {
            // chars not equal
            if (positionW == 1)
                positionW = 0; // start over, don't increment sequence
            else
                positionS++;
        }
    }
    return counter;
}

int main()
{
    string s = "ababc";
    string w = "ab";
    cout << maxRepeating(s, w) << endl; // 2
    w = "ba";
    cout << maxRepeating(s, w) << endl; // 1
    w = "ac";
    cout << maxRepeating(s, w) << endl; // 0
    s = "aaabaaaabaaabaaaabaaaabaaaabaaaaba";
    w = "aaaba";
    cout << maxRepeating(s, w) << endl; // 6
    return 0;
}