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
    Graph(int k, int n, int m) : k(k), n(n), m(m)
    {
        plate.resize(k, vector<vector<char>>(n, vector<char>(m)));
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
                    neighbours.push_back(Node(newLayer, newRow, newCol));
            }
        }
        return neighbours;
    }
};

void DFS(Node node, Graph& graph, int &count)
{
    // fill the component with connected nodes
    count++;
    graph.plate[node.layer][node.row][node.col] = 'v';
    vector<Node> neighbours = graph.getNeighbours(node);
    for (Node n : neighbours)
        if (graph.plate[n.layer][n.row][n.col]!='v')
            DFS(n, graph, count);
}

int numberOfCubicalUnits(Graph& plate, int x, int y)
{
    x--;
    y--;
    int count=0;
    DFS(Node(0,x,y), plate, count);
    return count;
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
_____________

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