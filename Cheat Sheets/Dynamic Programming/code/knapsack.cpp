// Knapsack family: 0/1, unbounded, bounded (binary splitting), item reconstruction,
// coin change (fewest coins, number of ways), and subset-sum with bitset.
// "dp[c]" = best answer using capacity / amount c. Complexity O(n * W) unless noted.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX / 4;

// 0/1 knapsack: each item used at most once. Max total value with total weight <= W.
// Capacity is iterated DOWNWARDS so an item cannot be reused. O(n * W), memory O(W).
ll knapsack01(const vector<int>& w, const vector<ll>& v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (int c = W; c >= w[i]; c--)
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[W];
}

// 0/1 knapsack that also returns WHICH items were taken (indices). O(n * W) time AND memory.
// take[i][c] remembers whether item i improved the best value at capacity c.
pair<ll, vector<int>> knapsack01_items(const vector<int>& w, const vector<ll>& v, int W) {
    int n = w.size();
    vector<ll> dp(W + 1, 0);
    vector<vector<char>> take(n, vector<char>(W + 1, 0));
    for (int i = 0; i < n; i++)
        for (int c = W; c >= w[i]; c--)
            if (dp[c - w[i]] + v[i] > dp[c]) { dp[c] = dp[c - w[i]] + v[i]; take[i][c] = 1; }
    vector<int> items;
    for (int i = n - 1, c = W; i >= 0; i--)
        if (take[i][c]) { items.push_back(i); c -= w[i]; }
    reverse(items.begin(), items.end());
    return {dp[W], items};
}

// Unbounded knapsack: each item may be used any number of times.
// Capacity is iterated UPWARDS so an item can be reused. O(n * W)
ll knapsack_unbounded(const vector<int>& w, const vector<ll>& v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (int c = w[i]; c <= W; c++)
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[W];
}

// Bounded knapsack: item i is available cnt[i] times. Split each count into powers of two
// (1, 2, 4, ..., remainder) so that any count 0..cnt[i] is a sum of some pieces, then run
// 0/1 knapsack on the pieces. O(n * log(cnt) * W)
ll knapsack_bounded(const vector<int>& w, const vector<ll>& v, const vector<int>& cnt, int W) {
    vector<int> w2;
    vector<ll> v2;
    for (size_t i = 0; i < w.size(); i++) {
        int c = cnt[i];
        for (int k = 1; c > 0; k <<= 1) {
            int take = min(k, c);
            w2.push_back(w[i] * take);
            v2.push_back(v[i] * take);
            c -= take;
        }
    }
    return knapsack01(w2, v2, W);
}

// Fewest coins to make `amount` (unlimited coins of each denomination). -1 if impossible.
// dp[s] = min over coins of dp[s - coin] + 1. O(n * amount)
ll min_coins(const vector<int>& coins, int amount) {
    vector<ll> dp(amount + 1, INF);
    dp[0] = 0;
    for (int s = 1; s <= amount; s++)
        for (int c : coins)
            if (c <= s && dp[s - c] < INF) dp[s] = min(dp[s], dp[s - c] + 1);
    return dp[amount] >= INF ? -1 : dp[amount];
}

// Number of COMBINATIONS (order does not matter: 1+2 and 2+1 are the same) that sum to amount.
// Coins in the OUTER loop => each multiset is counted once. O(n * amount)
ll count_combinations(const vector<int>& coins, int amount, ll mod) {
    vector<ll> dp(amount + 1, 0);
    dp[0] = 1;
    for (int c : coins)
        for (int s = c; s <= amount; s++) dp[s] = (dp[s] + dp[s - c]) % mod;
    return dp[amount];
}

// Number of ORDERED ways (1+2 and 2+1 count separately) that sum to amount.
// Amount in the OUTER loop => every sequence is counted. O(n * amount)
ll count_sequences(const vector<int>& coins, int amount, ll mod) {
    vector<ll> dp(amount + 1, 0);
    dp[0] = 1;
    for (int s = 1; s <= amount; s++)
        for (int c : coins) if (c <= s) dp[s] = (dp[s] + dp[s - c]) % mod;
    return dp[amount];
}

// All subset sums of a (each element used at most once) as a bitset: bit s is set iff
// some subset sums to s. N must be > the total sum. O(n * N / 64)
template<size_t N>
bitset<N> subset_sums(const vector<int>& a) {
    bitset<N> bs;
    bs[0] = 1;
    for (int x : a) bs |= bs << x;
    return bs;
}

#ifdef LOCAL
int main() {
    vector<int> w = {1, 3, 4, 5};
    vector<ll> v = {1, 4, 5, 7};
    cout << knapsack01(w, v, 7) << "\n";                          // 9 (items of weight 3 and 4)
    auto [best, items] = knapsack01_items(w, v, 7);
    cout << best << ":"; for (int i : items) cout << " " << i; cout << "\n";   // 9: 1 2
    cout << knapsack_unbounded(w, v, 7) << "\n";                  // 9
    cout << knapsack_bounded({2}, {3}, {2}, 7) << "\n";           // 6 (only two copies fit by count)
    cout << min_coins({1, 5, 6, 9}, 11) << "\n";                  // 2 (5 + 6)
    cout << count_combinations({1, 2, 5}, 5, 1'000'000'007) << " "
         << count_sequences({1, 2}, 4, 1'000'000'007) << "\n";    // 4 5
    auto bs = subset_sums<64>({3, 5, 7});
    cout << bs[8] << bs[9] << bs[15] << "\n";                     // 101
}
#endif
