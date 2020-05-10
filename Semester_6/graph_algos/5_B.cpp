#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


vector<vector<int>> g;
vector<int> mt;
vector<bool> used;


bool try_kuhn(int v) {
    if (used[v])
        return false;

    used[v] = true;

    for (int to : g[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }

    return false;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("/home/drundolet/Projects/SPbU-homework/Semester_6/graph_algos/input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    g.resize(n);

    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        while (v != 0) {
            g[i].push_back(v - 1);
            cin >> v;
        }
    }

    mt.assign(m, -1);
    for (int v = 0; v < n; ++v) {
        used.assign(n, false);
        try_kuhn(v);
    }

    vector<pair<int, int>> answer(0);

    for (int i = 0; i < m; ++i)
        if (mt[i] != -1)
            answer.emplace_back(make_pair(mt[i] + 1, i + 1));

    cout << answer.size() << '\n';
    for (auto a : answer)
        cout << a.first << ' ' << a.second << '\n';

    return 0;
}