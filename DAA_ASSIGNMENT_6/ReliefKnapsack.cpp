#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n, W;
    cout << "Enter number of items and truck capacity: ";
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

    cout << "\nSelected items:\nName Weight Utility\n";
    for (int i : selected)
        cout << name[i] << " " << weight[i] << " " << utility[i] << "\n";
    if (selected.empty()) cout << "No items fit with a positive utility gain.\n";
    cout << "Total weight: " << W - remaining << " kg\n";
    cout << "Unused capacity: " << remaining << " kg\n";
    cout << "Maximum utility: " << dp[n][W] << "\n";
    return 0;
}
