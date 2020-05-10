#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("/home/drundolet/Projects/SPbU-homework/Semester_6/graph_algos/contest_1/input.txt", "r", stdin);

    int w, h, x2, y2, x1, y1;
    cin >> w >> h >> x1 >> y1 >> x2 >> y2;
    x1--;
    y1--;
    x2--;
    y2--;

    vector<vector<bool>> g(w, vector<bool>(h));
    vector<vector<pair<int, int>>> path(w, vector<pair<int, int>>(h));

    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            char cell;
            cin >> cell;
            g[i][j] = cell == '.';
        }
    }

    vector<vector<bool>> visited(w, vector<bool>(h, false));
    queue<pair<int, int>> q;
    q.push(make_pair(x2, y2));
    visited[x2][y2] = true;

    vector<int> x_diff = {-1, 1, 0, 0};
    vector<int> y_diff = {0, 0, -1, 1};

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

//        cout << "Current node: " << x + 1 << ' ' << y + 1 << '\n';

        if ((x == x1) && (y == y1)) {
            cout << "YES\n";

            int x_next = x1;
            int y_next = y1;
            cout << x_next + 1 << " " << y_next + 1 << '\n';
            do {
                pair<int, int> next = path[x_next][y_next];
                x_next = next.first;
                y_next = next.second;
                cout << x_next + 1 << " " << y_next + 1 << '\n';
            } while (x_next != x2 || y_next != y2);

            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int x_next = x + x_diff[i];
            int y_next = y + y_diff[i];

//            cout << "Next node: " << x_next << ' ' << y_next << '\n';

            if (x_next < 0 || x_next > w - 1 || y_next < 0 || y_next > h - 1) {
//                cout << "Fuckup at: " << x_next + 1 << " " << y_next + 1 << '\n';
                continue;
            }

            if (!visited[x_next][y_next] && g[x_next][y_next]) {
//                cout << x_next + 1 << ' ' << y_next + 1 << " -> " << x + 1 << ' ' << y + 1 << '\n';
                path[x_next][y_next] = make_pair(x, y);
                q.push(make_pair(x_next, y_next));
                visited[x_next][y_next] = true;
            }
        }
    }

    cout << "NO\n";

    return 0;
}
