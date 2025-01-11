// https://codeforces.com/gym/105562/problem/L

#include <iostream>
#include <vector>
using namespace std;

/*
Find the largest number of shelves on which you can place an art piece,
whilst also being able to fit all the new books on the shelves.
*/

int maxNumShelves()
{
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
    vector<int> shelf_heights;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        shelf_heights.push_back(a);
    }

    // the heights of the books
    vector<int> book_heights;
    for (int i = 0; i < m; i++)
    {
        int b;
        cin >> b;
        book_heights.push_back(b);
    }

    if (maxNumShelves() == -1)
        cout << "impossible" << endl;
    else
        cout << maxNumShelves() << endl;

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