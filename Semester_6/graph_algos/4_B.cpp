#include <vector>
#include <iostream>

using namespace std;
#define INF 2147483647

int n = 20;
int weight[20][20];
vector<vector<int>> dp((((1 << n) - 1)), vector<int>(20, INF));
vector<int> final_path;
vector<int> path(0);
int global_answer = INF;

int tsp(int mask, int pos, int w) {
    if(mask == ((1 << n) - 1)) {
        if (w < global_answer) {
            global_answer = w;
            final_path = path;
        }
        return weight[pos][0];
    }

    if(dp[mask][pos] != INF)
        return dp[mask][pos];

    for(int v = 1; v < n; ++v) {
        if(v == pos || (mask & (1 << v)))
            continue;
        path.push_back(v);
        int answer = weight[v][pos] + tsp(mask | (1 << v), v, w + weight[pos][v]);
        path.pop_back();
        if(answer < dp[mask][pos])
            dp[mask][pos] = answer;
    }

    return dp[mask][pos];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("/home/drundolet/Projects/SPbU-homework/Semester_6/graph_algos/input.txt", "r", stdin);

    cin >> n;
    n++;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || j == 0)
                weight[i][j] = 0;
            else
                cin >> weight[i][j];
        }
    }

    cout << tsp(1, 0, 0) << endl;
    for (auto v : final_path) {
        cout << v << ' ';
    }

    return 0;
}