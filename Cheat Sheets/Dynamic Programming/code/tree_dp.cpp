// DP on trees (iterative, safe for n = 2e5 chains): root the tree, process nodes children-first.
//  subtree sizes, maximum weight independent set, diameter, and REROOTING
//  (sum of distances from every node to all others in O(n)).
// Idea: dp[v] depends only on dp of v's children, so go through BFS order BACKWARDS.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct TreeDP {
    int n;
    vector<vector<int>> adj;
    vector<int> par, order, sz;     // order = BFS order from the root (parents first)

    // Tree with n nodes (0-indexed).
    TreeDP(int n) : n(n), adj(n) {}

    // Add an undirected edge u - v.
    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    // Root the tree: fills par, order (BFS order) and subtree sizes. O(n)
    void root(int r = 0) {
        par.assign(n, -1); order.clear(); sz.assign(n, 1);
        order.push_back(r);
        for (int i = 0; i < (int)order.size(); i++) {
            int v = order[i];
            for (int u : adj[v]) if (u != par[v]) { par[u] = v; order.push_back(u); }
        }
        for (int i = n - 1; i > 0; i--) sz[par[order[i]]] += sz[order[i]];
    }

    // Maximum total weight of a set of nodes with no two ADJACENT (weights >= 0). O(n)
    // dp0[v] = best in v's subtree if v is NOT chosen, dp1[v] = best if v IS chosen.
    ll max_independent_set(const vector<ll>& w) {
        vector<ll> dp0(n, 0), dp1(n, 0);
        for (int i = n - 1; i >= 0; i--) {
            int v = order[i];
            dp1[v] += w[v];                                   // children already added their part
            if (par[v] != -1) {
                dp0[par[v]] += max(dp0[v], dp1[v]);           // parent not chosen: child free
                dp1[par[v]] += dp0[v];                        // parent chosen: child must not be
            }
        }
        return max(dp0[order[0]], dp1[order[0]]);
    }

    // Diameter in edges. down[v] = longest downward path from v; combine the two best children.
    int diameter() {
        vector<int> down(n, 0);
        int best = 0;
        for (int i = n - 1; i >= 0; i--) {
            int v = order[i], top1 = 0, top2 = 0;
            for (int u : adj[v]) if (u != par[v]) {
                int d = down[u] + 1;
                if (d > top1) { top2 = top1; top1 = d; } else if (d > top2) top2 = d;
            }
            down[v] = top1;
            best = max(best, top1 + top2);
        }
        return best;
    }

    // REROOTING: ans[v] = sum of distances from v to every other node, for ALL v, in O(n).
    // Pass 1 (bottom-up): down[v] = sum of distances from v to nodes in its subtree.
    // Pass 2 (top-down): moving the root from v to child c brings sz[c] nodes one step
    // closer and pushes the other n - sz[c] nodes one step farther.
    vector<ll> sum_of_distances() {
        vector<ll> down(n, 0), ans(n, 0);
        for (int i = n - 1; i > 0; i--) {
            int v = order[i];
            down[par[v]] += down[v] + sz[v];
        }
        ans[order[0]] = down[order[0]];
        for (int i = 1; i < n; i++) {
            int v = order[i];
            ans[v] = ans[par[v]] - sz[v] + (n - sz[v]);
        }
        return ans;
    }
};

#ifdef LOCAL
int main() {
    TreeDP t(5);
    t.add_edge(0, 1); t.add_edge(0, 2); t.add_edge(1, 3); t.add_edge(1, 4);
    t.root(0);
    cout << t.sz[1] << " " << t.diameter() << "\n";                // 3 3
    cout << t.max_independent_set({1, 2, 3, 4, 5}) << "\n";        // 12 (nodes 2, 3, 4)
    auto d = t.sum_of_distances();
    cout << d[0] << " " << d[1] << " " << d[3] << "\n";            // 6 5 8
}
#endif
