/*
Certain positive integers have their decimal representation consisting only of ones and zeros,
and having at least one digit one, e.g. 101. If a positive integer does not have such a
property, one can try to multiply it by some positive integer to find out whether the product has this property...

Nosed are positive integers with such property.
1 is root with children 10 and 11
10 has children 100 and 101
11 has children 110 and 111
We do BFS on those nodes.
For each node we check whether it is a multiple of n.
Treat number as strings first.
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isMultiple(string num, int n)
{
    int numInt = stoi(num);
    return (numInt % n) == 0;
}

vector<string> generateNeighbours(const string &num)
{
    vector<string> neighbours;
    neighbours.push_back(num + "1");
    neighbours.push_back(num + "0");
    return neighbours;
}

int smallestMultiple(int n)
{
    queue<string> visitingQueue;
    visitingQueue.push("1");

    while (true)
    {
        string currentNode = visitingQueue.front();
        vector<string> neighbours = generateNeighbours(currentNode);
        for (string neighbour : neighbours)
        {
            if (isMultiple(neighbour, n))
                return stoi(neighbour);
            visitingQueue.push(neighbour);
        }
        visitingQueue.pop();
    }
}

int main()
{
    int testCases;
    cout << "Number of test cases: ";
    cin >> testCases;
    for (int i = 0; i < testCases; i++)
    {
        int n;
        cout << "Input n: ";
        cin >> n;
        cout << "Smallest multiple of " << n << " consisting only of digits 1 and 0 is " << smallestMultiple(n) << endl;
    }
    return 0;
}