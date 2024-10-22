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
using namespace std;

/* solve using bfs shortest path*/

bool isPrime(int p)
{
    if (p == 1)
        return false;
    if (p == 2)
        return true;
    for (int i = 2; i <= sqrt(p); i++)
    {
        if (p % i == 0)
            return false;
    }
    return true;
}

// differing in one digit only
vector<int> findPrimeNeighbours(int node)
{
    vector<int> neighbours;
    string nodeStr = to_string(node);
    for (int i = 0; i < 4; i++)
    {
        // save the original digits
        char originalDigit = nodeStr[i];
        // loop over all digits
        for (char newDigit = '0'; newDigit <= '9'; newDigit++)
        {
            if (newDigit == originalDigit)
                continue;
            // new neighbour, convert to int and check if prime
            string newNeighbourStr = nodeStr;
            newNeighbourStr[i] = newDigit;
            int newNeighbour = stoi(newNeighbourStr);
            if (newNeighbour >= 1000 && isPrime(newNeighbour))
            {
                neighbours.push_back(newNeighbour);
            }
        }
    }
    return neighbours;
}

// BFS queue, but checks for targetNode amongst neighbours before continuing to next level
int DistanceFrom(int startNode, int targetNode)
{
    if (startNode == targetNode)
        return 0;

    queue<int> visitingQueue;
    vector<bool> queued(10000, false);
    vector<int> distances(10000, 0);

    visitingQueue.push(startNode);
    queued[startNode] = true;

    while (!visitingQueue.empty())
    {
        int currentNode = visitingQueue.front();
        vector<int> neighbours = findPrimeNeighbours(currentNode);
        for (int neighbour : neighbours)
        {
            if(!queued[neighbour]) {
                distances[neighbour] = distances[currentNode] + 1;
                if (neighbour == targetNode) return distances[neighbour];
                visitingQueue.push(neighbour);
                queued[neighbour] = true;
            }
            
        }

        visitingQueue.pop();
    }
    return -1; // target not found
}

/*
Input:
3
1033 8179
1373 8017
1033 1033

Output:
6
7
0
*/

int main()
{
    cout << "Number of test cases: ";
    int testCases; // at most 100
    cin >> testCases;
    vector<int> results(testCases, 36);
    for (int i = 0; i < testCases; i++)
    {
        /* One line with two numbers separated by a blank. */
        cout << "Old password and the new one: ";
        int first, second; // four-digit primes
        cin >> first >> second;

        // store the results
        results[i] = DistanceFrom(first, second);
    }
    // output the results
    for (int result : results)
    {
        cout << result << endl;
    }

    return 0;
}
