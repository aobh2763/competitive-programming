// Minimum Spanning Tree via Kruskal (+ built-in DSU). O(m log m)
// If the graph is disconnected you get a minimum spanning FOREST
// and `connected` is false.
// Prim is better only for dense graphs with an adjacency matrix (O(n^2)).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge { int u, v; ll w; };

struct MSTResult {
    ll cost = 0;
    vector<int> used;       // indices (into the input edge vector) of chosen edges
    bool connected = false;
};

struct DSU {
    vector<int> p, sz;

    // n singleton sets.
    DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }

    // Root with path compression (iterative).
    int find(int v) { while (p[v] != v) v = p[v] = p[p[v]]; return v; }

    // Merge sets; false if already merged.
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b];
        return true;
    }
};

// Kruskal: sort edge indices by weight, take an edge iff it joins two components.
MSTResult kruskal(int n, const vector<Edge>& edges) {
    vector<int> idx(edges.size());
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) { return edges[a].w < edges[b].w; });
    DSU d(n);
    MSTResult r;
    for (int i : idx)
        if (d.unite(edges[i].u, edges[i].v)) {
            r.cost += edges[i].w;
            r.used.push_back(i);
        }
    r.connected = ((int)r.used.size() == n - 1) || n == 0;
    return r;
}

#ifdef LOCAL
int main() {
    vector<Edge> e = {{0, 1, 4}, {0, 2, 1}, {1, 2, 2}, {1, 3, 5}, {2, 3, 8}};
    auto r = kruskal(4, e);
    cout << r.cost << " " << r.connected << " " << r.used.size() << "\n";   // 8 1 3
}
#endif
