// Binary search templates: first/last x where a monotone predicate holds,
// binary search on real numbers, ternary search for unimodal functions.
// "Binary search on the answer": define pred(x) = "is x feasible?" and find the boundary.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Smallest x in [lo, hi] with pred(x) true, where pred looks like F F F T T T (monotone).
// Returns hi + 1 if pred is false everywhere. O(log(hi - lo)) calls to pred.
template<class F>
ll first_true(ll lo, ll hi, F pred) {
    ll l = lo, r = hi + 1;              // search the half-open range [l, r)
    while (l < r) {
        ll m = l + (r - l) / 2;
        if (pred(m)) r = m;
        else l = m + 1;
    }
    return l;
}

// Largest x in [lo, hi] with pred(x) true, where pred looks like T T T F F F.
// Returns lo - 1 if pred is false everywhere.
template<class F>
ll last_true(ll lo, ll hi, F pred) {
    return first_true(lo, hi, [&](ll x) { return !pred(x); }) - 1;
}

// Binary search on reals: shrink [lo, hi] for `iters` rounds and return the boundary of a
// predicate shaped F..FT..T. 100 iterations is enough for doubles; use iterations, not
// an epsilon loop (`while (hi - lo > eps)` can loop forever at large magnitudes).
template<class F>
double bisect_real(double lo, double hi, F pred, int iters = 100) {
    for (int i = 0; i < iters; i++) {
        double m = (lo + hi) / 2;
        if (pred(m)) hi = m; else lo = m;
    }
    return (lo + hi) / 2;
}

// Minimum of a unimodal (strictly decreasing then strictly increasing) function on the
// integers [lo, hi]. For a maximum, search for the minimum of -f. O(log(hi - lo)) evaluations.
template<class F>
ll ternary_int(ll lo, ll hi, F f) {
    while (hi - lo > 2) {
        ll m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2;
        else lo = m1;
    }
    ll best = lo;
    for (ll x = lo + 1; x <= hi; x++) if (f(x) < f(best)) best = x;
    return best;
}

// Minimum of a unimodal function on reals [lo, hi]. Returns the argmin.
template<class F>
double ternary_real(double lo, double hi, F f, int iters = 100) {
    for (int i = 0; i < iters; i++) {
        double m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2; else lo = m1;
    }
    return (lo + hi) / 2;
}

#ifdef LOCAL
int main() {
    vector<int> a = {1, 3, 3, 5, 8, 13};
    // first index with a[i] >= 4 (same as lower_bound)
    cout << first_true(0, 5, [&](ll i) { return a[i] >= 4; }) << "\n";   // 3
    cout << last_true(0, 5, [&](ll i) { return a[i] <= 3; }) << "\n";    // 2
    // binary search on the answer: smallest x with x*x >= 200
    cout << first_true(0, 1000, [](ll x) { return x * x >= 200; }) << "\n";  // 15
    cout << fixed << setprecision(6) << bisect_real(0, 10, [](double x) { return x * x >= 2; }) << "\n"; // 1.414214
    cout << ternary_int(-100, 100, [](ll x) { return (x - 7) * (x - 7); }) << "\n";  // 7
    cout << fixed << setprecision(4) << ternary_real(-10, 10, [](double x) { return (x - 2.5) * (x - 2.5); }) << "\n"; // 2.5000
}
#endif
