#include <iostream>
#include <vector>
using namespace std;

class Maze
{
private:
    int numRows;
    int numCols;
    vector<vector<char>> description;
    pair<int, int> firstOpening, secondOpening;
    // matrix of visited fields
    vector<vector<bool>> visitedFields;
    bool isValidMove(int, int);
    void DFS(int, int);

public:
    Maze(int, int);
    void writeField(int i, int j, char c)
    {
        description[i][j] = c;
    }
    bool isValid();
    void findOpenings();
    bool existsPath(const pair<int, int> &, const pair<int, int> &);
    void printCoord(pair<int, int> field)
    {
        cout << "(" << field.first << ", " << field.second << ")" << endl;
    }
};

Maze::Maze(int r, int c) : numRows(r), numCols(c)
{
    description.resize(r, vector<char>(c));
    firstOpening = make_pair(-1, -1);
    secondOpening = make_pair(-1, -1);
    visitedFields.resize(r);
    for (int i = 0; i < r; i++)
        visitedFields[i].resize(c, false);
}

void Maze::findOpenings()
{
    int row = 0;
    for (int i = 0; i < numCols; i++)
        if (description[row][i] == '.')
        {
            if (firstOpening == make_pair(-1, -1))
                firstOpening = make_pair(row, i);
            else if (secondOpening == make_pair(-1, -1))
            {
                secondOpening = make_pair(row, i);
                // that's it
                return;
            }
        }

    row = numRows - 1;
    for (int i = 0; i < numCols; i++)
        if (description[row][i] == '.')
        {
            if (firstOpening == make_pair(-1, -1))
                firstOpening = make_pair(row, i);
            else if (secondOpening == make_pair(-1, -1))
            {
                secondOpening = make_pair(row, i);
                // that's it
                return;
            }
        }

    int col = 0;
    for (int i = 0; i < numRows; i++)
        if (description[i][col] == '.')
        {
            if (firstOpening == make_pair(-1, -1))
                firstOpening = make_pair(i, col);
            else if (secondOpening == make_pair(-1, -1))
            {
                secondOpening = make_pair(i, col);
                // that's it
                return;
            }
        }

    col = numCols - 1;
    for (int i = 0; i < numRows; i++)
        if (description[i][col] == '.')
        {
            if (firstOpening == make_pair(-1, -1))
                firstOpening = make_pair(i, col);
            else if (secondOpening == make_pair(-1, -1))
            {
                secondOpening = make_pair(i, col);
                // that's it
                return;
            }
        }
}

bool Maze::isValidMove(int row, int col)
{
    if (row >= 0 && row < numRows && col >= 0 && col < numCols && description[row][col] == '.')
        return true;
    return false;
}

void Maze::DFS(int startRow, int startCol)
{
    visitedFields[startRow][startCol] = true;
    if (startRow == secondOpening.first &&
        startCol == secondOpening.second)
        return;

    // move to neighbours and continue dfs recursively
    int rowMoves[] = {-1, 1, 0, 0};
    int colMoves[] = {0, 0, -1, 1};

    // for each move create a destination field and check if valid
    for (int i = 0; i < 4; i++)
    {
        int newRow = startRow + rowMoves[i];
        int newCol = startCol + colMoves[i];
        pair<int, int> destinationField(make_pair(newRow, newCol));
        if (isValidMove(newRow, newCol) && !visitedFields[newRow][newCol])
        {
            // continue dfs from here
            DFS(newRow, newCol);
            // this dfs returns if reached second opening
        }
    }
}

// undirected graph, determine connectivity, dfs traversal
bool Maze::existsPath(const pair<int, int> &firstOpening, const pair<int, int> &secondOpening)
{
    DFS(firstOpening.first, firstOpening.second);
    if (visitedFields[secondOpening.first][secondOpening.second])
        return true;
    return false;
}

/*
has exactly one entry point and exactly one exit point
(exactly 2 openings in the edges) and there must be
at least one path from the entry point to exit point.
*/
bool Maze::isValid()
{
    int totalDots = 0;
    int innerDots = 0;

    for (int i = 0; i < numRows; i++)
        for (int j = 0; j < numCols; j++)
            if (description[i][j] == '.')
            {
                totalDots++;
                if (i > 0 && i < (numRows - 1) && j > 0 && j < (numCols - 1))
                    innerDots++;
            }

    bool exactlyTwoOpenings = ((totalDots - innerDots) == 2);
    if (!exactlyTwoOpenings)
        return false;

    findOpenings();
    cout << "First opening: ";
    printCoord(firstOpening);
    cout << "Second opening: ";
    printCoord(secondOpening);
    return existsPath(firstOpening, secondOpening);
}

int main()
{
    int testCases; // (1,10000)
    cout << "Number of test cases (from 1 up to 10000): ";
    cin >> testCases;
    for (int i = 0; i < testCases; i++)
    {
        int rows, cols; // (1,20)
        cout << "Number of rows and columns (from 1 up to 20): ";
        cin >> rows >> cols;
        Maze maze(rows, cols);

        cout << "Describe the maze: # is a wall, . is space.\n";
        for (int j = 0; j < rows; j++)
            for (int k = 0; k < cols; k++)
            {
                char c;
                cin >> c;
                maze.writeField(j, k, c);
            }

        if (maze.isValid())
            cout << "Valid!" << endl;
        else
            cout << "Invalid!" << endl;
    }
    return 0;
}

/*
test cases: 6

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
