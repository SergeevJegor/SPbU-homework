#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<vector<int>> &g, vector<int> &color, int v, int c) {
    color[v] = c;

    for (int u : g[v]) {
        if (color[u] == 0) {
            dfs(g, color, u, 3 - c);
        } else if (color[u] == c) {
            cout << "NO";
            exit(0);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("/home/drundolet/Projects/SPbU-homework/Semester_6/graph_algos/input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n, vector<int>(0));

    for (int i = 0; i < m; i++) {
        int b, e;
        cin >> b >> e;
        g[b - 1].push_back(e - 1);
        g[e - 1].push_back(b - 1);
    }

    vector<int> color(n, 0);

    for (int i = 0; i < n; i++) {
        if (color[i] == 0)
            dfs(g, color, i, 1);
    }

    cout << "YES" << '\n';
    for (int i = 0; i < n; i++) {
        cout << color[i] << " ";
    }
    return 0;
}