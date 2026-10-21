#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


// Colors are labels for time slots; further slots always get a unique label.
string colorName(int slot) {
    const vector<string> colors = {"Red", "Blue", "Green", "Yellow", "Orange", "Purple", "Cyan", "Magenta", "Brown", "Pink", "Teal", "Indigo"};
    if (slot <= (int)colors.size()) return colors[slot - 1];
    return "Color_" + to_string(slot);
}
int main() {
    cout << "ASSIGNMENT 7: EXAM TIMETABLE - GREEDY GRAPH COLORING\n";

    int n, m;
    cout << "Enter number of courses:\n";
    if (!(cin >> n) || n < 1 || n > 5000) {
        cout << "Invalid course count.\n";
        return 1;
    }
    vector<string> name(n + 1);
    cout << "Enter course names in ID order (one word each):\n";
    for (int i = 1; i <= n; i++) {
        if (!(cin >> name[i])) return 1;
    }

    vector<vector<int>> graph(n + 1);
    cout << "Enter number of conflicting course pairs:\n";
    if (!(cin >> m) || m < 0 || m > n * (n - 1) / 2) return 1;
    cout << "Enter each pair of course IDs sharing a student:\n";
    for (int i = 0; i < m; i++) {
        int a, b;
        if (!(cin >> a >> b) || a < 1 || a > n || b < 1 || b > n || a == b) {
            cout << "Invalid conflict pair.\n";
            return 1;
        }
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> slot(n + 1, 0);
    int totalSlots = 0;
    for (int course = 1; course <= n; course++) {
        vector<bool> used(n + 1, false);
        // Mark the slots already used by conflicting courses.
        for (int neighbor : graph[course]) {
            if (slot[neighbor] != 0) used[slot[neighbor]] = true;
        }
        // Give this course the first available slot.
        int s = 1;
        while (used[s]) s++;
        slot[course] = s;
        totalSlots = max(totalSlots, s);
    }


    cout << "\nCONFLICT TABLE\nCourse | Conflicting courses\n";
    for (int i = 1; i <= n; i++) {
        cout << name[i] << " | ";
        if (graph[i].empty()) cout << "None";
        for (size_t j = 0; j < graph[i].size(); j++) { if (j) cout << ", "; cout << name[graph[i][j]]; }
        cout << '\n';
    }
    cout << "\nEXAM COLOR ASSIGNMENT\nCourse | Assigned color\n";
    for (int i = 1; i <= n; i++) cout << name[i] << " | " << colorName(slot[i]) << '\n';
    cout << "\nEXAMS GROUPED BY COLOR (one color = one time slot)\n";
    for (int s = 1; s <= totalSlots; s++) {
        cout << colorName(s) << " | "; bool first = true;
        for (int i = 1; i <= n; i++) if (slot[i] == s) { if (!first) cout << ", "; cout << name[i]; first = false; }
        cout << '\n';
    }
    cout << "\nCONFLICT CHECK\nPair | Color 1 | Color 2 | Result\n";
    bool valid = true;
    for (int u = 1; u <= n; u++) for (int v : graph[u]) if (u < v) {
        bool ok = slot[u] != slot[v]; valid = valid && ok;
        cout << name[u] << " - " << name[v] << " | " << colorName(slot[u]) << " | " << colorName(slot[v]) << " | " << (ok ? "PASS" : "FAIL") << '\n';
    }
    cout << "Colors / time slots used: " << totalSlots << "\nSchedule validation: " << (valid ? "CONFLICT-FREE" : "FAILED")
         << "\nGreedy does not always give the minimum colors.\nTime including grouped output: O(V^2+E) | Storage: O(V+E)\n";
    return valid ? 0 : 1;
}
