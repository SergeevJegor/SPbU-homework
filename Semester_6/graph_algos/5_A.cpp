#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


const int MAXN = 100000;
const int MAXK = 200;

int t = 0;
int n, m;

vector<pair<int, int>> g[MAXN];
pair<int, int> dp[MAXN][MAXK];
int tin[MAXN], tout[MAXN];
int r[MAXN][2];
int parent_weight[MAXN];

bool is_ancestor(int u, int v) {
    return (tout[v] <= tout[u] && tin[v] >= tin[u]);
}

int lca(int u, int v) {
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = ceil(log2(n)); i >= 0; --i)
        if (!is_ancestor(dp[u][i].first, v))
            u = dp[u][i].first;

    return dp[u][0].first;
}

void dfs(int u, int v) {
    t++;
    tin[u] = t;

    dp[u][0] = make_pair(v, parent_weight[u]);

    for (int i = 1; i < ceil(log2(n)) + 1; i++) {
        dp[u][i].first = dp[dp[u][i - 1].first][i - 1].first;
        dp[u][i].second = min(dp[dp[u][i - 1].first][i - 1].second, dp[u][i - 1].second);
    }

    for (pair<int, int> vert : g[u])
        if (v != vert.first)
            dfs(vert.first, u);

    tout[u] = t;
    t++;
}

int path_weight(int u, int v) {
    int w = INFINITY;

    for (int i = ceil(log2(n)); i >= 0; i--) {
        int cur_v = dp[u][i].first;
        int cur_w = dp[u][i].second;
        if (!is_ancestor(cur_v, v)) {
            w = min(w, cur_w);
            u = cur_v;
        }
    }

    if (u == v)
        return w;
    else
        return min(w, dp[u][0].second);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("/home/drundolet/Projects/SPbU-homework/Semester_6/graph_algos/input.txt", "r", stdin);

    cin >> n;
    for (int i = 2; i < n + 1; i++) {
        int v, w;
        cin >> v >> w;
        g[v].emplace_back(i, w);
        parent_weight[i] = w;
    }

    dfs(1, 1);

    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> r[i][0] >> r[i][1];

    for (int i = 0; i < m; i++) {
        int parent = lca(r[i][0], r[i][1]);
        cout << min(path_weight(r[i][0], parent), path_weight((r[i][1]), parent)) << '\n';
    }

    return 0;
}