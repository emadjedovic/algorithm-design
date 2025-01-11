/*
positioning of eight queens on an 8 × 8 chessboard
such that no two queens threaten each other
*/

#include <iostream>
#define MAX_CANDIDATES INT32_MAX;
#define NMAX INT32_MAX;

// no two queens can occupy the same column/row
// we deal with a conditioned permutation of n elements

bool is_a_solution(int a[], int k, int n)
{
    return k==n;
}

int solution_count = 0;

//let's just count the number of solutions
void process_solution(int a[], int k, int n)
{
    solution_count++;
}

// is the kth square on the given column threated by any previously positioned queens?
// if yes then we don't include that square in our list of candidates
void construct_candidates(int a[], int k, int n, int c[], int* ncandidates)
{
    // constructing candidates for kth row
    bool legal_move;
    *ncandidates = 0;
    // row by row
    for(int i=0; i<n; i++)
    {
        legal_move = true;
        // check previous columns
        for(int j=0; j<k; j++)
        {
            int queen_row = a[j];

            // diagonal threat
            if(abs(i-queen_row)==abs(j-k)){
                // equal height and width
                legal_move = false;
            }

            // row threat
            if(i==queen_row)
            legal_move = false;

        }
        
        if(legal_move)
        {
            c[*ncandidates]=i; // ith row is a legal option in kth column
            *ncandidates++;
        }
    }

}

void backtrack(int a[], int k, int n)
{
    int c[MAX_CANDIDATES];
    int ncandidates;

    if(is_a_solution(a,k,n))
    {
        process_solution(a,k,n);
    } else {
        k = k+1;
        construct_candidates(a,k,n,c,&ncandidates);
        for(int i=0; i<ncandidates; i++)
        {
            a[k]=c[i];
            backtrack(a,k,n);
        }
    }

}

void nqueens(int n)
{
    int a[NMAX]; // solution vector
    backtrack(a, 0, n);
}

int main()
{
    // 365,596 solutions for n = 14
    nqueens(5);
    return 0;
}