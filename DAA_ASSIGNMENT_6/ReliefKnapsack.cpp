#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    cout << "ASSIGNMENT 6: DISASTER RELIEF TRUCK - 0/1 KNAPSACK\n";
    int n, W;
    cout << "Enter number of items and truck capacity:\n";
    if (!(cin >> n >> W) || n < 1 || n > 200 || W < 0 || W > 10000) {
        cout << "Invalid item count or capacity.\n";
        return 1;
    }

    vector<string> name(n + 1);
    vector<int> weight(n + 1);
    vector<long long> utility(n + 1);
    cout << "Enter each item: name weight utility\n";
    for (int i = 1; i <= n; i++) {
        if (!(cin >> name[i] >> weight[i] >> utility[i]) || weight[i] <= 0 ||
            utility[i] < 0 || utility[i] > 1000000000) {
            cout << "Invalid item details.\n";
            return 1;
        }
    }

    // dp[i][w] = maximum utility using the first i items and capacity w.
    vector<vector<long long>> dp(n + 1, vector<long long>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w]; // Leave the item.
            if (weight[i] <= w) {
                long long take = utility[i] + dp[i - 1][w - weight[i]];
                dp[i][w] = max(dp[i][w], take);
            }
        }
    }

    // Work backwards through the table to find the selected items.
    vector<int> selected;
    int remaining = W;
    for (int i = n; i >= 1; i--) {
        if (dp[i][remaining] != dp[i - 1][remaining]) {
            selected.push_back(i);
            remaining -= weight[i];
        }
    }
    reverse(selected.begin(), selected.end());


    vector<bool> loaded(n + 1, false);
    for (int i : selected) loaded[i] = true;
    cout << "\nSUPPLY AND SELECTION TABLE\nName | Weight kg | Utility | Divisibility | Take (0/1) | Decision\n";
    for (int i = 1; i <= n; i++) cout << name[i] << " | " << weight[i] << " | " << utility[i]
        << " | Whole package only | " << loaded[i] << " | " << (loaded[i] ? "Loaded" : "Left behind") << '\n';
    if (n <= 8 && W <= 20) {
        cout << "\nDP TABLE: maximum utility for each capacity\nItem/Capacity";
        for (int w = 0; w <= W; w++) cout << " | " << w;
        cout << '\n';
        for (int i = 0; i <= n; i++) {
            cout << (i == 0 ? "No items" : name[i]);
            for (int w = 0; w <= W; w++) cout << " | " << dp[i][w];
            cout << '\n';
        }
    } else cout << "DP table omitted from display for large input; optimum is computed using all states.\n";
    cout << "\nITEMS IN THE TRUCK\nName | Weight kg | Utility\n";
    for (int i : selected) cout << name[i] << " | " << weight[i] << " | " << utility[i] << '\n';
    if (selected.empty()) cout << "No items fit with a positive utility gain.\n";
    cout << "Truck capacity: " << W << " kg\nTotal weight: " << W - remaining
         << " kg\nUnused capacity: " << remaining << " kg\nMaximum utility: " << dp[n][W]
         << "\nSelected packages: " << selected.size() << " of " << n
         << "\nTime and space: O(N*(W+1)) | Each package used at most once.\n";
    return 0;
}
