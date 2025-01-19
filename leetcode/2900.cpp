#include <iostream>
#include <vector>
using namespace std;

// greedy
vector<string> getLongestSubsequence(const vector<string> &words, const vector<bool> &groups)
{
    int n = words.size();
    vector<string> wordsTaken;
    wordsTaken.push_back(words[0]);

    for (int i = 1; i < n; i++)
    {
        if (groups[i] == groups[i - 1])
        {
            continue;
        }
        else
        {
            wordsTaken.push_back(words[i]);
        }
    }

    return wordsTaken;
}

int main()
{
    vector<string> words = {"e", "a", "b"};
    vector<bool> groups = {0, 0, 1};
    vector<string> result = getLongestSubsequence(words, groups);
    for (string s : result)
        cout << s << " ";
    cout << endl;
    return 0;
}