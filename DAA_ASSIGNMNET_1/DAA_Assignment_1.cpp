#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include <stdexcept>
using namespace std;
struct Player { string name, team; int runs, season; };
long long comparisons = 0, merges = 0;

// Read quoted CSV fields, including commas and doubled quotes inside titles.
vector<string> csvFields(const string& line) {
    vector<string> fields; string field; bool quoted = false;
    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == '"') {
            if (quoted && i + 1 < line.size() && line[i + 1] == '"') {
                field += '"'; i++;
            } else quoted = !quoted;
        } else if (c == ',' && !quoted) { fields.push_back(field); field.clear(); }
        else if (c != '\r') field += c;
    }
    if (quoted) throw runtime_error("Unclosed CSV quote");
    fields.push_back(field); return fields;
}

void mergeSort(vector<Player>& a, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid); mergeSort(a, mid + 1, right);
    vector<Player> temp; temp.reserve(right - left + 1);
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        comparisons++;
        // Left record wins ties: stable, descending order of runs.
        if (a[i].runs >= a[j].runs) temp.push_back(a[i++]);
        else temp.push_back(a[j++]);
    }
    while (i <= mid) temp.push_back(a[i++]);
    while (j <= right) temp.push_back(a[j++]);
    for (size_t k = 0; k < temp.size(); k++) a[left + k] = temp[k];
    merges++;
}
int main(int argc, char* argv[]) {
    string filename = argc > 1 ? argv[1] : "IPLBatters.csv";
    ifstream file(filename); if (!file) { cerr << "Cannot open " << filename << '\n'; return 1; }
    vector<Player> a; string line; getline(file, line); int row = 1;
    while (getline(file, line)) {
        row++; if (line.empty() || line == "\r") continue;
        try {
            vector<string> f = csvFields(line);
            if (f.size() != 4) throw runtime_error("Expected name,team,runs,season");
            Player p = {f[0], f[1], stoi(f[2]), stoi(f[3])};
            if (p.name.empty() || p.runs < 0) throw runtime_error("Invalid player");
            a.push_back(p);
        } catch (const exception& e) { cerr << "CSV row " << row << ": " << e.what() << '\n'; return 1; }
    }
    auto start = chrono::steady_clock::now();
    if (!a.empty()) mergeSort(a, 0, static_cast<int>(a.size()) - 1);
    auto finish = chrono::steady_clock::now();
    cout << "ASSIGNMENT 1: IPL BATTING - MERGE SORT\n"
         << "Dataset: " << filename << "\nRecord: player + team + season (2008-2024)\n"
         << "Sort parameter: Runs | Order: Descending | Display: ALL records\n\n";
    cout << "Rank | Player | Team | Season | Runs\n" << string(100, '-') << '\n';
    long long total = 0;
    for (size_t i = 0; i < a.size(); i++) {
        cout << i + 1 << " | " << a[i].name << " | " << a[i].team << " | "
             << a[i].season << " | " << a[i].runs << '\n'; total += a[i].runs;
    }
    cout << string(100, '-') << "\nRecords loaded / displayed: " << a.size() << " / " << a.size()
         << "\nTotal batting runs across records: " << total;
    if (!a.empty()) cout << "\nHighest runs: " << a.front().runs << " | Lowest runs: " << a.back().runs;
    cout << "\nKey comparisons: " << comparisons << " | Merge operations: " << merges
         << fixed << setprecision(3) << "\nSorting time (excluding file I/O and printing): "
         << chrono::duration<double, milli>(finish - start).count() << " ms\n"
         << "Time: O(N log N) | Auxiliary memory: O(N)\n";
}
