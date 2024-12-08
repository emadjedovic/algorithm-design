// www.spoj.com/problems/ACODE/
// how many decodings there can be for a given string
// 1-1, B-2, ..., Z-26

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// check if a two-character string is a valid encoding between 10 and 26
bool validNumber(string ab)
{
    return (ab[0] == '1' || ab[0] == '2') && ab[1] <= '6';
}

int numPossibleDecodings(const string &encryption)
{
    // store the number of decodings up to each position
    vector<int> D(10000);
    D[0] = 1; // only one digit, one way to decode

    // two digit number
    if (validNumber(encryption.substr(0, 2)))
    {
        D[1]++;
    }
    // one digit number
    if (encryption[1] != '0')
        D[1]++;

    // three or more digits
    for (int i = 2; i < encryption.size(); i++)
    {
        // if the last two characters form a number between 10 and 26 then add the number of decodings from two characters back
        if (validNumber(encryption.substr(i - 1, 2)))
        {
            D[i] += D[i - 2];
        }
        // add the number of decodings from one character back
        if (encryption[i] != '0')
            D[i] += D[i - 1];
    }

    // the last element gives the result for the full string
    return D[encryption.size() - 1];
}

int main()
{
    int sets = 4;
    for (int i = 0; i < sets; i++)
    {
        string encryption;
        cout << "Input an encrypted number: ";
        cin >> encryption;
        if (encryption == "0")
            break;
        cout << numPossibleDecodings(encryption) << endl;
    }

    /*
    25114 -- 6
    1111111111 -- 89 (ten 1s)
    3333333333 -- 1 (ten 3s)
    0 -- END
    */

    return 0;
}