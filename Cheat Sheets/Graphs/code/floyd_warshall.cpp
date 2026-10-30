// Floyd-Warshall: all-pairs shortest paths. O(n^3) time, O(n^2) memory.
// Good for n <= ~400-500. Handles negative edges; detects negative cycles.
// Also usable for transitive closure (reachability) with booleans/bitsets.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX / 4;

struct Floyd {
    int n;
    vector<vector<ll>> d;       // d[i][j] = shortest distance i -> j
    vector<vector<int>> nxt;    // nxt[i][j] = first step on the best path i -> j

    // n nodes, no edges; d[i][i] = 0.
    Floyd(int n = 0) : n(n), d(n, vector<ll>(n, INF)), nxt(n, vector<int>(n, -1)) {
        for (int i = 0; i < n; i++) { d[i][i] = 0; nxt[i][i] = i; }
    }

    // Add edge u - v (or u -> v when directed). Keeps the minimum for multi-edges.
    void add_edge(int u, int v, ll w, bool directed = false) {
        if (w < d[u][v]) { d[u][v] = w; nxt[u][v] = v; }
        if (!directed && w < d[v][u]) { d[v][u] = w; nxt[v][u] = u; }
    }

    // Run the DP: allow node k as an intermediate, for k = 0..n-1. O(n^3)
    // k MUST be the outermost loop.
    void run() {
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++) {
                if (d[i][k] == INF) continue;
                for (int j = 0; j < n; j++) {
                    if (d[k][j] == INF) continue;
                    if (d[i][k] + d[k][j] < d[i][j]) {
                        d[i][j] = d[i][k] + d[k][j];
                        nxt[i][j] = nxt[i][k];
                    }
                }
            }
    }

    // True if some node can reach itself with negative total weight. Call after run().
    bool has_negative_cycle() {
        for (int i = 0; i < n; i++) if (d[i][i] < 0) return true;
        return false;
    }

    // Path u -> v as a node list, empty if unreachable.
    // Only meaningful when there is no negative cycle.
    vector<int> path(int u, int v) {
        vector<int> p;
        if (d[u][v] == INF) return p;
        for (; u != v; u = nxt[u][v]) p.push_back(u);
        p.push_back(v);
        return p;
    }
};

#ifdef LOCAL
int main() {
    Floyd f(4);
    f.add_edge(0, 1, 3, true); f.add_edge(1, 2, 1, true);
    f.add_edge(0, 2, 7, true); f.add_edge(2, 3, 2, true);
    f.run();
    cout << f.d[0][3] << "\n";                           // 6
    for (int v : f.path(0, 3)) cout << v << " ";         // 0 1 2 3
    cout << "\n" << f.has_negative_cycle() << "\n";      // 0
}
#endif
