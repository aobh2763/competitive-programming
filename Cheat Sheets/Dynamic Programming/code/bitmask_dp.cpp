// Bitmask DP: the state is a SUBSET of up to ~20 items stored as an integer mask.
//  tsp (Held-Karp), assignment problem, counting Hamiltonian paths, bin packing.
// Typical cost O(2^n * n) to O(2^n * n^2). Practical for n <= 20 (n <= 16 for n^2 versions).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX / 4;

// Travelling salesman (Held-Karp): shortest tour starting and ending at node 0 that visits
// every node once. dp[mask][v] = shortest path from 0 visiting exactly `mask`, ending at v.
// O(2^n * n^2) time, O(2^n * n) memory. Returns INF if no tour exists (INF edges).
ll tsp(const vector<vector<ll>>& d) {
    int n = d.size();
    if (n == 1) return 0;
    vector<vector<ll>> dp(1 << n, vector<ll>(n, INF));
    dp[1][0] = 0;
    for (int mask = 1; mask < (1 << n); mask += 2)          // only masks containing node 0
        for (int v = 0; v < n; v++) {
            if (dp[mask][v] >= INF || !(mask >> v & 1)) continue;
            for (int u = 0; u < n; u++) {
                if (mask >> u & 1 || d[v][u] >= INF) continue;
                dp[mask | 1 << u][u] = min(dp[mask | 1 << u][u], dp[mask][v] + d[v][u]);
            }
        }
    ll best = INF;
    for (int v = 1; v < n; v++)
        if (dp[(1 << n) - 1][v] < INF && d[v][0] < INF) best = min(best, dp[(1 << n) - 1][v] + d[v][0]);
    return best;
}

// Assignment problem: n workers, n jobs, cost[i][j]. Minimum total cost of giving each worker
// a different job. dp[mask] = best cost for the first popcount(mask) workers using jobs in
// `mask`. O(2^n * n). (For n > 20 use the Hungarian algorithm.)
ll assignment(const vector<vector<ll>>& cost) {
    int n = cost.size();
    vector<ll> dp(1 << n, INF);
    dp[0] = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] >= INF) continue;
        int i = __builtin_popcount(mask);                   // next worker to assign
        if (i == n) continue;
        for (int j = 0; j < n; j++)
            if (!(mask >> j & 1)) dp[mask | 1 << j] = min(dp[mask | 1 << j], dp[mask] + cost[i][j]);
    }
    return dp[(1 << n) - 1];
}

// Number of Hamiltonian paths (visit every node exactly once, any start and end) in a
// directed graph given by adjacency matrix adj[u][v] = 1 if edge u -> v. O(2^n * n^2)
ll count_hamiltonian_paths(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<vector<ll>> dp(1 << n, vector<ll>(n, 0));
    for (int v = 0; v < n; v++) dp[1 << v][v] = 1;
    for (int mask = 1; mask < (1 << n); mask++)
        for (int v = 0; v < n; v++) {
            if (!dp[mask][v]) continue;
            for (int u = 0; u < n; u++)
                if (!(mask >> u & 1) && adj[v][u]) dp[mask | 1 << u][u] += dp[mask][v];
        }
    ll total = 0;
    for (int v = 0; v < n; v++) total += dp[(1 << n) - 1][v];
    return total;
}

// Bin packing: fewest bins of capacity `cap` needed to hold all items (each item <= cap).
// dp[mask] = (bins used, load of the last bin) minimised lexicographically. O(2^n * n)
int min_bins(const vector<int>& w, int cap) {
    int n = w.size();
    vector<pair<int, int>> dp(1 << n, {n + 1, 0});
    dp[0] = {1, 0};
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask].first > n) continue;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) continue;
            pair<int, int> nxt = dp[mask];
            if (nxt.second + w[i] <= cap) nxt.second += w[i];
            else { nxt.first++; nxt.second = w[i]; }
            dp[mask | 1 << i] = min(dp[mask | 1 << i], nxt);
        }
    }
    return dp[(1 << n) - 1].first;
}

#ifdef LOCAL
int main() {
    vector<vector<ll>> d = {{0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
    cout << tsp(d) << "\n";                                        // 80
    cout << assignment({{9, 2, 7, 8}, {6, 4, 3, 7}, {5, 8, 1, 8}, {7, 6, 9, 4}}) << "\n";  // 13
    vector<vector<int>> g = {{0, 1, 1}, {1, 0, 1}, {1, 1, 0}};
    cout << count_hamiltonian_paths(g) << "\n";                    // 6
    cout << min_bins({4, 8, 1, 4, 2, 1}, 10) << "\n";              // 2
}
#endif
