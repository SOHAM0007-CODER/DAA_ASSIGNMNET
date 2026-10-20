#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
using namespace std;

struct Road {
    int from, to, open;
    double time, traffic, weather, fuel;
};

int n, stages;
double fuelPrice;
vector<Road> roads;
vector<vector<int>> cities, graph;

void require(bool valid) {
    if (!valid) {
        cout << "Invalid input. Please restart with correct values.\n";
        exit(1);
    }
}

bool valid(double x) {
    return x >= 0 && x <= 1e12;
}

void readRoad(Road &r) {
    require(bool(cin >> r.time >> r.traffic >> r.weather >> r.fuel >> r.open));
    require(valid(r.time) && valid(r.traffic) && valid(r.weather) &&
            valid(r.fuel) && (r.open == 0 || r.open == 1));
}

void findRoute(int source, int destination, int mode) {
    const double INF = 1e100;
    vector<double> cost(n + 1, INF);
    vector<int> nextRoad(n + 1, -1);
    cost[destination] = 0;

    // Work from the last stage towards the first stage.
    for (int s = stages - 1; s >= 1; s--) {
        for (int u : cities[s]) {
            for (int id : graph[u]) {
                Road r = roads[id];
                if (r.open == 0 || cost[r.to] == INF) continue;
                double weight = r.time + r.traffic + r.weather;
                if (mode == 2) weight = r.fuel * fuelPrice;
                if (weight + cost[r.to] < cost[u]) {
                    cost[u] = weight + cost[r.to];
                    nextRoad[u] = id;
                }
            }
        }
    }

    if (cost[source] == INF) {
        cout << "No delivery route exists.\n";
        return;
    }
    double time = 0, fuel = 0;
    vector<int> path;
    cout << "Optimal route: " << source;
    for (int u = source; u != destination; ) {
        int id = nextRoad[u];
        Road r = roads[id];
        path.push_back(id + 1);
        time += r.time + r.traffic + r.weather;
        fuel += r.fuel;
        u = r.to;
        cout << " -> " << u;
    }
    cout << "\nRoad IDs:";
    for (int id : path) cout << " " << id;
    cout << "\nTotal time: " << time << " minutes\n";
    cout << "Total fuel: " << fuel << " litres\n";
    cout << "Total fuel cost: " << fuel * fuelPrice << " INR\n";
}

int main() {
    cout << fixed << setprecision(2);
    cout << "Enter number of cities and stages: ";
    require(bool(cin >> n >> stages));
    require(n >= 2 && stages >= 2 && stages <= n);
    vector<int> stage(n + 1);
    cities.resize(stages + 1);
    graph.resize(n + 1);
    cout << "Enter stage of each city: ";
    for (int i = 1; i <= n; i++) {
        require(bool(cin >> stage[i]));
        require(stage[i] >= 1 && stage[i] <= stages);
        cities[stage[i]].push_back(i);
    }
    for (int s = 1; s <= stages; s++) require(!cities[s].empty());
    cout << "Enter fuel price (INR per litre): ";
    require(bool(cin >> fuelPrice));
    require(valid(fuelPrice) && fuelPrice > 0);
    int m;
    cout << "Enter number of roads: ";
    require(bool(cin >> m));
    require(m >= 0);
    roads.resize(m);
    cout << "Enter: from to baseTime trafficDelay weatherDelay fuel open(1/0)\n";
    for (int i = 0; i < m; i++) {
        Road &r = roads[i];
        cout << "Road " << i + 1 << ": ";
        require(bool(cin >> r.from >> r.to));
        require(r.from >= 1 && r.from <= n && r.to >= 1 && r.to <= n);
        require(stage[r.to] == stage[r.from] + 1);
        readRoad(r);
        graph[r.from].push_back(i);
    }

    while (true) {
        int choice;
        cout << "\n1. Delivery batch  2. Update road  3. Show roads  0. Exit\n";
        require(bool(cin >> choice));
        if (choice == 0) break;
        if (choice == 1) {
            int q;
            cout << "Enter number of requests: ";
            require(bool(cin >> q));
            require(q > 0);
            for (int i = 0; i < q; i++) {
                int source, destination, mode;
                cout << "Enter source destination mode(1=fastest, 2=cheapest): ";
                require(bool(cin >> source >> destination >> mode));
                require(source >= 1 && source <= n && destination >= 1 && destination <= n);
                require(stage[source] == 1 && stage[destination] == stages);
                require(mode == 1 || mode == 2);
                cout << (mode == 1 ? "Fastest delivery\n" : "Cheapest delivery\n");
                findRoute(source, destination, mode);
            }
        } else if (choice == 2) {
            int id;
            cout << "Enter road ID: ";
            require(bool(cin >> id));
            require(id >= 1 && id <= m);
            cout << "Enter baseTime trafficDelay weatherDelay fuel open(1/0): ";
            readRoad(roads[id - 1]);
            cout << "Road updated.\n";
        } else if (choice == 3) {
            cout << "ID From To Base Traffic Weather Fuel Open\n";
            for (int i = 0; i < m; i++) {
                Road r = roads[i];
                cout << i + 1 << " " << r.from << " " << r.to << " " << r.time << " "
                     << r.traffic << " " << r.weather << " " << r.fuel << " " << r.open << "\n";
            }
        } else cout << "Invalid menu choice.\n";
    }
    return 0;
}
