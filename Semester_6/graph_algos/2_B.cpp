#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("/home/drundolet/Projects/SPbU-homework/Semester_6/graph_algos/input.txt", "r", stdin);

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--;
    t--;
    vector<vector<pair<int, int>>> g(n);

    for (int i = 0; i < m; i++) {
        int b, e, w;
        cin >> b >> e >> w;
        g[b - 1].push_back(make_pair(e - 1, w));
        g[e - 1].push_back(make_pair(b - 1, w));
    }

    set<pair<int, int>> q;
    vector<int> d(n, -1);
    d[s] = 0;
    q.insert(make_pair(d[s], s));

    while (!q.empty()) {
        int vertex = q.begin()->second;
        q.erase(q.begin());

        if (d[vertex] == -1)
            continue;

        for (int i = 0; i < g[vertex].size(); i++) {
            int target = g[vertex][i].first;
            int len = g[vertex][i].second;

            if (d[target] > d[vertex] + len || d[target] == -1) {
                d[target] = d[vertex] + len;
                q.insert(make_pair(d[target], target));
            }
        }
    }

    cout << d[t];

    return 0;
}
