/*
A derangement is a permutation p of {1,...,n} such that no
item is in its proper position, i.e. pi != i for all 1≤i≤n.
Write an efficient backtracking program with pruning that
constructs all the derangements of n items
*/

#include <iostream>
#define MAX_CANDIDATES 100000
#define NMAX 100000

bool is_a_solution(int a[], int k, int n)
{
    return k==n;
}

void process_solution(int a[], int k, int n)
{
    for(int i=0; i<k; i++)
    {
        std::cout<<a[i]<<" ";
    }

    std::cout<<std::endl;

}

// each element ai is a number from 1 to n, which has not yet appeared in previous positions
// that is {1,2,...,n} - {some k used numbers}
void construct_candidates(int a[], int k, int n, int c[], int* ncandidates)
{
    // initialize an array to track the elements that are already used
    int in_perm[NMAX];
    for(int i=0; i<NMAX; i++) in_perm[i] = false;
    for(int i=0; i<k; i++){
        int element = a[i];
        in_perm[element] = true;
    }

    *ncandidates = 0;
    for(int i=0; i<n; i++)
    {
        if(in_perm[i]==false)
        {
            c[*ncandidates]=a[i];
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