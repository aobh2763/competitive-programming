// Bridges and articulation points (cut vertices), undirected graph. O(n + m)
// Bridge: an edge whose removal disconnects its component.
// Articulation point: a vertex whose removal disconnects its component.
// Iterative DFS with edge ids, so multi-edges are handled correctly
// (two parallel edges are NOT bridges) and deep graphs don't overflow the stack.
#include <bits/stdc++.h>
using namespace std;

struct Bridges {
    int n, m = 0;
    vector<vector<pair<int, int>>> adj;     // (neighbour, edge id)
    vector<int> bridges;                    // ids of bridge edges
    vector<char> is_art;                    // is_art[v] = v is a cut vertex

    // n nodes (0-indexed).
    Bridges(int n = 0) : n(n), adj(n) {}

    // Add undirected edge u - v. Edge ids are assigned in call order (0, 1, 2...).
    void add_edge(int u, int v) {
        adj[u].push_back({v, m});
        adj[v].push_back({u, m});
        m++;
    }

    // Compute bridges and articulation points using low-link values.
    // low[v] = smallest tin reachable from v's subtree using one back edge.
    //   edge (p, v) is a bridge          iff low[v] >  tin[p]
    //   p is a cut vertex because of v   iff low[v] >= tin[p]   (p non-root)
    //   root is a cut vertex             iff it has >= 2 DFS children
    void run() {
        bridges.clear();
        is_art.assign(n, 0);
        vector<int> tin(n, -1), low(n, 0), it(n, 0), pe(n, -1), par(n, -1);
        int timer = 0;
        for (int s = 0; s < n; s++) {
            if (tin[s] != -1) continue;
            int root_children = 0;
            vector<int> st = {s};
            tin[s] = low[s] = timer++;
            while (!st.empty()) {
                int v = st.back();
                if (it[v] < (int)adj[v].size()) {
                    auto [u, id] = adj[v][it[v]++];
                    if (id == pe[v]) continue;              // skip the edge we came by
                    if (tin[u] != -1) {
                        low[v] = min(low[v], tin[u]);       // back edge
                    } else {
                        pe[u] = id; par[u] = v;
                        tin[u] = low[u] = timer++;
                        st.push_back(u);
                    }
                } else {
                    st.pop_back();
                    if (st.empty()) break;
                    int p = st.back();
                    low[p] = min(low[p], low[v]);
                    if (low[v] > tin[p]) bridges.push_back(pe[v]);
                    if (p == s) root_children++;
                    else if (low[v] >= tin[p]) is_art[p] = 1;
                }
            }
            if (root_children >= 2) is_art[s] = 1;
        }
    }
};

#ifdef LOCAL
int main() {
    // triangle 0-1-2, bridge 2-3, triangle 3-4-5
    Bridges g(6);
    g.add_edge(0, 1); g.add_edge(1, 2); g.add_edge(2, 0);
    g.add_edge(2, 3);
    g.add_edge(3, 4); g.add_edge(4, 5); g.add_edge(5, 3);
    g.run();
    cout << g.bridges.size() << " " << g.bridges[0] << "\n";   // 1 3
    cout << (int)g.is_art[2] << (int)g.is_art[3] << (int)g.is_art[0] << "\n";  // 110
}
#endif
