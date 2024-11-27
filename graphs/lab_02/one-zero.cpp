/*
www.spoj.com/problems/ONEZERO/

Certain positive integers have their decimal representation consisting only of ones and zeros,
and having at least one digit one, e.g. 101. If a positive integer does not have such a
property, one can try to multiply it by some positive integer to find out whether the product has this property...

Nodes are positive integers with such property.
1 is root with children 10 and 11
10 has children 100 and 101
11 has children 110 and 111
We do BFS on those nodes.
For each node we check whether it is a multiple of n.

*/

#include <iostream>
#include <vector>
#include <queue> // for bfs
using namespace std;

bool isMultiple(int n, int multiple)
{
    if(multiple%n==0) return true;
    return false;
}

vector<int> generateNeighbours(int node)
{
    vector<int> result;
    string nodeString = to_string(node);
    result.push_back(stoi(nodeString+"0"));
    result.push_back(stoi(nodeString+"1"));
    return result;
}

int BFSUntilMultiple(int n)
{
    queue<int> q;
    q.push(1);

    while(true)
    {
        int node = q.front();
        q.pop();
        if(isMultiple(n, node)) return node;
        vector<int> neighbours = generateNeighbours(node);
        for(int neighbour: neighbours)
        {
            if(isMultiple(n, neighbour)) return neighbour;
            q.push(neighbour);
        }
    }
}

int main()
{
    int a = 17; // 11101
    int b = 11011; // 11011
    int c = 8; // 11101
    cout<<BFSUntilMultiple(a)<<endl;
    cout<<BFSUntilMultiple(b)<<endl;
    cout<<BFSUntilMultiple(c)<<endl;
    return 0;
}
