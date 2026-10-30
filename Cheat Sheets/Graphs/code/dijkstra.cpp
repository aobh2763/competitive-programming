// Dijkstra (non-negative weights) + 0-1 BFS
// Dijkstra: O((n + m) log n). 0-1 BFS: O(n + m).
// Never use Dijkstra with NEGATIVE edges (use bellman_ford.cpp).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX / 4;   // large, but dist + w cannot overflow

struct Dijkstra {
    int n;
    vector<vector<pair<int, ll>>> adj;   // adj[v] = {(to, weight)}

    // Graph with n nodes (0-indexed).
    Dijkstra(int n = 0) : n(n), adj(n) {}

    // Add edge u - v of weight w (or u -> v when directed = true).
    void add_edge(int u, int v, ll w, bool directed = false) {
        adj[u].push_back({v, w});
        if (!directed) adj[v].push_back({u, w});
    }

    // Shortest distances from src (INF = unreachable). Optional parent array.
    // Lazy deletion: skip heap entries that are already outdated.
    vector<ll> run(int src, vector<int>* par = nullptr) {
        vector<ll> d(n, INF);
        if (par) par->assign(n, -1);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        d[src] = 0;
        pq.push({0, src});
        while (!pq.empty()) {
            auto [dv, v] = pq.top(); pq.pop();
            if (dv > d[v]) continue;
            for (auto [u, w] : adj[v]) if (dv + w < d[u]) {
                d[u] = dv + w;
                if (par) (*par)[u] = v;
                pq.push({d[u], u});
            }
        }
        return d;
    }

    // Shortest distances when EVERY edge weight is 0 or 1. Deque instead of heap.
    // 0-weight edges push to the front, 1-weight edges to the back.
    vector<ll> zero_one_bfs(int src) {
        vector<ll> d(n, INF);
        deque<int> dq;
        d[src] = 0;
        dq.push_back(src);
        while (!dq.empty()) {
            int v = dq.front(); dq.pop_front();
            for (auto [u, w] : adj[v]) if (d[v] + w < d[u]) {
                d[u] = d[v] + w;
                if (w == 0) dq.push_front(u); else dq.push_back(u);
            }
        }
        return d;
    }

    // Rebuild path src -> t from the parent array. Empty if unreachable.
    static vector<int> path(const vector<int>& par, int src, int t) {
        vector<int> p;
        if (t != src && par[t] == -1) return p;
        for (int v = t; v != -1; v = par[v]) p.push_back(v);
        reverse(p.begin(), p.end());
        return p;
    }
};

#ifdef LOCAL
int main() {
    Dijkstra g(5);
    g.add_edge(0, 1, 4); g.add_edge(0, 2, 1); g.add_edge(2, 1, 2);
    g.add_edge(1, 3, 5); g.add_edge(2, 3, 8);
    vector<int> par;
    auto d = g.run(0, &par);
    cout << d[3] << " " << (d[4] == INF) << "\n";          // 8 1
    for (int v : Dijkstra::path(par, 0, 3)) cout << v << " "; // 0 2 1 3
    cout << "\n";
}
#endif
