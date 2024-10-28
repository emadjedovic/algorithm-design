#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <stack>
using namespace std;

struct Node
{
    vector<Node *> adjacent_vertices;
    int label;

    void dfs_helper(unordered_map<Node *, Node *> &previous)
    {
        // call dfs on one of this node's neighbours
        for (Node *neighbour : adjacent_vertices)
        {
            // check if not already visited
            if (previous.find(neighbour) == previous.end())
            {
                // not visited
                previous.insert({neighbour, this});
                neighbour->dfs_helper(previous);
            }
        }
    }
};

class Graph
{
private:
    int numberOfNodes;
    vector<Node *> adjacencyList;

public:
    Graph(int n) : numberOfNodes(n)
    {
        adjacencyList.resize(n);
        for (int i = 0; i < n; i++)
        {
            adjacencyList[i] = new Node();
            adjacencyList[i]->label = i;
        }
    };
    ~Graph()
    {
        for (Node *node : adjacencyList)
            delete node;
    }
    void add_edge(int from, int to)
    {
        Node *startNode = adjacencyList[from];
        Node *endNode = adjacencyList[to];
        startNode->adjacent_vertices.push_back(endNode);
    }

    void bfs(Node *first)
    {
        unordered_map<Node *, int> distances; // instead of previous for dfs
        distances.insert({first, 0});
        queue<Node *> queue;
        queue.push(first);

        while (!queue.empty())
        {
            Node *node = queue.front();
            queue.pop();
            int nodeDistance = distances[node];

            for (Node *neighbour : node->adjacent_vertices)
            {
                // check if not already visited
                if (distances.find(neighbour) == distances.end())
                {
                    distances.insert({neighbour, nodeDistance + 1});
                    queue.push(neighbour);
                }
            }
        }
    }

    void dfs_classic(Node *first)
    {
        unordered_map<Node *, Node *> previous;
        previous.insert({first, nullptr});
        stack<Node *> stack;
        stack.push(first);

        while (!stack.empty())
        {
            Node *node = stack.top();
            stack.pop();

            for (Node *neighbour : node->adjacent_vertices)
            {
                // check if not already visited
                if (previous.find(neighbour) == previous.end())
                {
                    // not visited
                    previous.insert({neighbour, node});
                    stack.push(neighbour);
                }
            }
        }
    }

    void dfs_recursive(Node *first)
    {
        // here we keep track of visited at the same time
        unordered_map<Node *, Node *> previous;
        previous.insert({first, nullptr});
        first->dfs_helper(previous);
    }
};

int main()
{
    /* code */
    return 0;
}
