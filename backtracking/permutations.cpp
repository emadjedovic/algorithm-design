#include <iostream>
#define MAX_CANDIDATES 10000
#define NMAX 10000

bool is_a_solution(int a[], int k, int n)
{
    return k == n; // reached the end position
}

void process_solution(int a[], int k, int n)
{
    for (int i = 0; i < k; i++)
        std::cout << a[i] << " ";

    std::cout << std::endl;
}

// each element ai is a number from 1 to n, which has not yet appeared in previous positions
// that is {1,2,...,n} - {some k used numbers}
void construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
    // initialize an array to track the elements that are already used
    bool in_perm[NMAX];
    for (int i = 0; i < n; i++)
        in_perm[i] = false;
    // previous k-1 elements of the solution a
    for (int i = 0; i < k; i++)
        in_perm[a[i]] = true;

    *ncandidates = 0;
    for (int i = 0; i < n; i++)
    {
        if (in_perm[i] == false)
        {
            // not in the permutation yet, it's a candidate
            c[*ncandidates] = i;
            (*ncandidates)++;
        }
    }
}

void backtrack(int a[], int k, int n)
{
    int c[MAX_CANDIDATES];
    int ncandidates;

    if (is_a_solution(a, k, n))
    {
        process_solution(a, k, n);
    }
    else
    {
        k++;
        construct_candidates(a, k, n, c, &ncandidates);
        for (int i = 0; i < ncandidates; i++)
        {
            a[k - 1] = c[i];
            backtrack(a, k, n);
        }
    }
}

void generate_permutations(int n)
{
    int a[NMAX]; // solution vector
    backtrack(a, 0, n);
}

int main()
{
    generate_permutations(4);
    return 0;
}
