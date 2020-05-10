#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

int timer = 0;
vector<int> answer;

void dfs(vector<vector<int>> &g, int u, int v, int lowest[], int discovery[]);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("/home/drundolet/Projects/SPbU-homework/Semester_6/graph_algos/input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);

    for (int i = 0; i < m; i++) {
        int b, e;
        cin >> b >> e;
        g[b - 1].push_back(e - 1);
        g[e - 1].push_back(b - 1);
    }

    int lowest[n], discovery[n];
    for (int i = 0; i < n; i++)
        lowest[i] = discovery[i] = -1;


    for (int i = 0; i < n; i++) {
        if (discovery[i] == -1)
            dfs(g, i, -1, lowest, discovery);
    }

    sort(answer.begin(), answer.end());
    answer.erase(unique(answer.begin(), answer.end()), answer.end());
    cout << answer.size() << '\n';
    for (int i : answer)
        cout << i << '\n';

    return 0;
}

void dfs(vector<vector<int>> &g, int v, int p, int lowest[], int discovery[]) {
    discovery[v] = timer++;
    lowest[v] = discovery[v];
    int children = 0;
    for (int to : g[v]) {
        if (to == p) continue;
        if (discovery[to] != -1) {
            lowest[v] = min(lowest[v], discovery[to]);
        } else {
            dfs(g, to, v, lowest, discovery);
            lowest[v] = min(lowest[v], lowest[to]);
            if (lowest[to] >= discovery[v] && p != -1)
                answer.push_back(v + 1);
            ++children;
        }
    }
    if (p == -1 && children > 1)
        answer.push_back(v + 1);
}
