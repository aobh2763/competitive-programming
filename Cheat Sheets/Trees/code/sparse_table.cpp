// Sparse Table: static range min (or any IDEMPOTENT op: min, max, gcd, and, or)
// Build: O(n log n). Query: O(1). No updates (use a segment tree for those).
// NOT valid for sum (ranges overlap in the query). Use a prefix sum for that.
// To get max/gcd: change the body of op().
#include <bits/stdc++.h>
using namespace std;

template<class T>
struct SparseTable {
    vector<vector<T>> t;    // t[j][i] = op over a[i .. i + 2^j - 1]

    // The idempotent operation. Swap min for max / __gcd / etc. as needed.
    static T op(const T& a, const T& b) { return min(a, b); }

    // Build all levels from a. O(n log n)
    SparseTable(const vector<T>& a) {
        int n = a.size(), LOG = __lg(max(n, 1)) + 1;
        t.assign(LOG, vector<T>(n));
        t[0] = a;
        for (int j = 1; j < LOG; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                t[j][i] = op(t[j - 1][i], t[j - 1][i + (1 << (j - 1))]);
    }

    // op over a[l..r], inclusive (l <= r). Two overlapping power-of-two blocks. O(1)
    T query(int l, int r) {
        int j = __lg(r - l + 1);
        return op(t[j][l], t[j][r - (1 << j) + 1]);
    }
};

#ifdef LOCAL
int main() {
    vector<int> a = {5, 3, 8, 1, 9, 2, 7};
    SparseTable<int> st(a);
    cout << st.query(0, 2) << "\n";  // 3
    cout << st.query(2, 5) << "\n";  // 1
    cout << st.query(4, 4) << "\n";  // 9
}
#endif
