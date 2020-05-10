#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m = 0;
    cin >> n >> m;

    vector<vector<int>> g(n);

    int v1, v2;
    for (int i = 0; i < m; i++) {
        cin >> v1 >> v2;
        g[v1 - 1].push_back(v2 - 1);
        g[v2 - 1].push_back(v1 - 1);
    }

    queue<int> q;
    q.push(0);

    vector<bool> visited(n);
    visited[0] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i : g[current]) {
            int adj_vertex = i;
            if (!visited[adj_vertex]) {
                visited[i] = true;
                q.push(adj_vertex);
            }
        }
    }

    if(find(visited.begin(), visited.end(), false) == visited.end()) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}
