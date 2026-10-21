#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <algorithm>
#include <cstdlib>
using namespace std;

const long long INF = numeric_limits<long long>::max() / 4;
int n, startCity;
long long timeLimit, fuelPrice;
vector<vector<long long>> cost, minutes, distanceKm, fuelMl;

struct Node {
    vector<int> path;
    unsigned int visited;
    long long paid, time, bound;
};

struct LeastBound {
    bool operator()(const Node &a, const Node &b) const {
        return a.bound > b.bound; // Smallest bound is expanded first.
    }
};

void require(bool valid) {
    if (!valid) {
        cout << "Invalid input. Please restart with correct values.\n";
        exit(1);
    }
}

// Print exact thousandths (mL -> litres, milli-INR -> INR).
string thousandths(long long value) {
    string fraction = to_string(value % 1000);
    return to_string(value / 1000) + "." +
           string(3 - fraction.size(), '0') + fraction;
}

// Remaining tour needs one outgoing edge from current + each unvisited city,
// and one incoming edge into each unvisited city + the starting city.
long long remainingBound(const Node &node, const vector<vector<long long>> &weight) {
    vector<int> from = {node.path.back()}, to;
    for (int u = 0; u < n; u++) {
        if (!(node.visited & (1U << u))) {
            from.push_back(u);
            to.push_back(u);
        }
    }
    to.push_back(startCity);
    long long outgoing = 0, incoming = 0;
    for (int u : from) {
        long long cheapest = INF;
        for (int v : to) {
            if (u == v) continue;
            if (u == node.path.back() && v == startCity && from.size() > 1) continue;
            cheapest = min(cheapest, weight[u][v]);
        }
        if (cheapest == INF) return INF;
        outgoing += cheapest;
    }
    for (int v : to) {
        long long cheapest = INF;
        for (int u : from) {
            if (u == v) continue;
            if (u == node.path.back() && v == startCity && from.size() > 1) continue;
            cheapest = min(cheapest, weight[u][v]);
        }
        if (cheapest == INF) return INF;
        incoming += cheapest;
    }
    // These are two bounds on the SAME remaining tour; do not add them.
    return max(outgoing, incoming);
}

long long bestCost = INF;
vector<int> bestPath;

void completeTour(const Node &node) {
    int last = node.path.back();
    if (cost[last][startCity] == INF) return;
    if (node.time + minutes[last][startCity] > timeLimit) return;
    long long total = node.paid + cost[last][startCity];
    if (total < bestCost) {
        bestCost = total;
        bestPath = node.path;
        bestPath.push_back(startCity);
    }
}

// Greedy only supplies an initial upper bound; it is NOT the final solver.
void initialTour(bool fastest) {
    Node node = {{startCity}, 1U << startCity, 0, 0, 0};
    while ((int)node.path.size() < n) {
        int u = node.path.back(), next = -1;
        for (int v = 0; v < n; v++) {
            if ((node.visited & (1U << v)) || cost[u][v] == INF) continue;
            if (next == -1 || (fastest ? minutes[u][v] < minutes[u][next]
                                      : cost[u][v] < cost[u][next])) next = v;
        }
        if (next == -1) return;
        node.paid += cost[u][next];
        node.time += minutes[u][next];
        node.path.push_back(next);
        node.visited |= 1U << next;
    }
    completeTour(node);
}

