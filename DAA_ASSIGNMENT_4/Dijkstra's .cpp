#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;
const long long INF = numeric_limits<long long>::max() / 4;
vector<vector<long long>> graph;
int n;
bool validNode(int v) { return v >= 0 && v < n; }
void dijkstra(int source, int destination) {
    vector<long long> dist(n, INF); vector<int> parent(n, -1); vector<bool> visited(n, false);
    dist[source] = 0;
    cout << "\nDIJKSTRA TRACE\nStep | Finalized node | Minimum distance | Successful relaxations\n";
    for (int step = 0; step < n; step++) {
        int u = -1;
        for (int v = 0; v < n; v++) if (!visited[v] && (u == -1 || dist[v] < dist[u])) u = v;
        if (u == -1 || dist[u] == INF) break;
        visited[u] = true;
        cout << step + 1 << " | " << u << " | " << dist[u] << " | "; bool changed = false;
        for (int v = 0; v < n; v++) if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
            dist[v] = dist[u] + graph[u][v]; parent[v] = u;
            if (changed) cout << ", ";
            changed = true;
            cout << v << "=" << dist[v];
        }
        if (!changed) cout << "None";
        cout << '\n';
    }
    cout << "\nDISTANCE TABLE FROM SOURCE " << source << "\nNode | Shortest cost | Parent\n";
    for (int v = 0; v < n; v++) {
        cout << v << " | "; if (dist[v] == INF) cout << "Unreachable"; else cout << dist[v];
        cout << " | " << parent[v] << '\n';
    }
    if (dist[destination] == INF) { cout << "No path available to destination.\n"; return; }
    vector<int> path;
    for (int v = destination; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    cout << "\nOptimal path: ";
    for (size_t i = 0; i < path.size(); i++) { if (i) cout << " -> "; cout << path[i]; }
    cout << "\nLeg | From -> To | Road cost | Cumulative cost\n"; long long sum = 0;
    for (size_t i = 1; i < path.size(); i++) {
        sum += graph[path[i-1]][path[i]];
        cout << i << " | " << path[i-1] << " -> " << path[i] << " | " << graph[path[i-1]][path[i]] << " | " << sum << '\n';
    }
    cout << "Minimum cost: " << dist[destination] << "\nRoads used: " << path.size()-1 << '\n';
}
int main() {
    int m, source, destination;
    cout << "ASSIGNMENT 4: EMERGENCY ROUTING - DIJKSTRA\nEnter nodes (1-1000) and connections:\n";
    if (!(cin >> n >> m) || n < 1 || n > 1000 || m < 0) return 1;
    graph.assign(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++) graph[i][i] = 0;
    cout << "Enter undirected roads: from to nonnegativeCost (node IDs start at 0)\n";
    for (int i = 0; i < m; i++) {
        int u,v; long long w;
        if (!(cin >> u >> v >> w) || !validNode(u) || !validNode(v) || w < 0 || w > 1000000000000LL) return 1;
        graph[u][v] = graph[v][u] = min(graph[u][v], w);
    }
    cout << "\nROAD TABLE\nFrom | To | Cost\n";
    for (int u = 0; u < n; u++) for (int v = u+1; v < n; v++) if (graph[u][v] != INF) cout << u << " | " << v << " | " << graph[u][v] << '\n';
    cout << "Enter source and destination:\n";
    if (!(cin >> source >> destination) || !validNode(source) || !validNode(destination)) return 1;
    dijkstra(source, destination);
    char update;
    cout << "Update a road? (Y/N):\n";
    while (cin >> update && (update == 'Y' || update == 'y')) {
        int u,v; long long w; cout << "Enter from to newCost:\n";
        if (!(cin >> u >> v >> w) || !validNode(u) || !validNode(v) || w < 0 || w > 1000000000000LL) return 1;
        graph[u][v] = graph[v][u] = w;
        cout << "Road updated: " << u << " <-> " << v << " cost " << w << ". Recomputing.\n";
        dijkstra(source, destination); cout << "Update another road? (Y/N):\n";
    }
    cout << "Time per run: O(V^2) | Matrix storage: O(V^2)\n";
}
