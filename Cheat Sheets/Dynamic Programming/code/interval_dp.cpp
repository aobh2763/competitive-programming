// Interval DP: the state is a segment [i, j]; solve short segments first, then combine
// two smaller segments split at some point k. Typical cost O(n^3).
//  matrix chain multiplication, merging adjacent piles, minimum palindrome cuts, burst balloons.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX / 4;

// Matrix chain: matrix i has size dims[i] x dims[i+1] (n matrices => dims has n+1 entries).
// Minimum number of scalar multiplications to multiply them all in the best order.
// dp[i][j] = min over split k of dp[i][k] + dp[k+1][j] + dims[i] * dims[k+1] * dims[j+1]. O(n^3)
ll matrix_chain(const vector<ll>& dims) {
    int n = dims.size() - 1;
    if (n <= 0) return 0;
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    for (int len = 2; len <= n; len++)
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INF;
            for (int k = i; k < j; k++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1]);
        }
    return dp[0][n - 1];
}

// Merge adjacent piles: merging two neighbouring piles costs the sum of their sizes.
// Minimum total cost to merge all piles into one. (If ANY two piles may be merged, use a
// min-heap greedy instead.)  dp[i][j] = min over k of dp[i][k] + dp[k+1][j] + sum(i..j). O(n^3)
// The cost function satisfies Knuth's condition, so dp_optimizations.cpp can make it O(n^2).
ll merge_piles(const vector<ll>& a) {
    int n = a.size();
    if (n <= 1) return 0;
    vector<ll> P(n + 1, 0);
    for (int i = 0; i < n; i++) P[i + 1] = P[i] + a[i];
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    for (int len = 2; len <= n; len++)
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INF;
            for (int k = i; k < j; k++) dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            dp[i][j] += P[j + 1] - P[i];
        }
    return dp[0][n - 1];
}

// Fewest cuts so that every piece of s is a palindrome. O(n^2)
// is_pal[i][j] says whether s[i..j] is a palindrome; cuts[j] = best for the prefix s[0..j].
int min_palindrome_cuts(const string& s) {
    int n = s.size();
    if (n == 0) return 0;
    vector<vector<char>> is_pal(n, vector<char>(n, 0));
    for (int i = n - 1; i >= 0; i--)
        for (int j = i; j < n; j++)
            is_pal[i][j] = s[i] == s[j] && (j - i < 2 || is_pal[i + 1][j - 1]);
    vector<int> cuts(n);
    for (int j = 0; j < n; j++) {
        if (is_pal[0][j]) { cuts[j] = 0; continue; }
        cuts[j] = INT_MAX;
        for (int i = 1; i <= j; i++) if (is_pal[i][j]) cuts[j] = min(cuts[j], cuts[i - 1] + 1);
    }
    return cuts[n - 1];
}

// Burst balloons: bursting balloon k with current neighbours l and r gives a[l] * a[k] * a[r]
// coins (out-of-range neighbours count as 1). Max coins for bursting all balloons.
// Trick: let k be the LAST balloon burst in the open interval (i, j). O(n^3)
ll burst_balloons(const vector<ll>& a) {
    int n = a.size();
    vector<ll> b(n + 2, 1);
    for (int i = 0; i < n; i++) b[i + 1] = a[i];
    vector<vector<ll>> dp(n + 2, vector<ll>(n + 2, 0));     // dp[i][j]: best for balloons strictly between i and j
    for (int len = 2; len <= n + 1; len++)
        for (int i = 0; i + len <= n + 1; i++) {
            int j = i + len;
            for (int k = i + 1; k < j; k++)
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + b[i] * b[k] * b[j]);
        }
    return dp[0][n + 1];
}

#ifdef LOCAL
int main() {
    cout << matrix_chain({10, 30, 5, 60}) << "\n";                 // 4500
    cout << merge_piles({4, 1, 1, 4}) << "\n";                     // 18
    cout << min_palindrome_cuts("aab") << "\n";                    // 1
    cout << burst_balloons({3, 1, 5, 8}) << "\n";                  // 167
}
#endif
