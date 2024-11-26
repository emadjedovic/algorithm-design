// https://codeforces.com/contest/1725/problem/M

/*
- a directed graph with N nodes and M edges
- edge i connects two different nodes Ui and Vi with a length of Wi
- two different starting nodes
- the goals is to end up at the common node
- first starting node is 1
- second starting node is p (2<=p<=N)
- for each second start p find the minimum time in seconds needed to arrive at the common node 
(or report if impossible)

MY SOLUTION

- store shortest paths from start1 to all the other nodes
- directed and weighted graph with positive edges -> use dijkstra
- for each startP also store shortest paths to all other nodes
- if start1 and startP can both arrive to some common node (dist<INF) then sum up their distances
- for the current P store in result the minimum of all common destination distances
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge
{
    int to;
    int weight;
    Edge(int t, int w): to(t), weight(w){}
};

void dijkstra(int start, const vector<vector<Edge>>& adjList, vector<int>& distances)
{   
    int numNodes = adjList.size();
    distances.resize(adjList.size());
    for(int i=0; i<numNodes; i++)
        distances[i]=INT32_MAX;
    
    distances[start]=0;
    // potential + node (we are sorting by potential)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minHeapPotentials;

    pair<int,int> startNode = make_pair(0, start);
    minHeapPotentials.push(startNode);
    while(!minHeapPotentials.empty())
    {
        pair<int,int> currentMinNode = minHeapPotentials.top();
        minHeapPotentials.pop();
        int labelOld = currentMinNode.second;
        vector<Edge> neighbours = adjList[labelOld];
        for(Edge e: neighbours)
        {
            int newDistance = distances[labelOld]+e.weight;
            if(newDistance<distances[e.to]){
                // relaxation
                distances[e.to] = newDistance;
                minHeapPotentials.push(make_pair(newDistance, e.to));
            }
        }
    }

}

vector<int> pTimes(const vector<vector<Edge>>& adjList)
{
    vector<int> result;

    vector<int> distancesFrom1;
    dijkstra(0, adjList, distancesFrom1);
    for(size_t p=1; p<adjList.size(); p++)
    {
        vector<int> distancesFromP;
        dijkstra(p, adjList, distancesFromP);
        // find common nodes with distance < INF
        int minResult = -1;
        for(size_t i=0; i<adjList.size(); i++)
        {
            if(distancesFrom1[i] != INT32_MAX && distancesFromP[i]!=INT32_MAX)
            {
                int endingInNodeI = distancesFrom1[i] + distancesFromP[i];
                if(minResult==-1 || (minResult!=-1 && endingInNodeI<minResult)) minResult = endingInNodeI;
            }
        }
        result.push_back(minResult);
    }

    return result;
}

int main()
{
    int N,M;
    cout<<"Input N and M: "<<endl;
    cin>>N>>M;

    vector<vector<Edge>> adjList;
    adjList.resize(N, vector<Edge>());
    for(int i=0; i<M; i++)
    {
        int Ui, Vi, Wi;
        // Ui != Vi
        cout<<"Input Ui, Vi and Wi: ";
        cin>>Ui>>Vi>>Wi;
        adjList[Ui-1].push_back(Edge(Vi-1, Wi));
    }

    // we have a graph now

    vector<int> result = pTimes(adjList);

    cout<<"Minimum times for p=2,3,4,..."<<endl;
    for(int i: result) cout<<i<<" ";
    cout<<endl;

    return 0;
}

/*
5 7
1 2 2
2 4 1
4 1 4
2 5 3
5 4 1
5 2 4
2 1 1

OUTPUT: 1 -1 3 4
*/