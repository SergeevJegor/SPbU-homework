#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int MAXN = 100000;
const int MAXK = 200;

int t = 0;
int n, m;

int dp[MAXN][MAXK];
int tin[MAXN], tout[MAXN];
int r[MAXN][2];
vector<int> g[MAXN];

bool is_ancestor(int u, int v) {
    return (tout[v] <= tout[u] && tin[v] >= tin[u]);
}

int lca(int u, int v) {
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int k = ceil(log2(n)); k >= 0; --k)
        if (!is_ancestor(dp[u][k], v))
            u = dp[u][k];

    return dp[u][0];
}

void dfs(int u, int v) {
    t++;
    tin[u] = t;

    dp[u][0] = v;
    for (int i = 1; i < ceil(log2(n)) + 1; i++)
        dp[u][i] = dp[dp[u][i - 1]][i - 1];

    for (int vert : g[u])
        if (v != vert)
            dfs(vert, u);

    tout[u] = t;
    t++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("/home/drundolet/Projects/SPbU-homework/Semester_6/graph_algos/input.txt", "r", stdin);

    cin >> n;
    for (int i = 2; i < n + 1; i++) {
        int v;
        cin >> v;
        g[v].push_back(i);
    }

    dfs(1, 1);

    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> r[i][0] >> r[i][1];

    for (int i = 0; i < m; i++)
        cout << lca(r[i][0], r[i][1]) << '\n';

    return 0;
}