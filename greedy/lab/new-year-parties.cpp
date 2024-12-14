// codeforces.com/problemset/problem/1283/E

/*
n - the number of friends
The i-th friend lives in a house with an integer coordinate xi... 1≤xi≤n
The i-th friend can move to the house with coordinate xi−1, xi+1 or stay at xi.
Each friend is allowed to move no more than once.

For all friends holds, however, they can come to houses with coordinates 0 and n+1
(if their houses are at 1 or n, respectively).

The number of occupied houses is the number of distinct positions among the final ones.
So all friends choose the moves they want to perform.
After that the number of occupied houses is calculated.
What is the minimum and the maximum number of occupied houses can there be?
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

/*
The goal is to maximize the number of friends who share the same final position.
This involves grouping friends into as few houses as possible.
At each step, we try to "merge" a friend into an already-occupied house or minimally expand the occupied set.
The decision to place a friend at pos-1, pos, or pos+1 is based solely on the current state of the occupied set, not the future state of all other friends.
This local decision-making fits the greedy paradigm.
*/
int minOccupied(const vector<int> &coord)
{
    vector<int> sorted_coord = coord;
    sort(sorted_coord.begin(), sorted_coord.end());

    set<int> occupied; // final occupied houses
    for (int pos : sorted_coord)
    {
        // if there are many friends in the same house, this sorted array will look like, for example, 1,1,1,2,3
        // the first instance of 1 will be instered into "occupied" and each subsequent 1 will be "continued"
        if (occupied.find(pos) != occupied.end())
        {
            // stay in the current house
            continue;
        }
        // 2 will move into 1
        else if (occupied.find(pos - 1) != occupied.end() && pos - 1 > 0)
        {
            // Friend moves to a previously occupied house at pos-1
            continue;
        }
        else if (occupied.find(pos + 1) != occupied.end())
        {
            // Friend moves to a previously occupied house at pos+1
            continue;
        }
        // 1 and 3 are inserted
        occupied.insert(pos);
    }
    return occupied.size();
}

/*
The goal is to spread friends as much as possible, ensuring that no two friends share a house unless absolutely necessary.
At each step, we try to place a friend into the nearest unoccupied position to maximize the spread.
Decisions are made without considering the global impact, such as whether future friends might lose placement options due to this choice.
*/
int maxOccupied(const vector<int> &coord)
{
    vector<int> sorted_coord = coord;
    sort(sorted_coord.begin(), sorted_coord.end());

    set<int> occupied;
    for (int pos : sorted_coord)
    {
        // lets say we have 2121213 for example
        if (occupied.find(pos) == occupied.end())
        {
            // not occupied, insert 2, 1
            occupied.insert(pos);
        }
        else if (occupied.find(pos + 1) == occupied.end())
        {
            // current occupied but the next one isn't
            // insert 3
            // the final "3" can move to "4"
            occupied.insert(pos + 1);
        }
        else if (occupied.find(pos - 1) == occupied.end() && pos - 1 > 0)
        {
            // current and next occupied, but the previous isn't
            // the second "1" can move to "0" for example
            occupied.insert(pos - 1);
        }
        // skip some coordinates (neither current, next or previous are free so the friend stays in the current house, no new houses are added to "occupied")
    }
    return occupied.size();
}

int main()
{
    vector<int> coord1 = {1, 2, 4, 4};                                 // initial house coordinates
    cout << minOccupied(coord1) << " " << maxOccupied(coord1) << endl; // 2 4
    // possible outcomes for min result: 2,2,3,3 ... 2,2,4,4 ... 1,1,4,4 ... etc
    // possible outcomes for max result: 0,2,3,4 ... 2,1,4,3 ... 1,3,4,5 ... etc

    vector<int> coord2 = {1, 1, 8, 8, 8, 4, 4, 4, 4}; // 3 8
    cout << minOccupied(coord2) << " " << maxOccupied(coord2) << endl;

    vector<int> coord3 = {4, 3, 7, 1, 4, 3, 3}; // 3 6
    cout << minOccupied(coord3) << " " << maxOccupied(coord3) << endl;

    vector<int> coord4 = {5, 5, 5, 5, 5}; // 1 3
    cout << minOccupied(coord4) << " " << maxOccupied(coord4) << endl;

    vector<int> coord5 = {2, 1, 2, 1, 2, 1, 3};
    cout << minOccupied(coord5) << " " << maxOccupied(coord5) << endl;

    return 0;
}

/*
Why not suitable for DP?
Each friend independently chooses a move, so there's no direct dependency between friends.
The current placement of one friend doesn't affect the optimal placement of other friends except indirectly (via shared occupancy).

The problem has a natural "greedy choice property":

    Minimization: Merging friends into already-occupied houses at each step is optimal, as it reduces the need to open new houses.
    Maximization: Spreading friends apart at each step is optimal, as it increases the total number of occupied houses without overlap.

The problem also exhibits an "optimal substructure":

    Once a group of friends is optimally placed, adding another friend does not require re-solving for the previous friends.
*/
