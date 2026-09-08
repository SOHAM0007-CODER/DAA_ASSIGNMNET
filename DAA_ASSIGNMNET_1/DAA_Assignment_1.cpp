#include <bits/stdc++.h>
#include<chrono>
using namespace std;

struct Player
{
    string name;
    string team;
    int runs;
};

void merge(vector<Player>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Player> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i].runs >= R[j].runs)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(vector<Player>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main()
{
    vector<Player> players;

    ifstream file("IPL2025Batters.csv");

    if (!file)
    {
        cout << "File not found!";
        return 0;
    }

    string line;
    getline(file, line);

    auto stripQuotes = [](string s)
    {
        if (!s.empty() && s.front() == '"') s.erase(0, 1);
        if (!s.empty() && s.back() == '"') s.pop_back();
        return s;
    };

    while (getline(file, line))
    {
        stringstream ss(line);

        string name, team, runs;

        getline(ss, name, ',');
        getline(ss, team, ',');
        getline(ss, runs, ',');

        name = stripQuotes(name);
        team = stripQuotes(team);
        runs = stripQuotes(runs);

        players.push_back({name, team, stoi(runs)});
    }

    file.close();

    mergeSort(players, 0, players.size() - 1);

    cout << "IPL 2025 Players Sorted By Runs\n";

    for (int i = 0; i < 10; i++)
{
    cout << players[i].name << " | " << players[i].team << " | "<< players[i].runs << " runs\n";
}
	auto start = chrono::high_resolution_clock::now();
mergeSort(players, 0, players.size() - 1);
auto end = chrono::high_resolution_clock::now();

chrono::duration<double, milli> elapsed = end - start;
cout << elapsed.count() << " ms\n";
    return 0;
}
