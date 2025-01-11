#include <iostream>
#define MAX_CANDIDATES INT32_MAX;

void process_solution(int a[], int k, int n)
{
    for (int i = 0; i < k; i++)
    {
        if (a[i] == true)
            std::cout << i << " ";
    }

    std::cout << std::endl;
}

bool is_a_solution(int a[], int k, int n)
{
    return k == n;
}

// Sk={true, false}
// each ai of vector of solution a is taken from Sk
// that is, each subset solution a has n binary elements which indicate whether we included element i or not
void construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
    c[0]=true;
    c[1]=false;
    *ncandidates = 2;
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
        k = k + 1;
        construct_candidates(a, k, n, c, &ncandidates);
        for (int i = 0; i < ncandidates; i++)
        {
            a[k] = c[i];
            backtrack(a, k, n);
        }
    }
}

void generate_subsets(int n)
{
    const int NMAX = INT32_MAX;
    int a[NMAX]; // solution vector
    backtrack(a,0,n);
}

int main()
{
    generate_subsets(10);
    return 0;
}