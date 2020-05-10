#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("/home/drundolet/Projects/SPbU-homework/Semester_6/graph_algos/input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    vector<pair<int, pair<int, int>>> g(2*m);
    for (int i = 0; i < m; i++) {
        int b, e, w;
        cin >> b >> e >> w;
        g[i] = make_pair(w, make_pair(b - 1, e - 1));
        g[m + i] = make_pair(w, make_pair(e - 1, b - 1));
    }
    sort(g.begin(), g.end());

    vector<int> tree(n);
    for (int i = 0; i < n; i++) {
        tree[i] = i;
    }

    int cost = 0;
    for (int i = 0; i < 2*m; i++) {
        int b = g[i].second.first, e = g[i].second.second, w = g[i].first;
        if (tree[b] != tree[e]) {
            cost += w;
            int old_t = tree[e], new_t = tree[b];
            for (int j = 0; j < n; j++)
                if (tree[j] == old_t)
                    tree[j] = new_t;
        }
    }

    cout << cost;
}
