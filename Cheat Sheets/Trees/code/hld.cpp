// Heavy-Light Decomposition (vertex values, sum queries)
// Build: O(n). Path query/update: O(log^2 n). Subtree query: O(log n). LCA: O(log n).
// Each node gets pos[v] so that (a) every heavy chain is contiguous and
// (b) subtree of v = [pos[v], pos[v] + sz[v]). A segment tree sits on top of pos.
// To get max instead of sum: change the combine in the segtree part and the path loop.
// Fully iterative, safe for n = 2e5 chains.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct HLD {
    int n;
    vector<vector<int>> adj;
    vector<int> par, dep, sz, heavy, head, pos;
    vector<ll> t;           // bottom-up segment tree (sum) over positions, size 2n

    // Tree with n nodes (0-indexed).
    HLD(int n) : n(n), adj(n) {}

    // Add an undirected edge u - v.
    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    // Compute par/dep/sz/heavy/head/pos, then load the node values into the segtree. O(n)
    // val[v] is the value stored on node v (pass {} for all zeros).
    void build(int root = 0, const vector<ll>& val = {}) {
        par.assign(n, -1); dep.assign(n, 0); sz.assign(n, 1);
        heavy.assign(n, -1); head.assign(n, root); pos.assign(n, 0);

        // BFS order gives parents before children; process it backwards for sizes.
        vector<int> ord = {root};
        for (int i = 0; i < (int)ord.size(); i++) {
            int v = ord[i];
            for (int u : adj[v]) if (u != par[v]) {
                par[u] = v; dep[u] = dep[v] + 1; ord.push_back(u);
            }
        }
        for (int i = n - 1; i > 0; i--) sz[par[ord[i]]] += sz[ord[i]];
        for (int i = 1; i < n; i++) {
            int v = ord[i], p = par[v];
            if (heavy[p] == -1 || sz[v] > sz[heavy[p]]) heavy[p] = v;
        }

        // Put the heavy child first so it receives pos[v] + 1 in the DFS below.
        for (int v = 0; v < n; v++)
            for (int i = 0; i < (int)adj[v].size(); i++)
                if (adj[v][i] == heavy[v]) { swap(adj[v][0], adj[v][i]); break; }

        // Iterative DFS assigning pos and head.
        int cur = 0;
        vector<int> st = {root}, it(n, 0);
        pos[root] = cur++;
        while (!st.empty()) {
            int v = st.back();
            if (it[v] < (int)adj[v].size()) {
                int u = adj[v][it[v]++];
                if (u == par[v]) continue;
                head[u] = (u == heavy[v]) ? head[v] : u;
                pos[u] = cur++;
                st.push_back(u);
            } else st.pop_back();
        }

        t.assign(2 * n, 0);
        for (int v = 0; v < n; v++) t[n + pos[v]] = val.empty() ? 0 : val[v];
        for (int i = n - 1; i >= 1; i--) t[i] = t[2 * i] + t[2 * i + 1];
    }

    // Segment tree point set: value at position i becomes x. O(log n)
    void seg_set(int i, ll x) {
        for (t[i += n] = x; i > 1; i >>= 1) t[i >> 1] = t[i] + t[i ^ 1];
    }

    // Segment tree sum over positions [l, r). O(log n)
    ll seg_query(int l, int r) {
        ll res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }

    // Set the value on node v to x. O(log n)
    void set_val(int v, ll x) { seg_set(pos[v], x); }

    // Sum of node values on the path u - v (both endpoints included). O(log^2 n)
    // Jump the deeper chain head upwards until both nodes share a chain.
    ll query_path(int u, int v) {
        ll res = 0;
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            res += seg_query(pos[head[u]], pos[u] + 1);
            u = par[head[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        return res + seg_query(pos[u], pos[v] + 1);
    }

    // Sum of node values in the subtree of v. O(log n)
    ll query_subtree(int v) { return seg_query(pos[v], pos[v] + sz[v]); }

    // Lowest common ancestor of u and v, using the same chain jumping. O(log n)
    int lca(int u, int v) {
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            u = par[head[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
};

#ifdef LOCAL
int main() {
    HLD h(6);
    h.add_edge(0, 1); h.add_edge(0, 2); h.add_edge(1, 3);
    h.add_edge(1, 4); h.add_edge(4, 5);
    h.build(0, {1, 2, 3, 4, 5, 6});
    cout << h.query_path(3, 5) << "\n";     // 4+2+5+6 = 17
    cout << h.query_subtree(1) << "\n";     // 2+4+5+6 = 17
    h.set_val(4, 100);
    cout << h.query_path(3, 5) << "\n";     // 4+2+100+6 = 112
    cout << h.lca(3, 5) << "\n";            // 1
}
#endif
