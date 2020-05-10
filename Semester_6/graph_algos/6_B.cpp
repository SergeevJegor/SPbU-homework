
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int INF = INFINITY;

struct Edge {
    int next;
    int inv;
    int flow;
    int cap_flow;
    int cost;

    Edge(int next, int inv, int cap, int cost) : next(next), inv(inv), flow(0), cap_flow(cap), cost(cost) {}
};


struct Graph {
    int n;
    vector<vector<Edge>> e;
    vector<int> phi;
    vector<int> dest;
    vector<int> flags;
    vector<int> from;
    vector<pair<Edge *, int>> edges_list;

    Graph(int n) : n(n), e(n), phi(n), dest(n), flags(n), from(n) {}

    void AddDirectedEdge(int a, int b, int cap, int cost) {
        e[a].push_back(Edge(b, e[b].size(), cap, cost));
        e[b].push_back(Edge(a, e[a].size() - 1, 0, -cost));
    }

    void AddEdge(int a, int b, int cap) {
        auto entry_a = find_if(e[a].begin(), e[a].end(),
                               [&b = b](const Edge &edge) -> bool { return edge.next == b; });
        auto entry_b = find_if(e[b].begin(), e[b].end(),
                               [&a = a](const Edge &edge) -> bool { return edge.next == a; });

        if ((entry_a != e[a].end()) and (entry_b != e[b].end())) {
            entry_a->cap_flow += cap;
            entry_b->cap_flow += cap;
            edges_list.emplace_back(make_pair(entry_a.base(), cap));
        } else {
            e[a].push_back(Edge(b, e[b].size(), cap, 0));
            e[b].push_back(Edge(a, e[a].size() - 1, cap, 0));
            edges_list.emplace_back(make_pair(&e[a].back(), cap));
        }

    }

    pair<long long, long long> MinCostMaxFlow() {
        fill(phi.begin(), phi.end(), INF);
        phi[0] = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (phi[j] < INF)
                    for (int k = 0; k < e[j].size(); ++k)
                        if (e[j][k].cap_flow > 0 && phi[e[j][k].next] > phi[j] + e[j][k].cost)
                            phi[e[j][k].next] = phi[j] + e[j][k].cost;

        long long resultFlow = 0, resultCost = 0;

        for (;;) {
            fill(flags.begin(), flags.end(), 0);
            fill(dest.begin(), dest.end(), INF);
            dest[0] = 0;

            for (;;) {
                int i = -1;
                for (int j = 0; j < n; ++j)
                    if (!flags[j] && dest[j] < INF && (i < 0 || dest[i] > dest[j]))
                        i = j;
                if (i < 0) break;

                flags[i] = 1;

                for (int j = 0; j < e[i].size(); ++j)
                    if (e[i][j].cap_flow > e[i][j].flow) {
                        int a = e[i][j].next;
                        if (!flags[a] && dest[a] > dest[i] + e[i][j].cost + phi[i] - phi[a]) {
                            dest[a] = dest[i] + e[i][j].cost + phi[i] - phi[a];
                            from[a] = e[i][j].inv;
                        }
                    }
            }


            if (!flags[n - 1]) break;

            for (int i = 0; i < n; ++i)
                phi[i] += flags[i] ? dest[i] : dest[n - 1];

            long long augFlow = INF, augCost = 0;

            for (int i = n - 1; i != 0;) {
                int a = e[i][from[i]].next;
                int b = e[i][from[i]].inv;

                augFlow = min(augFlow, (long long) (e[a][b].cap_flow - e[a][b].flow));
                augCost += e[a][b].cost;

                i = a;
            }

            for (int i = n - 1; i != 0;) {
                int a = e[i][from[i]].next;
                int b = e[i][from[i]].inv;

                e[a][b].flow += augFlow;
                e[i][from[i]].flow -= augFlow;

                i = a;
            }

            resultFlow += augFlow;
            resultCost += augFlow * augCost;
        }

        return make_pair(resultFlow, resultCost);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("/home/drundolet/Projects/SPbU-homework/Semester_6/graph_algos/input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    Graph g(n);

    for (int i = 0, a, b, f, c; i < m; ++i) {
        cin >> a >> b >> f >> c;
        g.AddDirectedEdge(a - 1, b - 1, f, c);
    }


    auto answer = g.MinCostMaxFlow();
    cout << answer.second;

    return 0;
}
