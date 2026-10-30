// LCA with binary lifting
// Preprocess: O(n log n) time and memory. Query: O(log n).
// Also gives k-th ancestor and distance between nodes.
// Iterative DFS for tin/tout, so it is safe on deep (path-like) trees.
#include <bits/stdc++.h>
using namespace std;

struct LCA {
    int n, LOG;
    vector<vector<int>> adj, up;    // up[j][v] = 2^j-th ancestor of v (root's ancestors = root)
    vector<int> depth, tin, tout;

    // Tree with n nodes (0-indexed). LOG = enough bits to cover depth < n.
    LCA(int n) : n(n), LOG(max(1, 32 - __builtin_clz(max(n, 2)))), adj(n) {}

    // Add an undirected edge u - v.
    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    // Iterative DFS for depth/tin/tout/parent, then fill the lifting table. O(n log n)
    void build(int root = 0) {
        up.assign(LOG, vector<int>(n, root));
        depth.assign(n, 0); tin.assign(n, 0); tout.assign(n, 0);
        vector<int> st = {root}, it(n, 0);
        int timer = 0;
        tin[root] = timer++;
        while (!st.empty()) {
            int v = st.back();
            if (it[v] < (int)adj[v].size()) {
                int u = adj[v][it[v]++];
                if (u == up[0][v]) continue;
                up[0][u] = v;
                depth[u] = depth[v] + 1;
                tin[u] = timer++;
                st.push_back(u);
            } else {
                tout[v] = timer;
                st.pop_back();
            }
        }
        for (int j = 1; j < LOG; j++)
            for (int v = 0; v < n; v++)
                up[j][v] = up[j - 1][up[j - 1][v]];
    }

    // True if u is an ancestor of v (or u == v). O(1)
    bool is_ancestor(int u, int v) { return tin[u] <= tin[v] && tout[v] <= tout[u]; }

    // Lowest common ancestor of u and v. O(log n)
    // Lift u while its ancestor still does NOT cover v; the answer is then the parent.
    int lca(int u, int v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int j = LOG - 1; j >= 0; j--)
            if (!is_ancestor(up[j][u], v)) u = up[j][u];
        return up[0][u];
    }

    // The k-th ancestor of v (k = 1 is the parent). Returns root if k > depth. O(log n)
    int kth_ancestor(int v, int k) {
        for (int j = 0; j < LOG; j++)
            if (k >> j & 1) v = up[j][v];
        return v;
    }

    // Number of edges on the path u - v. O(log n)
    int dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }
};

#ifdef LOCAL
int main() {
    LCA t(6);
    t.add_edge(0, 1); t.add_edge(0, 2); t.add_edge(1, 3);
    t.add_edge(1, 4); t.add_edge(4, 5);
    t.build(0);
    cout << t.lca(3, 5) << "\n";   // 1
    cout << t.lca(2, 5) << "\n";   // 0
    cout << t.dist(3, 5) << "\n";  // 3
}
#endif
