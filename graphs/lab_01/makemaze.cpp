/*
A valid maze has exactly one entry point and exactly one exit point
(exactly 2 openings in the edges) and there must be at least one
path from the entry point to exit point.

For each test case find whether the maze is "valid" or "invalid".
*/

#include <iostream>
#include <vector>
using namespace std;

bool exactlyTwoOpenings(const vector<vector<char>> &maze)
{
    // calculate the number of dots in the edges
    int numRows = maze.size();
    int numCols = maze[0].size();

    // edge cases

    if (numRows == 1)
    {
        int dots = 0;
        for (int i = 0; i < numCols; i++)
        {
            if (maze[0][i] == '.')
                dots++;
            if (dots > 2)
                return false;
        }
        if (dots < 2)
            return false;
        return true;
    }

    if (numCols == 1)
    {
        int dots = 0;
        for (int i = 0; i < numRows; i++)
        {
            if (maze[i][0] == '.')
                dots++;
            if (dots > 2)
                return false;
        }
        if (dots < 2)
            return false;
        return true;
    }

    // subtract total dots and inner dots
    int total_dots = 0;
    int inner_dots = 0;
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            if (maze[i][j] == '.')
                total_dots++;
        }
    }
    for (int i = 1; i < numRows - 1; i++)
    {
        for (int j = 1; j < numCols - 1; j++)
        {
            if (maze[i][j] == '.')
                inner_dots++;
        }
    }

    return ((total_dots - inner_dots) == 2);
}

void findOpenings(const vector<vector<char>> &maze, int &entryRow, int &entryCol, int &exitRow, int &exitCol)
{
    bool foundEntry = false;
    bool foundExit = false;
    int numRows = maze.size();
    int numCols = maze[0].size();

    // first row
    for (int i = 0; i < numCols; i++)
    {
        if (maze[0][i] == '.')
        {
            if (!foundEntry)
            {
                entryCol = i;
                entryRow = 0;
                foundEntry = true;
                cout << "Entry: " << entryRow << " " << entryCol << endl;
            }
            else
            {
                exitCol = i;
                exitRow = 0;
                foundExit = true;
                cout << "Exit: " << exitRow << " " << exitCol << endl;
                return;
            }
        }
    }

    // last row
    for (int i = 0; i < numCols; i++)
    {
        if (maze[numRows - 1][i] == '.')
        {
            if (!foundEntry)
            {
                entryCol = i;
                entryRow = numRows - 1;
                foundEntry = true;
                cout << "Entry: " << entryRow << " " << entryCol << endl;
            }
            else
            {
                exitCol = i;
                exitRow = numRows - 1;
                foundExit = true;
                cout << "Exit: " << exitRow << " " << exitCol << endl;
                return;
            }
        }
    }

    // first column
    for (int i = 0; i < numRows; i++)
    {
        if (maze[i][0] == '.')
        {
            if (!foundEntry)
            {
                entryCol = 0;
                entryRow = i;
                foundEntry = true;
                cout << "Entry: " << entryRow << " " << entryCol << endl;
            }
            else
            {
                exitCol = 0;
                exitRow = i;
                foundExit = true;
                cout << "Exit: " << exitRow << " " << exitCol << endl;
                return;
            }
        }
    }

    // last column
    for (int i = 0; i < numRows; i++)
    {
        if (maze[i][numCols - 1] == '.')
        {
            if (!foundEntry)
            {
                entryCol = numCols - 1;
                entryRow = i;
                foundEntry = true;
                cout << "Entry: " << entryRow << " " << entryCol << endl;
            }
            else
            {
                exitCol = numCols - 1;
                exitRow = i;
                foundExit = true;
                cout << "Exit: " << exitRow << " " << exitCol << endl;
                return;
            }
        }
    }
}

bool isValidMove(int row, int col, const vector<vector<char>> &maze, vector<vector<bool>> &visited)
{
    int numRows = maze.size();
    int numCols = maze[0].size();

    // Check if the move is within bounds, not a wall, and not visited yet
    return row >= 0 && row < numRows && col >= 0 && col < numCols && maze[row][col] == '.' && !visited[row][col];
}

bool DFS(const vector<vector<char>> &maze, int startRow, int startCol, int targetRow, int targetCol, vector<vector<bool>> &visited)
{
    // If the current cell is the exit, return true
    if (startRow == targetRow && startCol == targetCol)
    {
        return true;
    }

    // Mark the current cell as visited
    visited[startRow][startCol] = true;

    // Define possible moves (up, down, left, right)
    int rowMoves[] = {-1, 1, 0, 0};
    int colMoves[] = {0, 0, -1, 1};

    // Explore all four possible directions
    for (int i = 0; i < 4; i++)
    {
        int newRow = startRow + rowMoves[i];
        int newCol = startCol + colMoves[i];

        // If the new move is valid, continue DFS from that cell
        if (isValidMove(newRow, newCol, maze, visited))
        {
            if (DFS(maze, newRow, newCol, targetRow, targetCol, visited))
            {
                return true;
            }
        }
    }

    // If no path is found from this cell, backtrack (DFS fails)
    return false;
}

bool hasFeasiblePath(const vector<vector<char>> &maze)
{
    int entryRow, entryCol, exitRow, exitCol;
    findOpenings(maze, entryRow, entryCol, exitRow, exitCol);

    // Initialize the visited array to keep track of explored cells
    vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), false));

    // Perform DFS from the entry point to the exit point
    return DFS(maze, entryRow, entryCol, exitRow, exitCol, visited);
}

bool isValid(const vector<vector<char>> &maze)
{
    // check exactly two openings
    bool firstCondition = exactlyTwoOpenings(maze);

    // Check that there exists at least one feasible path
    if (!firstCondition)
    {
        return false;
    }

    // check there exists at least one feasible path
    bool secondCondition = hasFeasiblePath(maze);

    return secondCondition;
}

int main()
{
    int testCases; // (1,10000)
    cout << "Number of test cases (from 1 up to 10000): ";
    cin >> testCases;
    for (int i = 0; i < testCases; i++)
    {
        int rows, columns; // (1,20)
        cout << "Number of rows and columns (from 1 up to 20): ";
        cin >> rows >> columns;

        cout << "Describe the maze: # is a wall, . is space." << endl;
        vector<vector<char>> maze(rows, vector<char>(columns));
        for (int j = 0; j < rows; j++)
        {
            for (int k = 0; k < columns; k++)
            {
                cin >> maze[j][k];
            }
        }
        bool result = isValid(maze);
        if (result)
            cout << "Valid!" << endl;
        else
            cout << "Invalid!" << endl;
    }

    return 0;
}

/*
Example

Input:
6

4 4
####
#...
#.##
#.##

5 5
#.###
#..##
##..#
#.#.#
###.#

1 1
.

5 1
#
#
.
.
#

2 2
#.
.#

3 4
#..#
#.##
#.##

Output:

valid
valid
invalid
valid
invalid
invalid
*/
