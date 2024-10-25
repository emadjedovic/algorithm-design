#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node
{
    int label;
    vector<int> neighbours;
    int indegree;
};

class Graph
{
private:
    int numberOfNodes;
    vector<Node> adjList;

public:
    Graph(int n) : numberOfNodes(n)
    {
        adjList.resize(n);
        for (int i = 0; i < n; i++)
        {
            adjList[i].label = i;
            adjList[i].indegree = 0;
        }
    };
    void addEdge(int start, int end)
    {
        adjList[start].neighbours.push_back(end);
        adjList[end].indegree++;
    }

    void topologicalSort()
    {
        queue<int> zeroIndegreeNodes;
        vector<int> order;

        // find all nodes with 0 indegree
        for(Node node: adjList){
            if(node.indegree==0) zeroIndegreeNodes.push(node.label);
        }

        // add new to order
        while (!zeroIndegreeNodes.empty())
        {
            int currentNode = zeroIndegreeNodes.front();
            order.push_back(currentNode);
            zeroIndegreeNodes.pop();

            // reduce neighbour's indegree by 1
            for(int neighbour: adjList[currentNode].neighbours){
                adjList[neighbour].indegree--;
                // if it's zero then add to list of zero indegrees
                if(adjList[neighbour].indegree==0) zeroIndegreeNodes.push(neighbour);
            }
        }

        // no more zero indegrees
        // did we visit all nodes, though?
        if(order.size() != numberOfNodes) {
            cout<<"Graph contains a cycle. Topological sort not possible."<<endl;
            return;
        }

        // topological sort possible, now print it out
        for(int i: order) cout<<i<<" ";
        cout<<endl;
        
    }

    void printAdjacencyList()
    {
        for (int i = 0; i < numberOfNodes; i++)
        {
            Node currentNode = adjList[i];
            cout << currentNode.label << ": ";
            for (size_t j = 0; j < currentNode.neighbours.size(); j++)
                cout << currentNode.neighbours[j] << " ";
            cout << endl;
        }
    }
};

int main()
{
    Graph graph(8);
    cout<<"Adding edges...";
    graph.addEdge(0,7);
    graph.addEdge(7,3);
    graph.addEdge(3,6);
    graph.addEdge(7,4);
    graph.addEdge(4,5);
    graph.addEdge(4,2);
    graph.addEdge(2,1);
    graph.printAdjacencyList();
    cout << "TOPOLOGICAL SORT" << endl;
    graph.topologicalSort();
    return 0;
}
