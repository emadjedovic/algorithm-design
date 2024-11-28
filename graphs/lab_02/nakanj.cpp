// www.spoj.com/problems/NAKANJ/

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

// input start and destination
// output minimal number of moves required

bool outOfBoard(const string &position)
{
    // from a1 to h8
    char letter = position[0];
    char number = position[1];
    if (number < '1' || number > '8' || letter > 'h' || letter < 'a')
        return true;
    return false;
}

vector<string> generateNeighbours(const string &position)
{
    vector<string> result;

    // two up, one left/right
    // two down, one left/right
    // two right, one up/down
    // two left, one up/down

    vector<vector<int>> moves =
        {
            {-2, -1},
            {-2, 1},
            {2, -1},
            {2, 1},
            {1, -2},
            {-1, -2},
            {1, 2},
            {-1, 2}};

    for (auto move : moves)
    {
        string newPosition = position;
        newPosition[0] += move[0];
        newPosition[1] += move[1];
        if (!outOfBoard(newPosition))
            result.push_back(newPosition);
    };

    return result;
}

int minKnightMoves(string start, string dest)
{
    if (start == dest)
        return 0;

    // list of legal moves
    // nodes are positions and two nodes are directly connected if our knight can reach that position from current position
    // traverse neighbours until reached destination
    // bfs with layer tracking
    // double bfs for better efficiency

    unordered_map<string, int> movesMade;
    movesMade[start] = 0;

    queue<string> q;
    q.push(start);

    while (true)
    {
        string current = q.front();
        q.pop();

        vector<string> neighbours = generateNeighbours(current);
        for (string n : neighbours)
        {
            if (n == dest)
                return movesMade[current] + 1;
            // if neighbour was already noted in movesMade then skip
            if (movesMade.find(n) != movesMade.end())
            {
                // already visited
                continue;
            }
            q.push(n);
            movesMade[n] = movesMade[current] + 1;
        }
    }
}

int main()
{
    cout << minKnightMoves("a1", "h8") << endl; // 6
    cout << minKnightMoves("a1", "c2") << endl; // 1
    cout << minKnightMoves("h8", "c3") << endl; // 4
    return 0;
}