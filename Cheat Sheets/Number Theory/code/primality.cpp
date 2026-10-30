// Primality and factorization for numbers up to ~1e18:
//  - is_prime: deterministic Miller-Rabin for all 64-bit integers
//  - factorize: Pollard's rho (Brent's variant, batched gcd) + Miller-Rabin
// is_prime ~ O(log^2 n) per call; rho finds a factor in ~O(n^(1/4)) expected.
#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;
using u128 = unsigned __int128;

// (a * b) mod m for 64-bit values, via 128-bit product.
u64 mulmod(u64 a, u64 b, u64 m) { return (u128)a * b % m; }

// a^e mod m, safe for any 64-bit modulus. O(log e)
u64 powmod(u64 a, u64 e, u64 m) {
    u64 r = 1 % m;
    a %= m;
    for (; e; e >>= 1, a = mulmod(a, a, m)) if (e & 1) r = mulmod(r, a, m);
    return r;
}

// Deterministic Miller-Rabin: the first 12 primes as witnesses are enough for
// every n < 3.3e24, so they are exact for all 64-bit integers.
// Write n - 1 = d * 2^s; n is a probable prime to base a if a^d = 1 or
// a^(d*2^r) = -1 for some 0 <= r < s.
bool is_prime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL})
        if (n % p == 0) return n == p;
    u64 d = n - 1;
    int s = __builtin_ctzll(d);
    d >>= s;
    for (u64 a : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        u64 x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mulmod(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

// Find a nontrivial factor of composite n with Pollard's rho + Brent cycle detection.
// Instead of one gcd per step, multiply 128 differences together and take one gcd.
// May return n itself on an unlucky random polynomial, so callers retry (see factor()).
u64 rho(u64 n) {
    if (n % 2 == 0) return 2;
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    u64 c = rng() % (n - 1) + 1, y = rng() % n, x = y, ys = y, g = 1, q = 1;
    const u64 m = 128;
    auto f = [&](u64 v) { return (mulmod(v, v, n) + c) % n; };
    for (u64 r = 1; g == 1; r <<= 1) {
        x = y;
        for (u64 i = 0; i < r; i++) y = f(y);
        for (u64 k = 0; k < r && g == 1; k += m) {
            ys = y;
            for (u64 i = 0; i < m && i < r - k; i++) {
                y = f(y);
                q = mulmod(q, x > y ? x - y : y - x, n);
            }
            g = std::gcd(q, n);
        }
    }
    if (g == n) {       // batch overshot: redo the last block one step at a time
        do {
            ys = f(ys);
            g = std::gcd(x > ys ? x - ys : ys - x, n);
        } while (g == 1);
    }
    return g;
}

// Recursive helper: append all prime factors of n (with repetition) to out.
void factor_rec(u64 n, vector<u64>& out) {
    if (n == 1) return;
    if (is_prime(n)) { out.push_back(n); return; }
    u64 d = rho(n);
    while (d == n) d = rho(n);          // retry with a fresh random polynomial
    factor_rec(d, out);
    factor_rec(n / d, out);
}

// Prime factorization of n (1 <= n <= ~1e18) as sorted (prime, exponent) pairs.
vector<pair<u64, int>> factorize(u64 n) {
    vector<u64> ps;
    // Strip small primes first: cheap, and keeps rho away from tiny awkward cases.
    for (u64 p = 2; p < 100 && p * p <= n; p++)
        while (n % p == 0) { ps.push_back(p); n /= p; }
    factor_rec(n, ps);
    sort(ps.begin(), ps.end());
    vector<pair<u64, int>> res;
    for (u64 p : ps) {
        if (!res.empty() && res.back().first == p) res.back().second++;
        else res.push_back({p, 1});
    }
    return res;
}

#ifdef LOCAL
int main() {
    cout << is_prime(1'000'000'007) << is_prime(1'000'000'007ULL * 998244353ULL)
         << is_prime(999'999'999'999'999'989ULL) << "\n";               // 101
    for (auto [p, e] : factorize(600851475143ULL)) cout << p << "^" << e << " ";  // 71^1 839^1 1471^1 6857^1
    cout << "\n";
    for (auto [p, e] : factorize(1'000'000'007ULL * 998244353ULL)) cout << p << "^" << e << " ";
    cout << "\n";
}
#endif
