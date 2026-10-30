// Strongly Connected Components: iterative Tarjan. O(n + m)
// comp[v] = id of v's SCC. Tarjan finishes SINKS first, so comp ids are in
// REVERSE topological order: an edge between SCCs always goes from a
// higher id to a lower id. Condensation is therefore a DAG you can DP over
// by iterating ids from high to low (sources first) or low to high (sinks first).
#include <bits/stdc++.h>
using namespace std;

struct SCC {
    int n, count = 0;
    vector<vector<int>> adj;
    vector<int> comp;

    // n nodes (0-indexed), no edges.
    SCC(int n = 0) : n(n), adj(n) {}

    // Directed edge u -> v.
    void add_edge(int u, int v) { adj[u].push_back(v); }

    // Run Tarjan's algorithm with an explicit stack (no recursion). Fills comp, count.
    // num = discovery time, low = lowest discovery time reachable via the DFS subtree
    // plus at most one back/cross edge to a node still on the stack.
    void run() {
        comp.assign(n, -1);
        vector<int> num(n, -1), low(n, 0), it(n, 0), st, call;
        vector<char> on(n, 0);
        int timer = 0;
        count = 0;
        for (int s = 0; s < n; s++) {
            if (num[s] != -1) continue;
            num[s] = low[s] = timer++;
            st.push_back(s); on[s] = 1; call.push_back(s);
            while (!call.empty()) {
                int v = call.back();
                if (it[v] < (int)adj[v].size()) {
                    int u = adj[v][it[v]++];
                    if (num[u] == -1) {
                        num[u] = low[u] = timer++;
                        st.push_back(u); on[u] = 1; call.push_back(u);
                    } else if (on[u]) {
                        low[v] = min(low[v], num[u]);
                    }
                } else {
                    // v is the root of an SCC: pop everything above it from the stack.
                    if (low[v] == num[v]) {
                        while (true) {
                            int w = st.back(); st.pop_back();
                            on[w] = 0;
                            comp[w] = count;
                            if (w == v) break;
                        }
                        count++;
                    }
                    call.pop_back();
                    if (!call.empty()) {
                        int p = call.back();
                        low[p] = min(low[p], low[v]);
                    }
                }
            }
        }
    }

    // DAG of components (deduplicated edges, no self loops). Node ids = comp ids.
    vector<vector<int>> condensation() {
        vector<vector<int>> dag(count);
        for (int v = 0; v < n; v++)
            for (int u : adj[v]) if (comp[v] != comp[u]) dag[comp[v]].push_back(comp[u]);
        for (auto& a : dag) { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
        return dag;
    }
};

#ifdef LOCAL
int main() {
    SCC g(6);
    g.add_edge(0, 1); g.add_edge(1, 2); g.add_edge(2, 0);   // SCC {0,1,2}
    g.add_edge(2, 3); g.add_edge(3, 4); g.add_edge(4, 3);   // SCC {3,4}
    g.add_edge(4, 5);                                       // SCC {5}
    g.run();
    cout << g.count << "\n";                                // 3
    cout << (g.comp[0] == g.comp[2]) << (g.comp[3] == g.comp[4]) << (g.comp[0] == g.comp[3]) << "\n"; // 110
    cout << (g.comp[0] > g.comp[3]) << "\n";                // 1 (edge goes high -> low)
}
#endif
