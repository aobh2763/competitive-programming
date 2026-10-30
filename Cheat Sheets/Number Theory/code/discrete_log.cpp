// Primitive roots and discrete logarithm.
//  - primitive_root(p): smallest generator of (Z/pZ)* for prime p
//  - discrete_log(a, b, m): smallest x >= 0 with a^x = b (mod m), or -1.
//    Baby-step giant-step, extended to handle gcd(a, m) > 1. O(sqrt(m)).
// Intermediate products use plain long long, so keep m below ~3e9.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// a^e mod m (m < ~3e9).
ll binpow(ll a, ll e, ll m) {
    ll r = 1 % m; a %= m;
    for (; e > 0; e >>= 1, a = a * a % m) if (e & 1) r = r * a % m;
    return r;
}

// Smallest primitive root modulo prime p. g is one iff g^((p-1)/q) != 1 for every
// prime factor q of p - 1. Primitive roots are small (usually < 100). O(sqrt p + log^2 p)
ll primitive_root(ll p) {
    if (p == 2) return 1;
    vector<ll> qs;
    ll n = p - 1;
    for (ll q = 2; q * q <= n; q++) {
        if (n % q) continue;
        qs.push_back(q);
        while (n % q == 0) n /= q;
    }
    if (n > 1) qs.push_back(n);
    for (ll g = 2; g < p; g++) {
        bool ok = true;
        for (ll q : qs) if (binpow(g, (p - 1) / q, p) == 1) { ok = false; break; }
        if (ok) return g;
    }
    return -1;
}

// Smallest x >= 0 with a^x = b (mod m), or -1 if none exists.
// Step 1: while gcd(a, m) = g > 1, divide it out (b must be divisible by g too),
//         tracking a shift `add` and a running factor k.
// Step 2: now gcd(a, m) = 1, so solve k * a^x = b by baby-step giant-step:
//         write x = n*p - q, store b*a^q for q in [0, n], look up k*a^(n*p).
ll discrete_log(ll a, ll b, ll m) {
    a %= m; b %= m;
    if (m == 1) return 0;
    ll k = 1 % m, add = 0, g;
    while ((g = std::gcd(a, m)) > 1) {
        if (b == k) return add;
        if (b % g) return -1;
        b /= g; m /= g; add++;
        k = k * (a / g) % m;
    }
    if (b == k) return add;
    ll n = (ll)sqrtl((long double)m) + 1;
    unordered_map<ll, ll> vals;
    ll cur = b;
    for (ll q = 0; q <= n; q++) {
        vals[cur] = q;                  // later (larger) q overwrites: gives the smallest x
        cur = cur * a % m;
    }
    ll an = binpow(a, n, m);
    cur = k;
    for (ll p = 1; p <= n; p++) {
        cur = cur * an % m;
        auto it = vals.find(cur);
        if (it != vals.end()) return n * p - it->second + add;
    }
    return -1;
}

#ifdef LOCAL
int main() {
    cout << primitive_root(998244353) << " " << primitive_root(7) << "\n";  // 3 3
    cout << discrete_log(2, 8, 13) << "\n";                  // 3
    cout << discrete_log(3, 1, 7) << "\n";                   // 0
    cout << discrete_log(2, 3, 8) << "\n";                   // -1
    cout << discrete_log(4, 8, 12) << "\n";                  // -1 (4^x mod 12 is 4 or 1... never 8)
    cout << discrete_log(6, 0, 12) << "\n";                  // 2 (6^2 = 36 = 0 mod 12)
}
#endif
