// GCD / LCM, extended Euclid, modular inverse for ANY modulus (when it exists),
// linear Diophantine equations, and the Chinese Remainder Theorem (also for
// non-coprime moduli). All O(log) per call.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Greatest common divisor (Euclid). Works for non-negative inputs.
ll gcd_ll(ll a, ll b) { while (b) { a %= b; swap(a, b); } return a; }

// Least common multiple. Divide first to avoid overflow: a / gcd * b.
ll lcm_ll(ll a, ll b) { return a / gcd_ll(a, b) * b; }

// Extended Euclid: returns g = gcd(a, b) and sets x, y with a*x + b*y = g. (a, b >= 0)
ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Inverse of a modulo m (any m > 1), or -1 if gcd(a, m) != 1.
ll mod_inv(ll a, ll m) {
    ll x, y;
    ll g = ext_gcd(((a % m) + m) % m, m, x, y);
    if (g != 1) return -1;
    return ((x % m) + m) % m;
}

// Solve a*x + b*y = c for integers x, y (a, b >= 0, not both 0).
// Returns false if there is no solution. Otherwise one solution is (x, y) and
// ALL solutions are (x + k*(b/g), y - k*(a/g)) for any integer k. g = gcd(a, b).
bool diophantine(ll a, ll b, ll c, ll& x, ll& y, ll& g) {
    g = ext_gcd(a, b, x, y);
    if (c % g != 0) return false;
    x *= c / g;
    y *= c / g;
    return true;
}

// Combine x = r1 (mod m1) and x = r2 (mod m2). Moduli need NOT be coprime.
// Returns {r, lcm(m1, m2)} with 0 <= r < lcm, or {-1, -1} if inconsistent.
pair<ll, ll> crt(ll r1, ll m1, ll r2, ll m2) {
    ll x, y;
    ll g = ext_gcd(m1, m2, x, y);
    if ((r2 - r1) % g != 0) return {-1, -1};
    ll m2g = m2 / g;
    // m1*x + m2*y = g  =>  (m1/g)*x = 1 (mod m2/g), so k = ((r2-r1)/g * x) mod (m2/g)
    ll k = (ll)((i128)((r2 - r1) / g) % m2g * (x % m2g) % m2g);
    if (k < 0) k += m2g;
    ll l = m1 / g * m2;
    ll r = (ll)(((i128)r1 + (i128)m1 * k) % l);
    if (r < 0) r += l;
    return {r, l};
}

// Fold crt over many congruences x = r[i] (mod m[i]). {-1, -1} if no solution.
pair<ll, ll> crt_all(const vector<ll>& r, const vector<ll>& m) {
    pair<ll, ll> cur = {0, 1};
    for (size_t i = 0; i < r.size(); i++) {
        cur = crt(cur.first, cur.second, ((r[i] % m[i]) + m[i]) % m[i], m[i]);
        if (cur.first == -1) return cur;
    }
    return cur;
}

#ifdef LOCAL
int main() {
    cout << gcd_ll(84, 36) << " " << lcm_ll(4, 6) << "\n";    // 12 12
    cout << mod_inv(3, 10) << " " << mod_inv(4, 10) << "\n";  // 7 -1
    ll x, y, g;
    cout << diophantine(6, 9, 21, x, y, g) << " " << 6 * x + 9 * y << "\n"; // 1 21
    auto p = crt(2, 3, 3, 5);
    cout << p.first << " " << p.second << "\n";               // 8 15
    p = crt(1, 4, 3, 6);                                      // non-coprime moduli, consistent
    cout << p.first << " " << p.second << "\n";               // 9 12
    p = crt(1, 4, 2, 6);                                      // parity clash
    cout << p.first << " " << p.second << "\n";               // -1 -1
    p = crt_all({2, 3, 2}, {3, 5, 7});
    cout << p.first << " " << p.second << "\n";               // 23 105
}
#endif
