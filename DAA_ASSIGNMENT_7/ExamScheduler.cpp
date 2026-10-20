#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of courses: ";
    if (!(cin >> n) || n < 1 || n > 5000) {
        cout << "Invalid course count.\n";
        return 1;
    }
    vector<string> name(n + 1);
    cout << "Enter course names in ID order (one word each): ";
    for (int i = 1; i <= n; i++) {
        if (!(cin >> name[i])) return 1;
    }

    vector<vector<int>> graph(n + 1);
    cout << "Enter number of conflicting course pairs: ";
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

    cout << "\nExam timetable:\nID Course Slot\n";
    for (int i = 1; i <= n; i++)
        cout << i << " " << name[i] << " " << slot[i] << "\n";
    cout << "Slots used: " << totalSlots << "\n";
    cout << "Greedy gives a valid schedule; minimum slots are not always guaranteed.\n";
    return 0;
}
