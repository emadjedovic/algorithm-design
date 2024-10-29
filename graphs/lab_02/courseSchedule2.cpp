/*
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
You are given an array prerequisites where prerequisites{i} = {ai, bi} indicates that you must take course bi first if you want to take course ai.

For example, the pair {0, 1}, indicates that to take course 0 you have to first take course 1.

Return the ordering of courses you should take to finish all courses.
If there are many valid answers, return any of them.
If it is impossible to finish all courses, return an empty array.

Constraints:

    1 <= numCourses <= 2000
    0 <= prerequisites.length <= numCourses * (numCourses - 1)
    prerequisites[i].length == 2
    0 <= ai, bi < numCourses
    ai != bi
    All the pairs [ai, bi] are distinct.

*/

#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<int> findOrder(int numCourses, const vector<vector<int>> &prerequisites)
{
    // topological sort
    // prerequisites are reversed edges
    vector<int> topSort;
    vector<int> indegrees(numCourses, 0);
    for (vector<int> edge : prerequisites)
        indegrees[edge[0]]++;

    set<int> zeroIndegreeNodes;
    for (int i = 0; i < numCourses; i++)
        if (indegrees[i] == 0)
            zeroIndegreeNodes.insert(i);

    while (!zeroIndegreeNodes.empty())
    {
        int node = *zeroIndegreeNodes.begin();
        topSort.push_back(node);
        zeroIndegreeNodes.erase(node);
        // decrement neighbours' indegree
        for (vector<int> edge : prerequisites)
        {
            int startNode = edge[1];
            int endNode = edge[0];
            if (startNode == node)
            {
                indegrees[endNode]--;
                if (indegrees[endNode] == 0)
                    zeroIndegreeNodes.insert(endNode);
            }
        }
    }

    if (topSort.size() != numCourses)
        return {};
    return topSort;
};

int main()
{
    int numCourses1 = 2;
    vector<vector<int>> prerequisites1 = {{1, 0}};
    vector<int> result1 = findOrder(numCourses1, prerequisites1);
    cout << "Example 1 Course Order: " << endl;
    for (int node : result1)
        cout << node << " ";
    cout << endl;

    int numCourses2 = 4;
    vector<vector<int>> prerequisites2 = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    vector<int> result2 = findOrder(numCourses2, prerequisites2);
    cout << "Example 2 Course Order: " << endl;
    for (int node : result2)
        cout << node << " ";
    cout << endl;

    int numCourses3 = 1;
    vector<vector<int>> prerequisites3 = {};
    vector<int> result3 = findOrder(numCourses3, prerequisites3);
    cout << "Example 3 Course Order: " << endl;
    for (int node : result3)
        cout << node << " ";
    cout << endl;

    return 0;
}
