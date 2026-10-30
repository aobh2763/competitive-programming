// Sieves: linear sieve giving smallest prime factor (spf), primes list, Euler's phi
// and Moebius mu for ALL numbers up to n in O(n). Fast factorization of any x <= n
// in O(log x). Plus a segmented sieve for primes in [L, R] with R up to ~1e12.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Sieve {
    int n;
    vector<int> spf, primes, phi, mu;   // phi/mu are filled only if with_phi_mu is true

    // Linear sieve up to n: every composite is visited exactly once, by its
    // smallest prime factor. O(n). Memory ~ 4 ints per number (drop phi/mu if not needed).
    Sieve(int n, bool with_phi_mu = true) : n(n), spf(n + 1, 0) {
        if (with_phi_mu) { phi.assign(n + 1, 0); mu.assign(n + 1, 0); phi[1] = 1; mu[1] = 1; }
        for (int i = 2; i <= n; i++) {
            if (spf[i] == 0) {                         // i is prime
                spf[i] = i; primes.push_back(i);
                if (with_phi_mu) { phi[i] = i - 1; mu[i] = -1; }
            }
            for (int p : primes) {
                if (p > spf[i] || (ll)i * p > n) break;
                spf[i * p] = p;
                if (with_phi_mu) {
                    if (i % p == 0) { phi[i * p] = phi[i] * p; mu[i * p] = 0; }
                    else            { phi[i * p] = phi[i] * (p - 1); mu[i * p] = -mu[i]; }
                }
            }
        }
    }

    // True iff 2 <= x <= n is prime. O(1)
    bool is_prime(int x) const { return x >= 2 && spf[x] == x; }

    // Prime factorization of x (2 <= x <= n) as (prime, exponent) pairs. O(log x)
    vector<pair<int, int>> factorize(int x) const {
        vector<pair<int, int>> f;
        while (x > 1) {
            int p = spf[x], e = 0;
            while (x % p == 0) { x /= p; e++; }
            f.push_back({p, e});
        }
        return f;
    }

    // All divisors of x (unsorted). Number of divisors is at most ~1344 for x <= 1e9.
    vector<int> divisors(int x) const {
        vector<int> d = {1};
        for (auto [p, e] : factorize(x)) {
            int sz = d.size(), pw = 1;
            for (int k = 1; k <= e; k++) {
                pw *= p;
                for (int i = 0; i < sz; i++) d.push_back(d[i] * pw);
            }
        }
        return d;
    }
};

// Plain sieve of Eratosthenes: is_comp-style flags, returns the primes <= n. O(n log log n)
vector<int> simple_sieve(int n) {
    vector<char> comp(n + 1, 0);
    vector<int> pr;
    for (int i = 2; i <= n; i++) {
        if (comp[i]) continue;
        pr.push_back(i);
        for (ll j = (ll)i * i; j <= n; j += i) comp[j] = 1;
    }
    return pr;
}

// Primes in [L, R] (R up to ~1e12, R - L up to ~1e7). Cross off multiples of
// every prime up to sqrt(R) inside the window. O((R-L) log log R + sqrt(R))
vector<ll> segmented_sieve(ll L, ll R) {
    ll lim = (ll)sqrtl((long double)R) + 1;
    vector<int> pr = simple_sieve((int)lim);
    vector<char> comp(R - L + 1, 0);
    for (int p : pr) {
        ll start = max((ll)p * p, (L + p - 1) / p * p);   // never cross off p itself
        for (ll j = start; j <= R; j += p) comp[j - L] = 1;
    }
    vector<ll> res;
    for (ll x = max(L, 2LL); x <= R; x++) if (!comp[x - L]) res.push_back(x);
    return res;
}

#ifdef LOCAL
int main() {
    Sieve s(100);
    cout << s.primes.size() << " " << s.is_prime(97) << "\n";        // 25 1
    cout << s.phi[36] << " " << s.mu[30] << " " << s.mu[12] << "\n"; // 12 -1 0
    for (auto [p, e] : s.factorize(360)) cout << p << "^" << e << " "; // 2^3 3^2 5^1
    cout << "\n" << s.divisors(12).size() << "\n";                   // 6
    auto seg = segmented_sieve(90, 120);
    for (ll p : seg) cout << p << " ";                               // 97 101 103 107 109 113
    cout << "\n";
}
#endif