void solve() {
    initialTour(false);
    initialTour(true);
    Node root = {{startCity}, 1U << startCity, 0, 0, 0};
    root.bound = remainingBound(root, cost);
    priority_queue<Node, vector<Node>, LeastBound> live;
    long long rootTime = remainingBound(root, minutes);
    if (root.bound < bestCost && rootTime <= timeLimit) live.push(root);

    cout << "\nINITIAL BOUNDS\nRoot cost lower bound:\n";
    if (root.bound == INF) cout << "No possible completion"; else cout << thousandths(root.bound) << " INR";
    cout << "\nRoot travel-time lower bound:\n";
    if (rootTime == INF) cout << "No possible completion"; else cout << rootTime << " minutes";
    cout << "\nInitial feasible seed cost:\n";
    if (bestCost == INF) cout << "None"; else cout << thousandths(bestCost) << " INR";
    cout << "\nGreedy seeds give upper bounds only; LC search proves the result.\n";
    cout << "\nSEARCH TRACE (first 20 expanded nodes)\nNode | Partial route | Paid INR | Elapsed min | Lower bound INR\n";
    unsigned long long expanded = 0, pruned = 0;
    size_t peakQueue = live.size();

    while (!live.empty()) {
        if (live.top().bound >= bestCost) break; // No live node can improve it.
        Node node = live.top();
        live.pop();
        expanded++;
        if (expanded <= 20) {
            cout << expanded << " | ";
            for (int city : node.path) cout << city + 1 << " ";
            cout << "| " << thousandths(node.paid) << " | " << node.time << " | " << thousandths(node.bound) << '\n';
        }
        int u = node.path.back();
        for (int v = 0; v < n; v++) {
            if ((node.visited & (1U << v)) || cost[u][v] == INF) continue;
            Node child = node;
            child.path.push_back(v);
            child.visited |= 1U << v;
            child.paid += cost[u][v];
            child.time += minutes[u][v];
            if (child.paid >= bestCost || child.time > timeLimit) {
                pruned++;
                continue;
            }
            if ((int)child.path.size() == n) {
                completeTour(child);
                continue;
            }
            long long extraTime = remainingBound(child, minutes);
            long long extraCost = remainingBound(child, cost);
            if (extraTime == INF || extraCost == INF ||
                child.time + extraTime > timeLimit ||
                child.paid + extraCost >= bestCost) {
                pruned++;
                continue;
            }
            child.bound = child.paid + extraCost;
            live.push(child);
            peakQueue = max(peakQueue, live.size());
        }
    }

    if (bestCost == INF) {
        cout << "\nNo tour visits every city and returns within the time limit.\n";
    } else {
        long long distance = 0, fuel = 0, duration = 0;
        cout << "\nOptimal route:\n";
        for (int i = 0; i < (int)bestPath.size(); i++) {
            if (i) cout << " -> ";
            cout << bestPath[i] + 1;
            if (i) {
                int a = bestPath[i - 1], b = bestPath[i];
                distance += distanceKm[a][b];
                fuel += fuelMl[a][b];
                duration += minutes[a][b];
            }
        }

        cout << "\nLEG DETAILS\nLeg | From -> To | Distance km | Fuel L | Cost INR | Time min | Cumulative INR\n";
        long long cumulative = 0;
        for (int i = 1; i < (int)bestPath.size(); i++) {
            int a = bestPath[i-1], b = bestPath[i]; cumulative += cost[a][b];
            cout << i << " | " << a+1 << " -> " << b+1 << " | " << distanceKm[a][b] << " | " << thousandths(fuelMl[a][b])
                 << " | " << thousandths(cost[a][b]) << " | " << minutes[a][b] << " | " << thousandths(cumulative) << '\n';
        }
        cout << "Cities visited exactly once: " << n << " / " << n << " | Return to start: YES\n";
        cout << "Deadline check: PASS | Spare time: " << timeLimit - duration << " minutes\n";
        cout << "\nMinimum fuel cost: " << thousandths(bestCost) << " INR\n";
        cout << "Total distance: " << distance << " km\n";
        cout << "Total fuel: " << thousandths(fuel) << " litres\n";
        cout << "Total travel time: " << duration << " minutes\n";
        cout << "Time limit: " << timeLimit << " minutes\n";
        cout << "Optimality proven by LC Branch and Bound.\n";
    }
    cout << "Expanded nodes: " << expanded << "\n";
    cout << "Pruned child nodes: " << pruned << "\n";
    cout << "Peak queued nodes: " << peakQueue << "\n";
}

int main() {
    cout << "ASSIGNMENT 8: SWIFTSHIP - LC BRANCH AND BOUND TSP\n";
    cout << "Enter number of cities (2-25):\n";
    require(bool(cin >> n));
    require(n >= 2 && n <= 25);
    cout << "Enter fuel price (whole INR per litre):\n";
    require(bool(cin >> fuelPrice));
    require(fuelPrice >= 1 && fuelPrice <= 100000);
    cost.assign(n, vector<long long>(n, INF));
    minutes = cost;
    distanceKm = cost;
    fuelMl = cost;
    int roads;
    cout << "Enter number of directed roads:\n";
    require(bool(cin >> roads));
    require(roads >= 0 && roads <= n * (n - 1));
    cout << "Enter: from to distanceKm fuelMlPerKm travelMinutes\n";
    for (int i = 0; i < roads; i++) {
        int a, b;
        long long distance, rate, time;
        require(bool(cin >> a >> b >> distance >> rate >> time));
        require(a >= 1 && a <= n && b >= 1 && b <= n && a != b);
        a--; b--;
        require(cost[a][b] == INF && distance >= 1 && distance <= 1000000 &&
                rate >= 1 && rate <= 10000 && time >= 1 && time <= 1000000);
        distanceKm[a][b] = distance;
        fuelMl[a][b] = distance * rate;
        cost[a][b] = fuelMl[a][b] * fuelPrice; // Exact milli-INR.
        minutes[a][b] = time;
    }
    cout << "Enter start city and maximum total travel minutes:\n";
    require(bool(cin >> startCity >> timeLimit));
    require(startCity >= 1 && startCity <= n && timeLimit >= 0 && timeLimit <= 25000000);

    startCity--;
    cout << "\nDIRECTED ROAD TABLE\nFrom -> To | Distance km | Consumption mL/km | Fuel L | Cost INR | Time min\n";
    for (int a = 0; a < n; a++) for (int b = 0; b < n; b++) if (cost[a][b] != INF)
        cout << a+1 << " -> " << b+1 << " | " << distanceKm[a][b] << " | " << fuelMl[a][b] / distanceKm[a][b]
             << " | " << thousandths(fuelMl[a][b]) << " | " << thousandths(cost[a][b]) << " | " << minutes[a][b] << '\n';
    cout << "Objective: minimum fuel cost | Starting city: " << startCity+1 << " | Deadline: " << timeLimit << " minutes\n";
    solve();
    return 0;
}
