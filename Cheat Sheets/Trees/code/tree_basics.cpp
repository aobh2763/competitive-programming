// Tree basics, all ITERATIVE (no recursion depth issues at n = 2e5+)
// One pass (O(n)) gives: parent, depth, subtree size, tin/tout (Euler tour)
// Diameter via two BFS passes: O(n)
// Subtree of v = positions [tin[v], tout[v]) in the DFS order.
#include <bits/stdc++.h>
using namespace std;

struct Tree {
    int n;
    vector<vector<int>> adj;
    vector<int> par, depth, sz, tin, tout, order;

    // Empty tree with n nodes (0-indexed).
    Tree(int n) : n(n), adj(n) {}

    // Add an undirected edge u - v.
    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    // Iterative DFS from root. Fills par, depth, sz, tin, tout, order. O(n)
    // order[i] = node visited i-th; tout[v] = one past the last tin in v's subtree.
    void dfs(int root = 0) {
        par.assign(n, -1); depth.assign(n, 0); sz.assign(n, 1);
        tin.assign(n, 0); tout.assign(n, 0); order.clear();
        vector<int> st = {root}, it(n, 0);
        par[root] = -1;
        tin[root] = 0; order.push_back(root);
        while (!st.empty()) {
            int v = st.back();
            if (it[v] < (int)adj[v].size()) {
                int u = adj[v][it[v]++];
                if (u == par[v]) continue;
                par[u] = v;
                depth[u] = depth[v] + 1;
                tin[u] = order.size();
                order.push_back(u);
                st.push_back(u);
            } else {
                tout[v] = order.size();
                if (par[v] != -1) sz[par[v]] += sz[v];
                st.pop_back();
            }
        }
    }

    // BFS from src. Returns (farthest node, its distance in edges). O(n)
    pair<int, int> farthest(int src) {
        vector<int> d(n, -1);
        queue<int> q;
        q.push(src); d[src] = 0;
        int best = src;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            if (d[v] > d[best]) best = v;
            for (int u : adj[v]) if (d[u] < 0) { d[u] = d[v] + 1; q.push(u); }
        }
        return {best, d[best]};
    }

    // Tree diameter in edges: BFS to the farthest node a, then BFS from a. O(n)
    // (For weighted trees, swap BFS for a DFS that sums weights.)
    int diameter() {
        int a = farthest(0).first;
        return farthest(a).second;
    }

    // True if u is an ancestor of v (or u == v). Needs dfs() first. O(1)
    bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }
};

#ifdef LOCAL
int main() {
    Tree t(6);
    t.add_edge(0, 1); t.add_edge(0, 2); t.add_edge(1, 3);
    t.add_edge(1, 4); t.add_edge(4, 5);
    t.dfs(0);
    cout << t.sz[1] << "\n";                // 4
    cout << t.diameter() << "\n";           // 4 (2-0-1-4-5)
    cout << t.is_ancestor(1, 5) << "\n";    // 1
}
#endif
