// Two classic DP speed-ups for transitions of the form "min over a split point":
//  1. Divide & conquer optimisation:  dp[j][i] = min_{p < i} dp[j-1][p] + cost(p, i)
//     O(k * n log n) instead of O(k * n^2), valid when opt(i) is monotone in i
//     (guaranteed if cost satisfies the quadrangle inequality).
//  2. Knuth optimisation (interval DP):  dp[i][j] = min_{i <= k < j} dp[i][k] + dp[k+1][j] + cost(i, j)
//     O(n^2) instead of O(n^3), valid when cost satisfies the quadrangle inequality
//     and is monotone on nested intervals (e.g. cost = sum of the segment, with positive values).
// ALWAYS check the condition (or stress-test against the slow DP): a wrong assumption
// silently gives wrong answers.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX / 4;

// Split positions 0..n into k non-empty consecutive groups; group (p, i] costs cost(p, i)
// (p < i, indices into 0..n). Returns the minimum total cost for exactly k groups.
// Layer j is computed from layer j-1 by divide & conquer on the monotone optimum. O(k n log n)
template<class Cost>
ll dc_optimization(int n, int k, Cost cost) {
    vector<ll> prev(n + 1, INF), cur(n + 1, INF);
    for (int i = 1; i <= n; i++) prev[i] = cost(0, i);          // layer 1: a single group
    // Fills cur[l..r] knowing the optimal split p lies in [optl, optr].
    function<void(int, int, int, int)> rec = [&](int l, int r, int optl, int optr) {
        if (l > r) return;
        int mid = (l + r) / 2;
        ll best = INF; int bp = optl;
        for (int p = optl; p <= min(mid - 1, optr); p++) {
            if (prev[p] >= INF) continue;
            ll val = prev[p] + cost(p, mid);
            if (val < best) { best = val; bp = p; }
        }
        cur[mid] = best;
        rec(l, mid - 1, optl, bp);
        rec(mid + 1, r, bp, optr);
    };
    for (int j = 2; j <= k; j++) {
        fill(cur.begin(), cur.end(), INF);
        rec(j, n, j - 1, n - 1);                                // layer j needs i >= j, p >= j-1
        swap(prev, cur);
    }
    return prev[n];
}

// Knuth optimisation for interval DP over items 0..n-1:
//   dp[i][j] = min over i <= m < j of dp[i][m] + dp[m+1][j] + cost(i, j),   dp[i][i] = 0.
// The best split opt[i][j] lies between opt[i][j-1] and opt[i+1][j], which shrinks the total
// work to O(n^2). cost(i, j) is the extra price of merging the whole segment [i, j].
template<class Cost>
ll knuth_optimization(int n, Cost cost) {
    if (n <= 1) return 0;
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    vector<vector<int>> opt(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) opt[i][i] = i;
    for (int len = 2; len <= n; len++)
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INF;
            for (int m = opt[i][j - 1]; m <= min(j - 1, opt[i + 1][j]); m++) {
                ll val = dp[i][m] + dp[m + 1][j] + cost(i, j);
                if (val < dp[i][j]) { dp[i][j] = val; opt[i][j] = m; }
            }
        }
    return dp[0][n - 1];
}

#ifdef LOCAL
int main() {
    vector<ll> a = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = a.size();
    vector<ll> P(n + 1, 0);
    for (int i = 0; i < n; i++) P[i + 1] = P[i] + a[i];
    // split into 3 groups minimising the sum of (group sum)^2
    cout << dc_optimization(n, 3, [&](int p, int i) { ll s = P[i] - P[p]; return s * s; }) << "\n";  // 341
    // merge adjacent piles (cost = segment sum) in O(n^2)
    cout << knuth_optimization(n, [&](int i, int j) { return P[j + 1] - P[i]; }) << "\n";            // 88
}
#endif
