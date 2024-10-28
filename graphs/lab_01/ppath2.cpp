/*
- going from 1033 to 8179 by a path of prime numbers where only one digit is changed from one prime to the next prime
- the price of a digit is one pound
- find the cheapest prime path between any two given four-digit primes

EXAMPLE FROM 1033 TO 8179
1033
1733
3733
3739
3779
8779
8179
- The cost of this solution is 6 pounds.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <queue> // for bfs
#include <unordered_map>
using namespace std;

bool isPrime(int p)
{
    if (p <= 1)
        return false;
    if (p == 2)
        return true;
    for (int i = 2; i <= sqrt(p); i++)
        if (p % i == 0)
            return false;
    return true;
}

vector<string> getPrimeNeighbours(const string &p)
{
    vector<string> result;
    // for all 4 digits...
    for (size_t i = 0; i < p.size(); i++)
    {
        char digitForChange = p[i];
        for (char newDigit = '0'; newDigit <= '9'; newDigit++)
        {
            if (newDigit == digitForChange)
                continue;
            // create a new number
            string p_copy = p;
            p_copy[i] = newDigit;
            // we have to check p_copy>=1000 first in case we have 0 as the first digit
            int p_copy_int = stoi(p_copy);
            if (p_copy_int >= 1000 && isPrime(p_copy_int))
            {
                result.push_back(p_copy);
            }
        }
    }
    return result;
}

// F - first, S - second
void doubleBFS(const string &firstPrime, const string &secondPrime, int &distance)
{
    // so we can index with string, also tracking distance
    unordered_map<string, int> visitedF;
    visitedF[firstPrime] = 0; // distance to itself is 0
    unordered_map<string, int> visitedS;
    visitedS[secondPrime] = 0;

    // we check nodes from these queues not until they empty out
    // but until we find matching nodes
    queue<string> visitingQueueF;
    visitingQueueF.push(firstPrime);
    queue<string> visitingQueueS;
    visitingQueueS.push(secondPrime);

    while (true)
    {
        string currentNodeF = visitingQueueF.front();
        visitingQueueF.pop();
        vector<string> neighboursF = getPrimeNeighbours(currentNodeF);
        for (string n : neighboursF)
        {
            if (visitedF.find(n) != visitedF.end())
                continue; // visited
            if (visitedS.find(n) != visitedS.end())
            {
                // we have a match!
                int distanceFromFirst = visitedF[currentNodeF]+1;
                int distanceFromSecond = visitedS[n];
                distance = distanceFromFirst + distanceFromSecond;
                return;
            }
            // not visited, not a match, add to queue
            visitingQueueF.push(n);
            visitedF[n] = visitedF[currentNodeF] + 1;
        }

        string currentNodeS = visitingQueueS.front();
        visitingQueueS.pop();

        vector<string> neighboursS = getPrimeNeighbours(currentNodeS);
        for (string n : neighboursS)
        {
            if (visitedS.find(n) != visitedS.end())
                continue; // visited
            if (visitedF.find(n) != visitedF.end())
            {
                // we have a match!
                int distanceFromFirst = visitedF[n];
                int distanceFromSecond = visitedS[currentNodeS]+1;
                distance = distanceFromFirst + distanceFromSecond;
                return;
            }
            // not visited, not a match, add to queue
            visitingQueueS.push(n);
            visitedS[n] = visitedS[currentNodeS] + 1;
        }
    }
}

int cheapestPrimePath(int first, int second)
{
    int distance;
    doubleBFS(to_string(first), to_string(second), distance);
    return distance;
}

int main()
{
    int firstPrime = 1033;
    int secondPrime = 8179;
    cout << "The cheapest prime path: ";
    int result = cheapestPrimePath(firstPrime, secondPrime);
    cout << result << endl;
    vector<string> primeNeighbours = getPrimeNeighbours("501");
    for (string s : primeNeighbours)
        cout << s << endl;
    return 0;
}
