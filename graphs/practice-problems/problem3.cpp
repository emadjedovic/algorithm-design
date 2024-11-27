// codeforces.com/problemset/problem/60/B

/*
The plate can be represented by a parallelepiped k × n × m:
k layers (the first layer is the upper one),
each of which is a rectangle n × m with
empty squares ('.') obstacles ('#').

The water can only be present in the empty squares.

The tap is positioned above the square (x, y) of the first layer,
it is guaranteed that this square is empty.

Every minute a cubical unit of water falls into the plate.

Find the moment of time when the plate is absolutely full
and is going to be overfilled in the next moment.

The answer should contain a single number,
showing in how many minutes the plate will be filled.
*/

/*
MY ANSWER (needs review)

- start dfs from node x,y
- the water enters this point and fills all the holes "." connected to this node
- water reaches all nodes that are "reachable" from starting node x,y
- two nodes in the same layer are connected if there exists no obstacle between them
- two nodes from adjacent layers are connected if they are placed exactly on top of one another (same row and col, one layer up or down)
- we are looking for the number of nodes reachable from x,y
- the graph is undirected and unweighted

*/

#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    int layer;
    int row;
    int col;
    Node(int l, int r, int c) : layer(l), row(r), col(c) {}
};

class Graph
{
    int k, n, m;

public:
    vector<vector<vector<char>>> plate;
    vector<vector<vector<bool>>> visited;
    // each matrix element has a list of neighbours
    // neighbours are either "." or "#"
    Graph(int k, int n, int m) : k(k), n(n), m(m)
    {
        plate.resize(k, vector<vector<char>>(n, vector<char>(m)));
        visited.resize(k, vector<vector<bool>>(n, vector<bool>(m)));
    }
    
    vector<Node> getNeighbours(const Node& node) const
    {
        vector<Node> neighbours;
        vector<vector<int>> directions = 
        {
            // {layer, row, col}
            {1,0,0},
            {-1,0,0},
            {0,1,0},
            {0,-1,0},
            {0,0,1},
            {0,0,-1}
        };

        // for each direction check if water flows
        for(auto d: directions)
        {
            int newLayer = node.layer + d[0];
            int newRow = node.row + d[1];
            int newCol = node.col + d[2];

            // check if within bounds
            if(newLayer < k && newLayer >= 0 && newRow >= 0 && newRow < n && newCol >= 0 && newCol < m)
            {
                char character = plate[newLayer][newRow][newCol];
                if(character == '.')
                {
                    neighbours.push_back(Node(newLayer, newRow, newCol));
                }
            }
        }

        return neighbours;
    }
};

void DFS(Node node, Graph& graph, vector<Node> &component)
{
    // fill the component with connected nodes
    component.push_back(node);
    graph.visited[node.layer][node.row][node.col] = true;
    vector<Node> neighbours = graph.getNeighbours(node);
    for (Node n : neighbours)
    {
        if (!graph.visited[n.layer][n.row][n.col])
        {
            DFS(n, graph, component);
        }
    }
}

int numberOfCubicalUnits(Graph& plate, int x, int y)
{
    x--;
    y--;
    vector<Node> component;
    DFS(Node(0,x,y), plate, component);
    return component.size();
}

int main()
{
    int k, n, m;
    cout << "Input k, n, m: " << endl;
    cin >> k >> n >> m;
    Graph graph3d(k,n,m);

    // define each layer from top to bottom
    // new line for next layer
    for (int i = 0; i < k; i++)
    {
        cout << "Layer #" << i << endl;
        for (int j = 0; j < n; j++)
        {
            for (int l = 0; l < m; l++)
            {
                char c;
                cin >> c; // # or .
                graph3d.plate[i][j][l] = c;

            }
        }
        cout << endl;
    }

    int x, y;
    cout << "Enter tap coordinates: ";
    cin >> x >> y;

    int minuteCount = numberOfCubicalUnits(graph3d, x, y);
    cout << "Result: " << minuteCount << endl;

    return 0;
}

/*
1 1 1

.

1 1
output: 1
______________
2 1 1

.

#

1 1
output: 1
_______________
2 2 2

.#
##

..
..

1 1
output: 5
_____________
3 2 2

#.
##

#.
.#

..
..

1 2
output: 7

3 3 3

.#.
###
##.

.##
###
##.

...
...
...

1 1
output: 13
*/