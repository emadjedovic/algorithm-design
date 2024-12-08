#include <iostream>
#include <vector>

using namespace std;

// item-driven approach (iterates through relevant capacities for each item)
// only processing capacities where the item can fit
int knapsack(int W, int k, const vector<int> &w, const vector<int> &b, vector<int> &itemsUsed)
{
    vector<int> B(W + 1);

    for (int i = 0; i < k; i++)
    {
        // Iterate backwards through the capacities to avoid using the same item twice
        for (int W_current = W; W_current >= w[i]; W_current--)
        {
            int valueWithCurrentTaken = B[W_current - w[i]] + b[i];
            if (valueWithCurrentTaken > B[W_current])
            {
                B[W_current] = valueWithCurrentTaken;
                itemsUsed[W_current] = i; // Track the item taken for this capacity
            }
        }
    }
    return B[W];
}

int main()
{
    int W = 17;
    vector<int> w = {3, 4, 7, 8, 9};    // weights
    vector<int> b = {4, 5, 10, 11, 13}; // values
    int k = w.size();                   // total number of items available

    // track selected items (-1 means no item selected)
    vector<int> itemsUsed(W + 1, -1);

    int bestValue = knapsack(W, k, w, b, itemsUsed);

    cout << "Best value: " << bestValue << endl;
    cout << "Items: ";
    for (int W_current = W; W_current >= 0; W_current -= w[itemsUsed[W_current]])
    {
        if (itemsUsed[W_current] == -1)
            break;
        cout << itemsUsed[W_current] << " ";
    }
    cout << endl;

    return 0;
}
