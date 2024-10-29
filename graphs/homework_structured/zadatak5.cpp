// Implementirati crtanje grafa. Dati čvorovima koordinate. Linije simulirati recimo sa +++++.
#include "graph.h"

Graph Graph::convertToUndirected() const
{
    Graph undirectedGraph(numberOfNodes, false);

    // dodati grane u drugom smjeru
    for (int i = 0; i < numberOfNodes; i++)
    {
        for (int neighbour : adjacencyList[i].neighbours)
        {
            vector<int> othersNeighbours = adjacencyList[neighbour].neighbours;
            for (int node : othersNeighbours)
            {
                if (node == i)
                    continue; // izbjeći duplikate
            }
            undirectedGraph.addEdge(i, neighbour);
        }
    }

    return undirectedGraph;
}

// dodjeljujemo koordinate tako da čvorovi na istom levelu imaju istu y koordinatu
void Graph::assignCoordinatesUsingBFS()
{
    coordinates.resize(numberOfNodes);
    queue<int> q;
    vector<int> levels(numberOfNodes, -1);

    q.push(0);
    levels[0] = 0;
    coordinates[0] = {0, 0};

    while (!q.empty())
    {
        int parentNode = q.front();
        q.pop();

        int levelUp = levels[parentNode] + 1;
        int y = levelUp * 10; // konstantno za trenutni level

        int x = 0;
        int parentNodeX = coordinates[parentNode].first;
        // int pushLeft = levelUp*10;
        int neighbourInQuestion = 1;

        for (int neighbour : adjacencyList[parentNode].neighbours)
        {
            // svaki susjed dobija x koordinatu za 10 veću
            // ignoriramo posjećene
            if (levels[neighbour] == -1)
            {
                levels[neighbour] = levelUp;
                q.push(neighbour);
                // neighbourInQuestion stavlja ovaj čvor s desne strane prethodnog
                x = (parentNodeX - 10) + 10 * neighbourInQuestion;
                coordinates[neighbour] = {x, y};
                neighbourInQuestion++;
            }
        }
    }
}

void Graph::printCoordinates()
{
    for (int i = 0; i < numberOfNodes; ++i)
        cout << "Node " << i << ": (" << coordinates[i].first << ", " << coordinates[i].second << ")\n";
}

void Graph::drawGraph()
{
    // velicina povrsine za crtanje
    int width = 0, height = 0;
    for (auto &xyPair : coordinates)
    {
        width = max(width, xyPair.first);
        height = max(height, xyPair.second);
    }

    // dodati prostora
    width += 20;
    height += 10;
    vector<vector<string>> grid(height, vector<string>(width, " "));

    // postavljamo cvorove
    for (int i = 0; i < numberOfNodes; ++i)
    {
        int x = coordinates[i].first;
        int y = coordinates[i].second;
        grid[y][x] = "[" + to_string(i) + "]";
    }

    // postavljamo grane
    for (int i = 0; i < numberOfNodes; ++i)
    {
        int x1 = coordinates[i].first;
        int y1 = coordinates[i].second;
        for (int neighbour : adjacencyList[i].neighbours)
        {
            int x2 = coordinates[neighbour].first;
            int y2 = coordinates[neighbour].second;

            // horizontalno
            if (y1 == y2)
            {
                int startX = min(x1, x2);
                int endX = max(x1, x2);
                for (int x = startX + 1; x < endX; ++x)
                {
                    // provjeri je li polje prazno da ne bismo pisali preko čvorova
                    if (grid[y1][x] == " ")
                        grid[y1][x] = "-";
                }
            }
            // vertikalno
            else if (x1 == x2)
            {
                int startY = min(y1, y2);
                int endY = max(y1, y2);
                for (int y = startY + 1; y < endY; ++y)
                {
                    if (grid[y][x1] == " ")
                        grid[y][x1] = " | ";
                }
            }
            // dijagonalno
            else
            {
                int steps = max(abs(x2 - x1), abs(y2 - y1));
                for (int step = 1; step < steps; ++step)
                {
                    int x = x1 + step * (x2 - x1) / steps;
                    int y = y1 + step * (y2 - y1) / steps;
                    if (grid[y][x] == " ")
                        grid[y][x] = ".";
                }
            }
        }
    }

    cout << endl;
    for (const auto &row : grid)
    {
        for (const string &cell : row)
            cout << cell;
        cout << '\n';
    }
}

void Graph::drawInstantly()
{
    if (isDirected)
        convertToUndirected();
    assignCoordinatesUsingBFS();
    drawGraph();
}