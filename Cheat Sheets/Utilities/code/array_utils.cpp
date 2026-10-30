// Array utilities that show up constantly:
//  coordinate compression, 1D/2D prefix sums, 2D difference array, nearest greater/smaller
//  (monotonic stack), sliding window max, LIS, inversion count, Kadane.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Coordinate compression: replace every value by its rank among the distinct values
// (0-based). Returns the sorted distinct values so you can map back (vals[rank]). O(n log n)
template<class T>
vector<T> compress(vector<T>& a) {
    vector<T> vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (auto& x : a) x = lower_bound(vals.begin(), vals.end(), x) - vals.begin();
    return vals;
}

// Prefix sums: P[i] = a[0] + ... + a[i-1], so sum of a[l..r] = P[r+1] - P[l]. O(n)
vector<ll> prefix_sums(const vector<ll>& a) {
    vector<ll> P(a.size() + 1, 0);
    for (size_t i = 0; i < a.size(); i++) P[i + 1] = P[i] + a[i];
    return P;
}

// 2D prefix sums. query(r1, c1, r2, c2) = sum of the rectangle, all bounds inclusive, 0-indexed.
struct Prefix2D {
    vector<vector<ll>> P;

    // Build from an R x C grid. O(R * C)
    Prefix2D(const vector<vector<ll>>& g) {
        int R = g.size(), C = g[0].size();
        P.assign(R + 1, vector<ll>(C + 1, 0));
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                P[i + 1][j + 1] = g[i][j] + P[i][j + 1] + P[i + 1][j] - P[i][j];
    }

    // Sum of g[r1..r2][c1..c2] by inclusion-exclusion. O(1)
    ll query(int r1, int c1, int r2, int c2) const {
        return P[r2 + 1][c2 + 1] - P[r1][c2 + 1] - P[r2 + 1][c1] + P[r1][c1];
    }
};

// 2D difference array: add v to a whole rectangle in O(1), then build() once at the end.
struct Diff2D {
    int R, C;
    vector<vector<ll>> d;

    // R x C grid of zeros.
    Diff2D(int R, int C) : R(R), C(C), d(R + 2, vector<ll>(C + 2, 0)) {}

    // g[r1..r2][c1..c2] += v (inclusive, 0-indexed). O(1)
    void add(int r1, int c1, int r2, int c2, ll v) {
        d[r1][c1] += v; d[r1][c2 + 1] -= v;
        d[r2 + 1][c1] -= v; d[r2 + 1][c2 + 1] += v;
    }

    // Turn the differences into the final grid (2D prefix sum). O(R * C)
    vector<vector<ll>> build() const {
        vector<vector<ll>> g(R, vector<ll>(C, 0));
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++) {
                g[i][j] = d[i][j] + (i ? g[i - 1][j] : 0) + (j ? g[i][j - 1] : 0)
                          - (i && j ? g[i - 1][j - 1] : 0);
            }
        return g;
    }
};

// For each i, index of the nearest element to the right with a[j] > a[i], or n if none.
// Monotonic stack, O(n). Use cmp = less/greater variants below for smaller.
template<class T, class Cmp>
vector<int> next_by(const vector<T>& a, Cmp better) {
    int n = a.size();
    vector<int> res(n, n);
    vector<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && better(a[i], a[st.back()])) { res[st.back()] = i; st.pop_back(); }
        st.push_back(i);
    }
    return res;
}

// Next strictly greater element index to the right (n if none).
template<class T> vector<int> next_greater(const vector<T>& a) { return next_by(a, greater<T>()); }

// Next strictly smaller element index to the right (n if none).
template<class T> vector<int> next_smaller(const vector<T>& a) { return next_by(a, less<T>()); }

// Previous strictly greater element index to the left (-1 if none).
template<class T> vector<int> prev_greater(const vector<T>& a) {
    int n = a.size();
    vector<int> res(n, -1), st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[i] > a[st.back()]) { res[st.back()] = i; st.pop_back(); }
        st.push_back(i);
    }
    return res;
}

// Previous strictly smaller element index to the left (-1 if none).
template<class T> vector<int> prev_smaller(const vector<T>& a) {
    int n = a.size();
    vector<int> res(n, -1), st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[i] < a[st.back()]) { res[st.back()] = i; st.pop_back(); }
        st.push_back(i);
    }
    return res;
}

// Max of every window of k consecutive elements (n - k + 1 values). Monotone deque, O(n)
// For the minimum, call it on negated values or swap the comparison.
template<class T>
vector<T> sliding_window_max(const vector<T>& a, int k) {
    deque<int> dq;
    vector<T> res;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}

// Length of the longest strictly increasing subsequence (non-decreasing if strict = false).
// Patience sorting with binary search. O(n log n)
template<class T>
int lis_length(const vector<T>& a, bool strict = true) {
    vector<T> tails;
    for (const T& x : a) {
        auto it = strict ? lower_bound(tails.begin(), tails.end(), x)
                         : upper_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x); else *it = x;
    }
    return tails.size();
}

// Number of pairs i < j with a[i] > a[j], by merge sort. O(n log n). Sorts a copy.
ll count_inversions(vector<ll> a) {
    vector<ll> tmp(a.size());
    function<ll(int, int)> rec = [&](int l, int r) -> ll {      // sorts a[l, r)
        if (r - l <= 1) return 0;
        int m = (l + r) / 2;
        ll inv = rec(l, m) + rec(m, r);
        int i = l, j = m, k = l;
        while (i < m || j < r) {
            if (j == r || (i < m && a[i] <= a[j])) tmp[k++] = a[i++];
            else { tmp[k++] = a[j++]; inv += m - i; }           // a[i..m) are all > a[j]
        }
        copy(tmp.begin() + l, tmp.begin() + r, a.begin() + l);
        return inv;
    };
    return rec(0, a.size());
}

// Maximum sum of a non-empty contiguous subarray. O(n)
ll kadane(const vector<ll>& a) {
    ll best = a[0], cur = a[0];
    for (size_t i = 1; i < a.size(); i++) {
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
    }
    return best;
}

#ifdef LOCAL
int main() {
    vector<int> a = {50, 10, 50, 30};
    auto vals = compress(a);
    for (int x : a) cout << x << " ";                          // 2 0 2 1
    cout << "| " << vals.size() << "\n";                       // 3
    auto P = prefix_sums({1, 2, 3, 4});
    cout << P[3] - P[1] << "\n";                               // 5
    Prefix2D p2({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << p2.query(1, 1, 2, 2) << "\n";                      // 28
    Diff2D d(3, 3); d.add(0, 0, 1, 1, 5);
    cout << d.build()[1][1] << d.build()[2][2] << "\n";        // 50
    vector<int> b = {2, 1, 5, 3, 4};
    cout << next_greater(b)[1] << prev_smaller(b)[3] << "\n";  // 22
    for (int x : sliding_window_max(vector<int>{1, 3, -1, -3, 5, 3, 6, 7}, 3)) cout << x << " ";  // 3 3 5 5 6 7
    cout << "\n" << lis_length(vector<int>{10, 9, 2, 5, 3, 7, 101, 18}) << "\n";  // 4
    cout << count_inversions({3, 1, 2}) << " " << kadane({-2, 1, -3, 4, -1, 2, 1, -5, 4}) << "\n";  // 2 6
}
#endif
