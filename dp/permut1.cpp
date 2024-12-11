/*
Let A = [a1, a2, ... an] be a permutation of integers 1, 2, ... n.
A pair of indices (i, numInv), 1 <= i <= numInv <= n, is an inversion of the
permutation A if ai > aj. We are given integers n > 0 and k >= 0.
What is the number of n-element permutations containing exactly k inversions?

For instance, the number of 4-element permutations with exactly 1 inversion equals 3.

n=1 ... no result for any k

n=2 k=0 ... result = 1
n=2 k=1 ... result = 1
n=2 k>=2 ... no result

n=3 k=0 ... result = 1 ... 123
n=3 k=1 ... result = 2 ... 132 ... 213
n=3 k=2 ... result = 2 ... 312 ... 231
n=3 k=3 ... result = 1 ... 321
n=3 k>=4 ... no result

n=4 k=0 ... result = 1 ... 1234
n=4 k=1 ... result = 3 ... 1243, 1324, 2134
n=4 k=2 ... result = 3 ... 1423, 3124, 2314, 2143, 1342
n=4 k=3 ... result = 4 ... 3214, 3142, 2341, 1432, 2413, 4123
n=4 k=4 ... result = 3 ... 3241, 3412, 4132, 2431, 4213
n=4 k=5 ... result = 1 ... 4312, 3421, 4231
n=4 k=6 ... result = 1 ... 4321
n=4 k>=7 ... no result

n=7 k=2 ... answer is 20
n=7 k=3 ... answer is 49
n=8 k=3 ... answer is 76

n=4 k=3
... za n=3 k=3 imamo 321
dodamo 4 na kraj i ne mijenja se broj inverzija 3214
... za n=3 k=2 imamo 312, 231 i trebamo staviti negdje 4 tako da doda jednu inverziju
3142, 2341
... za n=3 k=1 imamo 132, 213 - trebamo dodavanjem 4 dobiti jos dvije inverzije
1432, 2413
... za n=3 k=0 imamo 123 - trebamo dodavanjem 4 dobiti 3 inverzije
4123
.. sve zajedno 3214, 3142, 2341, 1432, 2413, 4123

When n increases, n can be placed in positions 0 through n−1,
and each position introduces i additional inversions (where i ranges from 0 to n−1).

Placing the i-th element at position 0 introduces i-1 inversions.
Placing it at position 1 introduces i-2 inversions.
...
Placing it at position i-1 introduces 0 inversions.

*/

#include <iostream>
#include <vector>

using namespace std;

int permut1(int n, int k)
{
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

    // there is exactly one permutation with 0 inversions for any n (sorted order)
    for (int i = 1; i <= n; i++)
        dp[i][0] = 1;


     // Iterate over the size of the permutation
    for (int i = 2; i <= n; ++i)
        for (int numInv = 0; numInv <= k; ++numInv)
        {   
             // start with the value from the previous row
            dp[i][numInv] = dp[i - 1][numInv];

            // accumulates all values where fewer inversions are needed
            // from the left (in our matrix)
            if (numInv > 0)
                dp[i][numInv] += dp[i][numInv - 1];

            // these are permutations where the number of inversions exceeds the maximum allowed when placing the i-th element
            if (numInv >= i)
                dp[i][numInv] -= dp[i - 1][numInv - i];
        }

    return dp[n][k];
}

int main()
{
    int n, k;
    while (true)
    {
        cout << "n k = ";
        cin >> n >> k;
        if (n <= 0)
            break;
        cout << "Result = " << permut1(n, k) << endl;
    }
    return 0;
}