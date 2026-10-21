#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
struct Item { string name; double weight, utility, ratio, fraction; };
int main() {
    int n; double capacity;
    cout << "ASSIGNMENT 3: FLOOD RELIEF BOAT - FRACTIONAL KNAPSACK\nEnter item count and boat capacity (kg):\n";
    if (!(cin >> n >> capacity) || n < 1 || n > 10000 || !isfinite(capacity) || capacity < 0) return 1;
    vector<Item> items(n);
    cout << "Enter each bulk lot: name weight utility (one-word names)\n";
    for (Item& x : items) {
        if (!(cin >> x.name >> x.weight >> x.utility) || !isfinite(x.weight) || !isfinite(x.utility) || x.weight <= 0 || x.utility < 0) return 1;
        x.ratio = x.utility / x.weight; x.fraction = 0;
    }
    cout << fixed << setprecision(2);
    cout << "\nSUPPLY AND DIVISIBILITY TABLE\n"
         << "Supply | Weight kg | Utility | Utility/kg | Divisibility\n";
    for (const Item& x : items) cout << x.name << " | " << x.weight << " | " << x.utility << " | " << x.ratio << " | Divisible bulk lot\n";
    cout << "A fraction means part of a bulk lot, not cutting an individual blanket or sealed medicine.\n";
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) { return a.ratio > b.ratio; });
    double remaining = capacity, total = 0;
    cout << "\nGREEDY LOADING TABLE (highest utility/kg first)\n"
         << "Supply | Ratio | Fraction | Loaded % | Weight loaded kg | Utility gained | Decision\n";
    for (Item& x : items) {
        x.fraction = min(1.0, remaining / x.weight);
        double weight = x.fraction * x.weight, gain = x.fraction * x.utility;
        remaining = max(0.0, remaining - weight); total += gain;
        cout << x.name << " | " << x.ratio << " | " << x.fraction << " | " << 100 * x.fraction
             << " | " << weight << " | " << gain << " | "
             << (x.fraction == 0 ? "Not loaded" : x.fraction == 1 ? "Whole lot" : "Partial lot") << '\n';
    }
    cout << "\nITEMS IN THE BOAT\n";
    bool any = false;
    for (const Item& x : items) if (x.fraction > 0) {
        any = true; cout << x.name << ": " << x.weight * x.fraction << " kg (" << 100*x.fraction << "% of lot)\n";
    }
    if (!any) cout << "None\n";
    cout << "Boat capacity: " << capacity << " kg\nTotal weight used: " << capacity - remaining
         << " kg\nRemaining capacity: " << remaining << " kg\nMaximum utility: " << total
         << "\nTime: O(N log N) | Storage: O(N)\n";
}
