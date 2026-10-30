// Iterative Segment Tree (bottom-up), 0-indexed, half-open [l, r)
// Point set, range query with any associative op: O(log n)
// Works for non-commutative ops too (order is preserved).
// Usage:
//   SegTree seg(n, 0LL, [](ll a, ll b){ return a + b; });      // sum
//   SegTree mn(n, (int)2e9, [](int a, int b){ return min(a, b); }); // min
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class T, class F>
struct SegTree {
    int n;
    T id;           // identity element of the op (0 for sum, +inf for min)
    F f;            // the associative op
    vector<T> t;

    // n leaves, all initialised to the identity. O(n)
    SegTree(int n, T id, F f) : n(n), id(id), f(f), t(2 * n, id) {}

    // Fill leaves from a and build all internal nodes. O(n)
    void build(const vector<T>& a) {
        for (int i = 0; i < n; i++) t[n + i] = a[i];
        for (int i = n - 1; i >= 1; i--) t[i] = f(t[2 * i], t[2 * i + 1]);
    }

    // a[i] = v, then fix all ancestors. O(log n)
    void set(int i, T v) {
        for (t[i += n] = v; i > 1; i >>= 1)
            t[i >> 1] = f(t[i & ~1], t[i | 1]);
    }

    // Combine a[l..r-1] in order. Returns id if l >= r. O(log n)
    T query(int l, int r) {
        T a = id, b = id;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) a = f(a, t[l++]);
            if (r & 1) b = f(t[--r], b);
        }
        return f(a, b);
    }
};

#ifdef LOCAL
int main() {
    vector<ll> a = {5, 3, 8, 1, 9, 2, 7};
    SegTree seg((int)a.size(), 0LL, [](ll x, ll y) { return x + y; });
    seg.build(a);
    cout << seg.query(1, 4) << "\n";  // 12
    seg.set(2, 0);
    cout << seg.query(1, 4) << "\n";  // 4
}
#endif
