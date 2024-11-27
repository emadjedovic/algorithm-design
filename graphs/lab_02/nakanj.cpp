//  www.spoj.com/problems/NAKANJ/

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

bool outOfBoard(const string &destination)
{
    if (destination[0] < 'a' || destination[0] > 'h')
        return true;
    if (destination[1] < '1' || destination[1] > '8')
        return true;
    return false;
}

// al the fields the knight can move to
vector<string> getNeighbours(const string &position)
{
    vector<string> result;

    // (2,-1) means two steps right, one step down
    vector<pair<int, int>> moves = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

    // for each move create a string destination
    for (const auto &move : moves)
    {
        string destination = position; // move from here
        destination[0] += move.first;
        destination[1] += move.second;

        // if not visited and stays on the board then add to neighbours
        if (!outOfBoard(destination))
            result.push_back(destination);
    }

    return result;
}

void doubleBFS(const string &start, const string &destination, int &levelFromStart, int &levelFromDestination)
{
    // position (string) and distance (int)
    queue<pair<string, int>> bfsStart;
    queue<pair<string, int>> bfsDest;
    bfsStart.push({start, 0});
    bfsDest.push({destination, 0});

    unordered_map<string, bool> visitedStart;
    unordered_map<string, bool> visitedDest;
    visitedStart[start] = true;
    visitedDest[destination] = true;

    while (!bfsStart.empty() && !bfsDest.empty())
    {
        string currentNodeS = bfsStart.front().first;
        int currentDistanceS = bfsStart.front().second;
        bfsStart.pop();

        vector<string> neighboursS = getNeighbours(currentNodeS);
        for (const string &n : neighboursS)
        {
            levelFromStart = currentDistanceS + 1;
            if (visitedDest[n])
            {
                // collision with nodes from destination bfs
                cout << "Collided at: " << n << endl;
                return;
            }
            bfsStart.push({n, levelFromStart});
            visitedStart[n] = true;
        }

        string currentNodeD = bfsDest.front().first;
        int currentDistanceD = bfsDest.front().second;
        bfsDest.pop();

        vector<string> neighboursD = getNeighbours(currentNodeD);

        for (const string &n : neighboursD)
        {
            levelFromDestination = currentDistanceD + 1;
            if (visitedStart[n])
            {
                // collision with nodes from start bfs
                cout << "Collided at: " << n << endl;
                return;
            }
            bfsDest.push({n, levelFromDestination});
            visitedDest[n] = true;
        }
    }
}

int minKnightMoves(string start, string destination)
{
    if (start == destination)
        return 0;
    int levelFromStart = 0;
    int levelFromDestination = 0;
    doubleBFS(start, destination, levelFromStart, levelFromDestination);
    return levelFromStart + levelFromDestination;
}

int main()
{
    int T; // 1<=T<=4096
    cout << "Test cases: ";
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        string start, destination;
        cout << "Input start and destination (from a1 to h8): ";
        cin >> start >> destination;
        cout << "Minimal number of knight moves required: " << minKnightMoves(start, destination) << endl;
    }
    return 0;
}
