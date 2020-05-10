#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

int timer = 0;
vector<int> answer;

void dfs(vector<vector<pair<int, int>>> &g, int u, int v, int lowest[], int discovery[]);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("/home/drundolet/Projects/SPbU-homework/Semester_6/graph_algos/input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);

    for (int i = 0; i < m; i++) {
        int b, e;
        cin >> b >> e;
        g[b - 1].push_back(make_pair(e - 1, i));
        g[e - 1].push_back(make_pair(b - 1, i));
    }

    int lowest[n], discovery[n];
    for (int i = 0; i < n; i++)
        lowest[i] = discovery[i] = -1;


    for (int i = 0; i < n; i++) {
        if (discovery[i] == -1)
            dfs(g, i, i, lowest, discovery);
    }

    sort(answer.begin(), answer.end());

    cout << answer.size() << '\n';
    for (int i : answer)
        cout << i << '\n';

    return 0;
}

void dfs(vector<vector<pair<int, int>>> &g, int u, int v, int lowest[], int discovery[]) {
    discovery[v] = timer++;
    lowest[v] = discovery[v];
    for (pair<int, int> w_pair : g[v]) {
        int w = w_pair.first;
        int order = w_pair.second;
        if (discovery[w] == -1) {
            dfs(g, v, w, lowest, discovery);
            lowest[v] = min(lowest[v], lowest[w]);
            if (lowest[w] == discovery[w]) {
                answer.push_back(order + 1);
//                cout << order << '\n';
            }
        } else if (w != u)
            lowest[v] = min(lowest[v], discovery[w]);
    }
}
