// Combinatorics mod a prime: factorial tables, nCr, nPr, Catalan, stars & bars,
// multinomial, Lucas' theorem (for n, r larger than the modulus), Pascal's triangle.
// Precompute O(N), each nCr query O(1).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1'000'000'007;

ll binpow(ll a, ll e, ll m) {
    ll r = 1 % m; a %= m;
    for (; e > 0; e >>= 1, a = a * a % m) if (e & 1) r = r * a % m;
    return r;
}

struct Comb {
    int N;
    ll mod;
    vector<ll> f, invf;     // f[i] = i!,  invf[i] = (i!)^{-1}

    // Tables for 0..N. mod must be PRIME and > N.  O(N + log mod)
    // Inverse factorials are built backwards from one Fermat inverse.
    Comb(int N, ll mod = MOD) : N(N), mod(mod), f(N + 1), invf(N + 1) {
        f[0] = 1;
        for (int i = 1; i <= N; i++) f[i] = f[i - 1] * i % mod;
        invf[N] = binpow(f[N], mod - 2, mod);
        for (int i = N; i >= 1; i--) invf[i - 1] = invf[i] * i % mod;
    }

    // C(n, r) mod p. Returns 0 if r < 0 or r > n. Requires n <= N. O(1)
    ll nCr(int n, int r) const {
        if (r < 0 || r > n) return 0;
        return f[n] * invf[r] % mod * invf[n - r] % mod;
    }

    // P(n, r) = n! / (n-r)!  (ordered selections). O(1)
    ll nPr(int n, int r) const {
        if (r < 0 || r > n) return 0;
        return f[n] * invf[n - r] % mod;
    }

    // Inverse of i (1 <= i <= N) in O(1): (i-1)! / i!
    ll inv(int i) const { return invf[i] * f[i - 1] % mod; }

    // n-th Catalan number = C(2n, n) - C(2n, n+1). Needs 2n <= N.
    ll catalan(int n) const { return (nCr(2 * n, n) - nCr(2 * n, n + 1) + mod) % mod; }

    // Number of non-negative integer solutions of x1 + ... + xk = n. Needs n + k - 1 <= N.
    ll stars_bars(int n, int k) const { return nCr(n + k - 1, k - 1); }

    // Multinomial (k1 + ... + km)! / (k1! ... km!). Sum must be <= N.
    ll multinomial(const vector<int>& ks) const {
        int s = 0; ll r = 1;
        for (int k : ks) { s += k; r = r * invf[k] % mod; }
        return r * f[s] % mod;
    }
};

// Lucas' theorem: C(n, r) mod p for HUGE n, r (up to 1e18) when p is a small prime.
// c must be built with mod = p and N >= p - 1. O(log_p(n)) per query.
ll lucas(ll n, ll r, const Comb& c) {
    ll res = 1;
    while (n > 0 || r > 0) {
        ll ni = n % c.mod, ri = r % c.mod;
        if (ri > ni) return 0;
        res = res * c.nCr((int)ni, (int)ri) % c.mod;
        n /= c.mod; r /= c.mod;
    }
    return res;
}

// Pascal's triangle C[i][j] mod m for 0 <= j <= i <= n. Works for ANY modulus m
// (even composite). O(n^2) time and memory, so n up to ~5000.
vector<vector<int>> pascal(int n, int m) {
    vector<vector<int>> C(n + 1);
    for (int i = 0; i <= n; i++) {
        C[i].assign(i + 1, 1 % m);
        for (int j = 1; j < i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % m;
    }
    return C;
}

#ifdef LOCAL
int main() {
    Comb c(1000);
    cout << c.nCr(10, 3) << " " << c.nPr(5, 2) << "\n";       // 120 20
    cout << c.catalan(5) << " " << c.stars_bars(5, 3) << "\n"; // 42 21
    cout << c.multinomial({2, 1, 1}) << "\n";                  // 12
    cout << c.inv(7) * 7 % MOD << "\n";                        // 1
    Comb s(6, 7);                                              // p = 7
    cout << lucas(100, 7, s) << "\n";                          // C(100,7) mod 7 = 14 mod 7 = 0
    auto P = pascal(10, 6);
    cout << P[10][5] << "\n";                                  // 252 mod 6 = 0
}
#endif
