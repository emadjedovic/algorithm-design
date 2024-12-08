// codeforces.com/problemset/problem/4/D

/*
Chain here is such a sequence of envelopes A = {a1, a2, ..., an}, where the width and the height of the i-th envelope is strictly higher than the width and the height of the (i-1)-th envelope respectively. Chain size is the number of envelopes in the chain.

Peter wants to make the chain of the maximum size from the envelopes he has, the chain should be such, that he'll be able to put a card into it. The card fits into the chain if its width and height is lower than the width and the height of the smallest envelope in the chain respectively. It's forbidden to turn the card and the envelopes.

The card should fit into the smallest envelope.
If the card does not fit into any of the envelopes, print 0.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Envelope
{
    int w, h;
    int index;
    Envelope(int w, int h, int i) : w(w), h(h), index(i) {}
};

bool compare(const Envelope &a, const Envelope &b)
{
    if (a.w == b.w)
        return a.h < b.h;
    return a.w < b.w;
}

int maxChainSize(const vector<Envelope> &envelopes, vector<Envelope> &chain)
{
    int numEnvelopes = envelopes.size();

    // maximum chain size ending at envelope[i]
    // at least one envelope because we already filtered out the ones that are smaller than the card
    vector<int> D(numEnvelopes, 1);
    // for chain reconstruction
    vector<int> previous(numEnvelopes, -1);

    int result = 0;
    int lastIndex = -1;

    for (int i = 0; i < numEnvelopes; i++)
    {
        // for each envelope i, iterate over all previous envelopes  j < i
        for (int j = 0; j < i; j++)
        {
            // they are sorted by width first so it doesnt mean the next envelope is taller than the previous one
            // check if envelope[j] can fit into envelope[i]
            if (envelopes[j].w < envelopes[i].w && envelopes[j].h < envelopes[i].h)
            {
                // sure, it fits
                if (D[j] + 1 > D[i])
                {
                    D[i] = D[j] + 1;
                    previous[i] = j;
                }
            }
        }
        if (D[i] > result)
        {
            result = D[i];
            lastIndex = i;
        }
        // next envelope...
    }

    // reconstruct
    while (lastIndex != -1)
    {
        chain.push_back(envelopes[lastIndex]);
        lastIndex = previous[lastIndex];
    }

    reverse(chain.begin(), chain.end());

    return result;
}

int main()
{
    int numEnvelopes;
    int cardWidth;
    int cardHeight;

    cout << "Number of envelopes: ";
    cin >> numEnvelopes;
    cout << "Card width and height: ";
    cin >> cardWidth >> cardHeight;

    vector<Envelope> envelopes;
    for (int i = 0; i < numEnvelopes; i++)
    {
        int wi, hi;
        cout << "Input envelope width and height: ";
        cin >> wi >> hi;
        // only consider envelopes larger than the card
        if (wi > cardWidth && hi > cardHeight)
            envelopes.push_back(Envelope(wi, hi, i));
    }

    // for example all envelopes smaller than the card
    if (envelopes.empty())
    {
        cout << 0 << endl;
        return 0;
    }

    // sort envelopes by size asc
    sort(envelopes.begin(), envelopes.end(), compare);

    vector<Envelope> chain;
    int maxSize = maxChainSize(envelopes, chain);
    cout << "The maximum chain size: " << maxSize << endl;
    cout << "Envelopes forming the required chain: ";
    for (size_t i = 0; i < chain.size(); i++)
    {
        cout << chain[i].index + 1 << " ";
    }
    cout << endl;

    return 0;
}

/*
Input
2
1 1
2 2
2 2

Output
1
1

Input
3
3 3
5 4
12 11
9 8

Output
3
1 3 2
*/