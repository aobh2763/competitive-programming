// Bellman-Ford: single-source shortest paths with NEGATIVE edges.
// O(n * m). Detects negative cycles reachable from the source.
// Nodes whose distance is -INF are affected by (reachable from) a negative cycle.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX / 4;

struct BellmanFord {
    struct Edge { int u, v; ll w; };
    int n;
    vector<Edge> edges;

    // Graph with n nodes (0-indexed), edge list representation.
    BellmanFord(int n = 0) : n(n) {}

    // Add directed edge u -> v (weight w may be negative).
    // For an undirected NEGATIVE edge you get a negative cycle, so don't.
    void add_edge(int u, int v, ll w) { edges.push_back({u, v, w}); }

    // Distances from src. INF = unreachable, -INF = "arbitrarily small" (negative cycle).
    // Returns true if a negative cycle is reachable from src.
    bool run(int src, vector<ll>& dist) {
        dist.assign(n, INF);
        dist[src] = 0;
        // Phase 1: n - 1 rounds of relaxation (stop early if nothing changes).
        for (int i = 0; i < n - 1; i++) {
            bool changed = false;
            for (auto& e : edges)
                if (dist[e.u] < INF && dist[e.u] != -INF && dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.w;
                    changed = true;
                }
            if (!changed) return false;
        }
        // Phase 2: anything that can still be relaxed is on / behind a negative cycle.
        // Run n more rounds so the -INF mark spreads to every reachable node.
        bool neg = false;
        for (int i = 0; i < n; i++)
            for (auto& e : edges) {
                if (dist[e.u] == INF) continue;
                if (dist[e.u] == -INF) {
                    if (dist[e.v] != -INF) { dist[e.v] = -INF; neg = true; }
                } else if (dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = -INF;
                    neg = true;
                }
            }
        return neg;
    }
};

#ifdef LOCAL
int main() {
    BellmanFord g(5);
    g.add_edge(0, 1, 4); g.add_edge(0, 2, 5); g.add_edge(1, 2, -3); g.add_edge(2, 3, 2);
    vector<ll> d;
    bool neg = g.run(0, d);
    cout << neg << " " << d[3] << "\n";            // 0 3
    g.add_edge(3, 1, -1);                          // cycle 1->2->3->1 = -2
    neg = g.run(0, d);
    cout << neg << " " << (d[3] == -INF) << " " << (d[4] == INF) << "\n";  // 1 1 1
}
#endif
