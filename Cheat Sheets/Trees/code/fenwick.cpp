// Fenwick Tree (BIT), 1-indexed
// Point add, prefix/range sum: O(log n). Memory: O(n)
// lower_bound(k): smallest i with prefix sum >= k (values must be >= 0)
// Tip: for range-add + point-query, add(l, v), add(r+1, -v), query with sum(i)
#include <bits/stdc++.h>
using namespace std;

template<class T>
struct Fenwick {
    int n;
    vector<T> t;

    // Create a BIT of size n, all zeros. Indices are 1..n.
    Fenwick(int n = 0) : n(n), t(n + 1, 0) {}

    // a[i] += v. O(log n)
    void add(int i, T v) {
        for (; i <= n; i += i & -i) t[i] += v;
    }

    // Sum of a[1..i]. O(log n)
    T sum(int i) {
        T r = 0;
        for (; i > 0; i -= i & -i) r += t[i];
        return r;
    }

    // Sum of a[l..r], inclusive. O(log n)
    T sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    // Smallest index i such that sum(1..i) >= k, via binary descent. O(log n)
    // Requires non-negative values. Returns n + 1 if the total sum is < k.
    int lower_bound(T k) {
        int pos = 0;
        for (int pw = 1 << __lg(n); pw; pw >>= 1)
            if (pos + pw <= n && t[pos + pw] < k) {
                pos += pw;
                k -= t[pos];
            }
        return pos + 1;
    }
};

#ifdef LOCAL
int main() {
    Fenwick<long long> bit(8);
    for (int i = 1; i <= 8; i++) bit.add(i, i);
    cout << bit.sum(3, 5) << "\n";        // 12
    cout << bit.lower_bound(10) << "\n";  // 4
}
#endif
