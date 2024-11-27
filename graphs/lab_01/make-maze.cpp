// www.spoj.com/problems/MAKEMAZE/

#include <iostream>
#include <vector>
using namespace std;

class Graph
{
    int rows, columns;

    void DFS(pair<int, int> source);

public:
    pair<int, int> entry;
    pair<int, int> exit;
    bool foundEntry, foundExit;
    vector<vector<bool>> visitedDFS;

    vector<vector<char>> maze;
    Graph(int r, int c) : rows(r), columns(c)
    {
        maze.resize(r, vector<char>(c));
        visitedDFS.resize(r, vector<bool>(c, false));
        foundEntry = false;
        foundExit = false;
    }

    bool exactlyTwoOpenings();
    bool hasFeasiblePath();

    bool isValid()
    {
        if (!exactlyTwoOpenings())
            return false;
        return hasFeasiblePath();
    }
};

// rows*columns chars in total, the border should contain exactly two "." chars, so subtract the total "." chars by inner "." chars
bool Graph::exactlyTwoOpenings()
{
    int totalDots = 0;
    int innerDots = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (maze[i][j] == '#')
                continue;
            if (maze[i][j] == '.')
                totalDots++;
            if (maze[i][j] == '.' && i > 0 && i < rows - 1 && j > 0 && j < columns - 1)
                innerDots++;

            // borders
            if ((i == 0 || i == rows - 1 || j == 0 || j == columns - 1) && maze[i][j] == '.')
            {
                if (!foundEntry)
                {
                    entry = make_pair(i, j);
                    foundEntry=true;
                    cout << "entry: " << entry.first << " " << entry.second << endl;
                }
                else if (!foundExit)
                {
                    exit = make_pair(i, j);
                    foundExit=true;
                    cout << "exit: " << exit.first << " " << exit.second << endl;
                }
            }
        }
    }
    return (totalDots - innerDots) == 2;
}

void Graph::DFS(pair<int, int> node)
{
    // populate visitedDFS vector
    // two nodes in a matrix are "connected" - have an edge between them if both are "." char
    visitedDFS[node.first][node.second] = true;
    cout << "(" << node.first << "," << node.second << ")" << endl;

    // construct neighbours
    vector<pair<int, int>> neighbours;
    vector<vector<int>> directions =
        {
            {-1, 0}, // left
            {1, 0},  // right
            {0, -1}, // up
            {0, 1}   // down
        };
    for (auto d : directions)
    {
        // construct a neighbour pair and check if valid
        int newRow = node.first + d[0];
        int newCol = node.second + d[1];

        // chech if legal
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns && maze[newRow][newCol] == '.')
        {
            pair<int, int> neighbour = make_pair(newRow, newCol);

            // visit neighbour if not visited and run dfs on it
            if (!visitedDFS[neighbour.first][neighbour.second])
            {
                DFS(neighbour);
            }
        }
    }
}

/*
use dfs to determine reachability from source to destination
*/
bool Graph::hasFeasiblePath()
{
    DFS(entry);
    // we read from the visitedDFS vector whether our destination was visited
    return visitedDFS[exit.first][exit.second];
}

int main()
{
    int rows, columns;
    cout << "Enter rows and columns (from 1 up to 20): ";
    cin >> rows >> columns;
    Graph g(rows, columns);

    cout << "Describe the maze: # is a wall, . is space." << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            cin >> g.maze[i][j];
    }

    bool result = g.isValid();
    if (result)
        cout << "Valid!" << endl;
    else
        cout << "Invalid!" << endl;

    return 0;
}

/*
Example

4 4
####
#...
#.##
#.##
VALID

5 5
#.###
#..##
##..#
#.#.#
###.#
VALID

1 1
.
INVALID

5 1
#
#
.
.
#
VALID

2 2
#.
.#
INVALID

3 4
#..#
#.##
#.##
INVALID
*/
