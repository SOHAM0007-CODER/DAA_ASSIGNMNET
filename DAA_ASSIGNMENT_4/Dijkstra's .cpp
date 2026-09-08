#include <iostream>
#include <climits>
using namespace std;
const int MAX = 1000;
const int INF = INT_MAX;
int graph[MAX][MAX];
int distanceArr[MAX];
int parent[MAX];
bool visited[MAX];
int vertices;
int findMinDistance()
{
    int minDistance = INF;
    int minIndex = -1;
    for (int i = 0; i < vertices; i++)
    {
        if (!visited[i] && distanceArr[i] < minDistance)
        {
            minDistance = distanceArr[i];
            minIndex = i;
        }
    }
    return minIndex;
}
void printPath(int node)
{
    if (node == -1)
        return;
    printPath(parent[node]);
    cout << node << " ";
}
void dijkstra(int source, int destination)
{
    for (int i = 0; i < vertices; i++)
    {
        distanceArr[i] = INF;
        parent[i] = -1;
        visited[i] = false;
    }
    distanceArr[source] = 0;
    for (int count = 0; count < vertices - 1; count++)
    {
        int u = findMinDistance();
        if (u == -1)
            break;
        visited[u] = true;
        if (u == destination)
            break;
        for (int v = 0; v < vertices; v++)
        {
            if (!visited[v] &&
                graph[u][v] != INF &&
                distanceArr[u] != INF &&
                distanceArr[u] + graph[u][v] < distanceArr[v])
            {
                distanceArr[v] = distanceArr[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
    cout << "\nShortest Path\n";
    cout << "------------------------\n";
    if (distanceArr[destination] == INF)
    {
        cout << "No path available.\n";
    }
    else
    {
        cout << "Source: " << source << endl;
        cout << "Destination: " << destination << endl;
        cout << "Minimum Cost: " << distanceArr[destination] << endl;
        cout << "Optimal Path: ";
        printPath(destination);
        cout << endl;
    }
}
int main()
{
    int edges;
    int source, destination;
    cout << "Dijkstra's Algorithm\n";
    cout << "Enter number of nodes: ";
    cin >> vertices;
    if (vertices > MAX)
    {
        cout << "Maximum " << MAX << " nodes allowed!\n";
        return 0;
    }
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }
    cout << "Enter number of connections: ";
    cin >> edges;
    cout << "Enter Node1 Node2 Weight:\n";
    for (int i = 0; i < edges; i++)
    {
        int u, v, weight;
        cin >> u >> v >> weight;
        if (u < 0 || u >= vertices ||
            v < 0 || v >= vertices ||
            weight < 0)
        {
            cout << "Invalid input!\n";
            i--;
            continue;
        }
        graph[u][v] = weight;
        graph[v][u] = weight;
    }
    cout << "Enter source node: ";
    cin >> source;
    cout << "Enter destination node: ";
    cin >> destination;
    dijkstra(source, destination);
    char update;
    cout << "Do you want to update a connection? (Y/N): ";
    cin >> update;
    while (update == 'Y' || update == 'y')
    {
        int u, v, newWeight;
        cout << "Enter connection to update: ";
        cin >> u >> v;
        cout << "Enter new weight: ";
        cin >> newWeight;
        graph[u][v] = newWeight;
        graph[v][u] = newWeight;
        cout << "Connection updated successfully!\n";
        dijkstra(source, destination);
        cout << "Do you want to update another connection? (Y/N): ";
        cin >> update;
    }
    cout << "Program Completed Successfully!\n";
    return 0;
}