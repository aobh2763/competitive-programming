// Recursive Lazy Segment Tree: range add, range sum
// Both operations: O(log n). 0-indexed, inclusive [l, r].
// To adapt: change the combine step in pull(), and apply()/push().
// (e.g. range assign: keep a "has assignment" flag instead of adding)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct LazySeg {
    int n;
    vector<ll> sum, lz;     // sum[x]: node sum, lz[x]: pending add for x's children

    // Tree over n elements, all zeros. O(n)
    LazySeg(int n) : n(n), sum(4 * n, 0), lz(4 * n, 0) {}

    // Recursive build of node x covering [l, r] from array a. O(n)
    void build(const vector<ll>& a, int x, int l, int r) {
        if (l == r) { sum[x] = a[l]; return; }
        int m = (l + r) / 2;
        build(a, 2 * x, l, m);
        build(a, 2 * x + 1, m + 1, r);
        pull(x);
    }

    // Public build from a (size n). O(n)
    void build(const vector<ll>& a) { build(a, 1, 0, n - 1); }

    // Recompute node x from its two children.
    void pull(int x) { sum[x] = sum[2 * x] + sum[2 * x + 1]; }

    // Add v to every element of node x's segment [l, r] and remember it for later.
    void apply(int x, int l, int r, ll v) {
        sum[x] += v * (r - l + 1);
        lz[x] += v;
    }

    // Send node x's pending add down to both children, then clear it.
    void push(int x, int l, int r) {
        if (lz[x] == 0) return;
        int m = (l + r) / 2;
        apply(2 * x, l, m, lz[x]);
        apply(2 * x + 1, m + 1, r, lz[x]);
        lz[x] = 0;
    }

    // Add v to a[ql..qr] (recursive part). O(log n)
    void update(int x, int l, int r, int ql, int qr, ll v) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { apply(x, l, r, v); return; }
        push(x, l, r);
        int m = (l + r) / 2;
        update(2 * x, l, m, ql, qr, v);
        update(2 * x + 1, m + 1, r, ql, qr, v);
        pull(x);
    }

    // Sum of a[ql..qr] (recursive part). O(log n)
    ll query(int x, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return sum[x];
        push(x, l, r);
        int m = (l + r) / 2;
        return query(2 * x, l, m, ql, qr) + query(2 * x + 1, m + 1, r, ql, qr);
    }

    // Public: a[l..r] += v
    void update(int l, int r, ll v) { update(1, 0, n - 1, l, r, v); }

    // Public: sum of a[l..r]
    ll query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

#ifdef LOCAL
int main() {
    vector<ll> a = {1, 2, 3, 4, 5};
    LazySeg st(5);
    st.build(a);
    st.update(1, 3, 10);
    cout << st.query(0, 4) << "\n";  // 45
    cout << st.query(2, 2) << "\n";  // 13
}
#endif
