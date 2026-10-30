// First DP patterns: 1D recurrences (stairs, house robber) and grid DP
// (min path sum, counting paths with obstacles, largest all-ones square).
// Recipe for every DP: 1) define the state  2) write the transition  3) set base cases
// 4) pick an evaluation order where dependencies are ready  5) read off the answer.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Number of ways to climb n stairs taking 1..k steps at a time, mod `mod`.
// State: dp[i] = ways to reach step i. Transition: dp[i] = dp[i-1] + ... + dp[i-k]. O(n * k)
ll climb_stairs(int n, int k, ll mod) {
    vector<ll> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k && j <= i; j++) dp[i] = (dp[i] + dp[i - j]) % mod;
    return dp[n];
}

// House robber: max sum of chosen elements with no two ADJACENT elements chosen.
// Choosing nothing is allowed (answer >= 0). State keeps two values: best if the previous
// element was taken / not taken. O(n), memory O(1).
ll max_sum_no_adjacent(const vector<ll>& a) {
    ll take = 0, skip = 0;                  // best total ending with a[i] taken / not taken
    for (ll x : a) {
        ll new_take = skip + x;
        skip = max(skip, take);
        take = new_take;
    }
    return max(take, skip);
}

// Minimum sum of a path from the top-left to the bottom-right moving only right or down.
// dp[i][j] = g[i][j] + min(dp[i-1][j], dp[i][j-1]). O(R * C)
ll min_path_sum(const vector<vector<ll>>& g) {
    int R = g.size(), C = g[0].size();
    vector<vector<ll>> dp(R, vector<ll>(C, 0));
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) { dp[i][j] = g[i][j]; continue; }
            ll best = LLONG_MAX;
            if (i > 0) best = min(best, dp[i - 1][j]);
            if (j > 0) best = min(best, dp[i][j - 1]);
            dp[i][j] = best + g[i][j];
        }
    return dp[R - 1][C - 1];
}

// Number of right/down paths from the top-left to the bottom-right avoiding '#' cells,
// mod `mod`. dp[i][j] = dp[i-1][j] + dp[i][j-1] for open cells. O(R * C)
ll count_paths(const vector<string>& g, ll mod) {
    int R = g.size(), C = g[0].size();
    vector<vector<ll>> dp(R, vector<ll>(C, 0));
    if (g[0][0] == '#') return 0;
    dp[0][0] = 1;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (g[i][j] == '#') { dp[i][j] = 0; continue; }
            if (i > 0) dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
            if (j > 0) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;
        }
    return dp[R - 1][C - 1] % mod;
}

// Side length of the largest square made only of '1' cells.
// dp[i][j] = side of the biggest square whose BOTTOM-RIGHT corner is (i, j):
// 1 + min(up, left, up-left) if the cell is '1'. O(R * C)
int largest_square(const vector<string>& g) {
    int R = g.size(), C = g[0].size(), best = 0;
    vector<vector<int>> dp(R, vector<int>(C, 0));
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (g[i][j] != '1') continue;
            if (i == 0 || j == 0) dp[i][j] = 1;
            else dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            best = max(best, dp[i][j]);
        }
    return best;
}

#ifdef LOCAL
int main() {
    cout << climb_stairs(5, 2, 1'000'000'007) << "\n";             // 8
    cout << max_sum_no_adjacent({2, 7, 9, 3, 1}) << "\n";          // 12 (2 + 9 + 1)
    cout << min_path_sum({{1, 3, 1}, {1, 5, 1}, {4, 2, 1}}) << "\n"; // 7
    cout << count_paths({"...", ".#.", "..."}, 1'000'000'007) << "\n"; // 2
    cout << largest_square({"10100", "10111", "11111", "10010"}) << "\n"; // 2
}
#endif
