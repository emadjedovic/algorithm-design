#include <iostream>
#define MAX_CANDIDATES 2
#define NMAX 10000

void process_solution(bool a[], int k, int n)
{
    for (int i = 0; i < k; i++)
    {
        if (a[i] == true)
            std::cout << i+1 << " ";
    }

    std::cout << std::endl;
}

bool is_a_solution(bool a[], int k, int n)
{
    return k == n;
}

// Sk={true, false}
// each ai of vector of solution a is taken from Sk
// that is, each subset solution a has n binary elements which indicate whether we included element i or not
void construct_candidates(bool a[], int k, int n, bool c[], int *ncandidates)
{
    c[0] = true;
    c[1] = false;
    *ncandidates = 2;
}

void backtrack(bool a[], int k, int n)
{
    bool c[MAX_CANDIDATES];
    int ncandidates;
    if (is_a_solution(a, k, n))
    {
        process_solution(a, k, n);
    }
    else
    {
        k = k + 1;
        construct_candidates(a, k, n, c, &ncandidates);
        for (int i = 0; i < ncandidates; i++)
        {
            // k-1 for 0-indexing
            a[k-1] = c[i];
            backtrack(a, k, n);
        }
    }
}

void generate_subsets(int n)
{
    bool a[NMAX] = {false}; // solution vector
    backtrack(a, 0, n);
}

int main()
{
    generate_subsets(4);
    return 0;
}