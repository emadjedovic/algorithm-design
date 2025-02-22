#define MAX_CANDIDATES 100000

bool finished = false; // found all solutions yet?

// tests whether the first k elements of an array a is a complete solution
bool is_a_solution(int a[], int k, int input)
{
    // k==n for example
    return true;
}

void process_solution(int a[], int k, int input)
{
    // do something, print, count, or other
    return;
}

// fills an array c with all possible candidates for kth position of a array given the contents of the first k-1 positions
// store the number of candidates in "ncandidates" location
void construct_candidates(int a[], int k, int input, int c[], int *ncandidates)
{
    // specialized logic
    return;
}

void backtrack(int a[], int k, int input)
{
    // construct_candidates method fills c and ncandidates
    int c[MAX_CANDIDATES]; // candidates for the next position
    int ncandidates;       // next position candidate count

    if (is_a_solution(a, k, input))
    {
        process_solution(a, k, input);
    }
    else
    {
        k++; // move to next position
        construct_candidates(a, k, input, c, &ncandidates);
        // traverse through all candidates
        for (int i = 0; i < ncandidates; i++)
        {
            a[k] = c[i]; // add candidate c[i] to the kth position of the current solution
            backtrack(a, k, input);
            if (finished)
                return; // terminate early
        }
    }
}
