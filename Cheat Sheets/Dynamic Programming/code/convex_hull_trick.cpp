// Li Chao tree: maintain a set of lines y = m*x + b, add lines in any order,
// and query the MINIMUM value at any integer x in [lo, hi]. O(log(hi - lo)) per operation.
// Speeds up DPs of the form   dp[i] = min over j < i of ( dp[j] + b_j + m_j * x_i )
// (the cost splits into a part depending on j and a part multiplying something about i).
// For a MAXIMUM query add the negated lines and negate the answer.
// Values must stay within ~4e18: keep |m * x| + |b| below that.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll LINF = 4e18;

struct Line {
    ll m, b;
    // Value of the line at x.
    ll eval(ll x) const { return m * x + b; }
};

struct LiChao {
    ll lo, hi;
    struct Node { Line ln{0, LINF}; int l = -1, r = -1; };
    vector<Node> t;

    // Tree over integer queries x in [lo, hi]. Nodes are created lazily.
    LiChao(ll lo, ll hi) : lo(lo), hi(hi), t(1) {}

    // Insert a line. Walk down: at every node keep the line that is better in the middle,
    // push the loser into the half where it could still win. O(log(hi - lo))
    void add_line(Line nw) {
        int idx = 0;
        ll l = lo, r = hi;
        while (true) {
            ll m = l + (r - l) / 2;
            bool left_better = nw.eval(l) < t[idx].ln.eval(l);
            bool mid_better = nw.eval(m) < t[idx].ln.eval(m);
            if (mid_better) swap(t[idx].ln, nw);
            if (l == r) return;
            if (left_better != mid_better) {              // crossing is in the left half
                if (t[idx].l == -1) { t[idx].l = t.size(); t.push_back(Node()); }
                idx = t[idx].l; r = m;
            } else {                                      // crossing is in the right half
                if (t[idx].r == -1) { t[idx].r = t.size(); t.push_back(Node()); }
                idx = t[idx].r; l = m + 1;
            }
        }
    }

    // Minimum over all inserted lines at x (LINF if no line was added). O(log(hi - lo))
    ll query(ll x) const {
        ll best = LINF;
        int idx = 0;
        ll l = lo, r = hi;
        while (idx != -1) {
            best = min(best, t[idx].ln.eval(x));
            if (l == r) break;
            ll m = l + (r - l) / 2;
            if (x <= m) { idx = t[idx].l; r = m; }
            else        { idx = t[idx].r; l = m + 1; }
        }
        return best;
    }
};

// Example DP: split the sorted positions x[0..n) into consecutive groups; a group [j, i)
// costs (x[i-1] - x[j])^2 + C. Minimise the total. dp[i] = min_j dp[j] + (x[i-1]-x[j])^2 + C.
// Expand: dp[j] + x[j]^2 - 2*x[j]*x[i-1] + x[i-1]^2 + C  => line (m = -2x[j], b = dp[j] + x[j]^2)
// queried at x[i-1]. O(n log range) instead of O(n^2). (x must satisfy |x| <= ~1e9.)
ll split_cost_dp(const vector<ll>& x, ll C) {
    int n = x.size();
    LiChao lc(*min_element(x.begin(), x.end()), *max_element(x.begin(), x.end()));
    vector<ll> dp(n + 1, 0);
    lc.add_line({-2 * x[0], dp[0] + x[0] * x[0]});
    for (int i = 1; i <= n; i++) {
        dp[i] = lc.query(x[i - 1]) + x[i - 1] * x[i - 1] + C;
        if (i < n) lc.add_line({-2 * x[i], dp[i] + x[i] * x[i]});
    }
    return dp[n];
}

#ifdef LOCAL
int main() {
    LiChao lc(-10, 10);
    lc.add_line({2, 1});            // y = 2x + 1
    lc.add_line({-1, 5});           // y = -x + 5
    lc.add_line({0, 3});            // y = 3
    cout << lc.query(0) << " " << lc.query(4) << " " << lc.query(-5) << "\n";   // 1 1 -9
    cout << split_cost_dp({1, 2, 3, 10, 11, 12}, 5) << "\n";       // 18
}
#endif
