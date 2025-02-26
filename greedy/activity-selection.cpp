#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second; // Sort by finish time
}

void activitySelection(vector<pair<int, int>>& activities) {
    sort(activities.begin(), activities.end(), compare);

    cout << "Selected Activities:\n";

    int lastEndTime = -1;

    for (const auto& activity : activities) {
        if (activity.first >= lastEndTime) {
            cout << "Start: " << activity.first << ", End: " << activity.second << endl;
            lastEndTime = activity.second;
        }
    }
}

int main() {
    vector<pair<int, int>> activities = {{1, 3}, {2, 5}, {4, 6}, {6, 8}, {5, 7}, {8, 9}};
    
    activitySelection(activities);

    return 0;
}
