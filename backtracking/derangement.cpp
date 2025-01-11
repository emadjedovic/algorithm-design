/*
A derangement is a permutation p of {1,...,n} such that no
item is in its proper position, i.e. pi != i for all 1≤i≤n.
Write an efficient backtracking program with pruning that
constructs all the derangements of n items
*/

#include <iostream>
#define MAX_CANDIDATES 10000
#define NMAX 10000

bool is_a_solution(int a[], int k, int n)
{
    return k == n;
}

void process_solution(int a[], int k, int n)
{
    for (int i = 0; i < k; i++)
    {
        std::cout << a[i] << " ";
    }

    std::cout << std::endl;
}

// that is {1,2,...,n} - {kth element - some k-1 used numbers}
void construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
    // initialize an array to track the elements that are already used
    bool in_perm[NMAX];
    for (int i = 0; i < n; i++)
        in_perm[i] = false;
    for (int i = 0; i < k; i++)
    {
        int element = a[i];
        in_perm[element] = true;
    }

    *ncandidates = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == k)
            continue;
        if (in_perm[i] == false)
        {
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

void generate_derangements(int n)
{
    int a[NMAX]; // solution vector
    backtrack(a, 0, n);
}

int main()
{
    generate_derangements(5);
    return 0;
}