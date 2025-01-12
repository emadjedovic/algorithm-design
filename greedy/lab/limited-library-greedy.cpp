// https://codeforces.com/gym/105562/problem/L
// the algorithm combines elements of greedy and binary search

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
Find the largest number of shelves on which you can place an art piece,
whilst also being able to fit all the new books on the shelves.
*/

/*
Determines whether it is possible to arrange the books on the shelves while leaving k shelves for art pieces.
*/
bool allBooksFit(const vector<int> &shelfHeights, const vector<int> &bookHeights,
                 int maxNumBooks, int maxNumBooksArt, int k)
{
    // Places the tallest books on the tallest shelves first (greedy).
    int currentShelf = shelfHeights.size() - 1;
    // if currentShelf > k then it is a regular shelf without art
    // shelves <= k have art placed on them

    int numBooksOnCurrentShelf = 0;

    // until no books are left, take the tallest book first
    // (tallest book and current shelf)
    for (int i = bookHeights.size() - 1; i >= 0; i--)
    {
        if (currentShelf == -1 || bookHeights[i] > shelfHeights[currentShelf])
        {
            // -1 we ran out of shelves, the other scenario is that the book does not fit the current shelf
            return false;
        }
        numBooksOnCurrentShelf++;
        // should we hop onto the next shelf?
        if (currentShelf >= k && numBooksOnCurrentShelf == maxNumBooks)
        {
            currentShelf--;
            numBooksOnCurrentShelf = 0;
        }
        else if (currentShelf < k && numBooksOnCurrentShelf == maxNumBooksArt)
        {
            currentShelf--;
            numBooksOnCurrentShelf = 0;
        }
    }
    return true;
}

/*
This function uses binary search to find the maximum number of shelves (k)
that can have art while still allowing all books to be placed on the shelves.
Binary search.
*/
int maxNumArtShelves(const vector<int> &shelfHeights, const vector<int> &bookHeights, int x, int y)
{
    int minK = 0;
    int maxK = shelfHeights.size();
    while (minK < maxK)
    {
        int k = (minK + maxK + 1) / 2;
        if (allBooksFit(shelfHeights, bookHeights, x, y, k))
        {
            // k is a valid candidate, try larger values
            minK = k;
        }
        else
        {
            // try smaller k's
            maxK = k - 1;
        }
    }
    return minK;
}

int main()
{

    // n - the number of shelves
    // m - the number of books
    // x - the number of books that fit on a full shelf
    // y - the number of books that fit on a shelf next to an art piece.
    int n, m, x, y;
    cin >> n >> m >> x >> y;

    // the heights of the shelves
    vector<int> shelfHeights;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        shelfHeights.push_back(a);
    }

    // the heights of the books
    vector<int> bookHeights;
    for (int i = 0; i < m; i++)
    {
        int b;
        cin >> b;
        bookHeights.push_back(b);
    }

    sort(shelfHeights.begin(), shelfHeights.end());
    sort(bookHeights.begin(), bookHeights.end());

    if (allBooksFit(shelfHeights, bookHeights, x, y, 0))
        cout << maxNumArtShelves(shelfHeights, bookHeights, x, y) << endl;
    else
        cout << "impossible" << endl;

    return 0;
}

/*
4 8 4 2
4 8 6 2
1 2 3 5 7 7 8 8

3
-----------------
4 11 3 2
2 2 2 2
1 1 1 1 1 1 1 1 1 1 1

1
----------------
2 10 3 2
8 6
4 2 1 3 6 2 1 3 4 5

impossible
--------------
3 8 8 3
7 9 4
2 3 4 5 6 7 8 9

3
*/