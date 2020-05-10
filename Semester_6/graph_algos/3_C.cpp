#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

vector<vector<int>> g, gr;
vector<int> used, order, color;
set<pair<int, int>> s;

void dfs1(int v) {
    int i, to;
    used[v] = 1;
    for (i = 0; i < g[v].size(); i++) {
        to = g[v][i];

        if (!used[to]) dfs1(to);
    }
    order.push_back(v);
}

void dfs2(int v, int c) {
    int i, to;
    color[v] = c;
    for (i = 0; i < gr[v].size(); i++) {
        to = gr[v][i];
        if (color[to] == -1) dfs2(to, c);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("/home/drundolet/Projects/SPbU-homework/Semester_6/graph_algos/input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    g.assign(n, vector<int>(0));
    gr.assign(n, vector<int>(0));
    for (int i = 0; i < m; i++) {
        int b, e;
        cin >> b >> e;
        g[b - 1].push_back(e - 1);
        gr[e - 1].push_back(b - 1);
    }

    used.assign(n, 0);
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs1(i);

    int c = 0;
    color.assign(n, -1);
    for (int i = 0; i < n; i++) {
        int v = order[n - i - 1];
        if (color[v] == -1)
            dfs2(v, c++);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < g[i].size(); j++)
            if (color[i] != color[g[i][j]])
                s.insert(make_pair(color[i],color[g[i][j]]));

    cout << s.size();
}
