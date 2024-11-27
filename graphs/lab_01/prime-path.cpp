/*
www.spoj.com/problems/PPATH/

- nodes are 4-digit prime numbers
- two nodes are connected (exists an unweighted undirected edge between them) if they differ in exactly one digit
- form a graph and use bfs (layer by layer) to find the shortest path between start and target prime
- start double bfs, one from start prime and one from
- once the common node is reached we should sum the two numbers to get the total distance
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

bool isPrime(int n)
{
    if (n == 1)
        return false;
    if (n == 2)
        return true;
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

vector<int> getPrimeNeighbours(const int &prime)
{
    vector<int> result;

    // change exactly one digit, check if prime
    string primeString = to_string(prime);
    int length = primeString.length();

    for (int i = 0; i < length; i++)
    {
        char c = primeString[i];
        // change this char
        for (char new_c = '0'; new_c <= '9'; new_c++)
        {
            if (new_c == c)
                continue; // same digit
            if (i == 0 && new_c == '0')
                continue; // first digit
            string newPrime = primeString;
            newPrime[i] = new_c;
            int newPrimeInt = stoi(newPrime);
            if (isPrime(newPrimeInt))
            {
                result.push_back(newPrimeInt);
            }
        }
    }

    return result;
}

int cheapestPrimePath(int firstPrime, int secondPrime)
{
    if (firstPrime == secondPrime)
        return 0;

    vector<int> primeDistance;
    primeDistance.resize(10000000, -1); // hopefully enough for all the nodes
    primeDistance[firstPrime] = 0;

    queue<int> q;
    vector<int> queued(10000000, false);
    q.push(firstPrime);
    queued[firstPrime] = true;

    while (!q.empty())
    {
        int currentPrime = q.front();
        q.pop();

        vector<int> neighbours = getPrimeNeighbours(currentPrime);
        for (int neighbour : neighbours)
        {
            if (!queued[neighbour])
            {
                q.push(neighbour);
                queued[neighbour] = true;
                int layer = primeDistance[currentPrime] + 1;
                if (neighbour == secondPrime)
                {
                    return layer;
                }
                primeDistance[neighbour] = layer;
            }
        }
    }

    return -1; // second prime not found
}

int main()
{
    int firstPrime = 1033;
    int secondPrime = 1033;
    int result = cheapestPrimePath(firstPrime, secondPrime);
    cout << "The cheapest prime path: " << result << endl;
    return 0;
}

/*
1033 8179 -- 6
1373 8017 -- 7
1033 1033 -- 0
*/