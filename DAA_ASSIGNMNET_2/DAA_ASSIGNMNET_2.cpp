#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include <stdexcept>
#include <algorithm>
using namespace std;
struct Movie { string title; double rating; int year; double popularity; };
string sortKey; long long comparisons = 0, swaps = 0;

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

double key(const Movie& m) {
    if (sortKey == "year") return m.year;
    if (sortKey == "popularity") return m.popularity;
    return m.rating;
}
bool before(const Movie& a, const Movie& b) { comparisons++; return key(a) > key(b); }
// Middle pivot, two-way partition. Recurse on the smaller side to bound stack depth.
void quickSort(vector<Movie>& a, int left, int right) {
    while (left < right) {
        Movie pivot = a[left + (right - left) / 2]; int i = left, j = right;
        while (i <= j) {
            while (i <= right && before(a[i], pivot)) i++;
            while (j >= left && before(pivot, a[j])) j--;
            if (i <= j) { swap(a[i], a[j]); swaps++; i++; j--; }
        }
        if (j - left < right - i) { if (left < j) quickSort(a, left, j); left = i; }
        else { if (i < right) quickSort(a, i, right); right = j; }
    }
}
int main(int argc, char* argv[]) {
    string filename = argc > 1 ? argv[1] : "movies.csv";
    ifstream file(filename); if (!file) { cerr << "Cannot open " << filename << '\n'; return 1; }
    vector<Movie> a; string line; getline(file, line); int row = 1;
    while (getline(file, line)) {
        row++; if (line.empty() || line == "\r") continue;
        try {
            vector<string> f = csvFields(line);
            if (f.size() != 4) throw runtime_error("Expected title,rating,release_year,popularity");
            Movie m = {f[0], stod(f[1]), stoi(f[2]), stod(f[3])};
            if (m.title.empty() || !(m.rating >= 0 && m.rating <= 10) || !(m.popularity >= 0)) throw runtime_error("Invalid movie");
            a.push_back(m);
        } catch (const exception& e) { cerr << "CSV row " << row << ": " << e.what() << '\n'; return 1; }
    }
    cout << "ASSIGNMENT 2: MOVIE RANKING - QUICK SORT\nSort movies by (rating/year/popularity):\n";
    if (!(cin >> sortKey) || (sortKey != "rating" && sortKey != "year" && sortKey != "popularity")) {
        cerr << "Choose rating, year or popularity.\n"; return 1;
    }
    auto start = chrono::steady_clock::now();
    if (!a.empty()) quickSort(a, 0, static_cast<int>(a.size()) - 1);
    auto finish = chrono::steady_clock::now();
    cout << "Dataset: " << filename << "\nSort parameter: " << sortKey
         << " | Order: Descending | Display: ALL records\nRating scale: 0-10; year 0 = missing date\n\n"
         << "Rank | Movie | Rating | Year | TMDB popularity\n" << string(100, '-') << '\n';
    cout << fixed << setprecision(3);
    for (size_t i = 0; i < a.size(); i++) cout << i + 1 << " | " << a[i].title << " | " << a[i].rating
        << " | " << a[i].year << " | " << a[i].popularity << '\n';
    cout << string(100, '-') << "\nRecords loaded / displayed: " << a.size() << " / " << a.size();
    if (!a.empty()) cout << "\nHighest selected value: " << key(a.front()) << " | Lowest: " << key(a.back());
    cout << "\nKey comparisons: " << comparisons << " | Swaps: " << swaps
         << "\nSorting time (excluding file I/O and printing): "
         << chrono::duration<double, milli>(finish - start).count() << " ms\n"
         << "Average time: O(N log N); worst: O(N^2) | Recursion stack: O(log N)\n"
         << "Equal ratings may appear in any order (Quick Sort is not stable).\n";
}
