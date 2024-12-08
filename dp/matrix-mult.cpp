#include <iostream>
#include <vector>

using namespace std;

void MatrixMultOrder(int numMatrices, const vector<int> &dims, vector<vector<int>> &N, vector<vector<int>> &T)
{
    // fill diagonal 0s
    for (int i = 0; i < numMatrices; i++)
        N[i][i] = 0;

    for (int length = 2; length <= numMatrices; length++)
    {
        for (int i = 0; i < numMatrices - length + 1; i++)
        {
            int j = i + length - 1; // the ending matrix
            N[i][j] = INT32_MAX;
            // try all possible splits
            for (int k = i; k < j; k++)
            {
                int numMult = N[i][k] + N[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                // we want to find the minimum
                if (numMult < N[i][j])
                {
                    N[i][j] = numMult;
                    T[i][j] = k; // split point
                }
            }
        }
    }
}

void PrintOptimalParenthesis(const vector<vector<int>> &T, int start, int end)
{
    if (start == end)
    {
        cout << "A" << start; // only one matrix
    }
    else
    {
        cout << "(";
        // print left part of the chain
        PrintOptimalParenthesis(T, start, T[start][end]);
        // print right part of the chain
        PrintOptimalParenthesis(T, T[start][end] + 1, end);
        cout << ")";
    }
}

void PrintMatrix(const vector<vector<int>> &matrix)
{
    int n = matrix.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << "\t"; // Print matrix values with tabs for better alignment
        }
        cout << endl;
    }
}

int main()
{
    int numMatrices = 6;
    // A0(30x35), A1(35x15), A2(15x5), A3(5x10), A4(10x20), A5(20x25)
    vector<int> dims = {30, 35, 15, 5, 10, 20, 25};

    // DP matrix, N - minimum number of operations to multiply matrices Ai...Aj
    vector<vector<int>> N(numMatrices, vector<int>(numMatrices));

    // DP matrix, T - the index where we split the matrices between Ai and Aj (the matrix behind which we place the parethesis)
    vector<vector<int>> T(numMatrices, vector<int>(numMatrices));

    // fill the DP tables N and T
    MatrixMultOrder(numMatrices, dims, N, T);

    cout << "N matrix (minimum number of multiplications):" << endl;
    PrintMatrix(N);

    cout << "Minimum number of multiplications: " << N[0][numMatrices - 1] << endl;

    cout << "Optimal parenthesization: ";
    PrintOptimalParenthesis(T, 0, numMatrices - 1);
    cout << endl;

    return 0;
}