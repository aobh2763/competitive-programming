// Number-theoretic functions by trial division (no sieve needed): factorization,
// Euler's phi, number/sum of divisors, divisor list, integer sqrt, floor/ceil division
// for negatives, and the "divisor block" loop for sum of floor(n / i).
// Trial division is O(sqrt n): fine for n up to ~1e12 for a few calls.
// For many queries use sieve.cpp; for n up to 1e18 use primality.cpp.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Prime factorization of n (n >= 1) as (prime, exponent) pairs, ascending. O(sqrt n)
vector<pair<ll, int>> factorize(ll n) {
    vector<pair<ll, int>> f;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p) continue;
        int e = 0;
        while (n % p == 0) { n /= p; e++; }
        f.push_back({p, e});
    }
    if (n > 1) f.push_back({n, 1});
    return f;
}

// Euler's totient: how many 1 <= k <= n are coprime to n.
// phi(n) = n * prod over primes p | n of (1 - 1/p). O(sqrt n)
ll euler_phi(ll n) {
    ll r = n;
    for (auto [p, e] : factorize(n)) r = r / p * (p - 1);
    return r;
}

// Number of divisors d(n) = prod (e_i + 1). O(sqrt n)
ll count_divisors(ll n) {
    ll r = 1;
    for (auto [p, e] : factorize(n)) r *= (e + 1);
    return r;
}

// Sum of divisors sigma(n) = prod (p^(e+1) - 1) / (p - 1). O(sqrt n)
ll sum_divisors(ll n) {
    ll r = 1;
    for (auto [p, e] : factorize(n)) {
        ll term = 1, pw = 1;
        for (int i = 0; i < e; i++) { pw *= p; term += pw; }
        r *= term;
    }
    return r;
}

// All divisors of n in ascending order. O(sqrt n + d log d)
vector<ll> divisors(ll n) {
    vector<ll> d;
    for (ll i = 1; i * i <= n; i++)
        if (n % i == 0) { d.push_back(i); if (i != n / i) d.push_back(n / i); }
    sort(d.begin(), d.end());
    return d;
}

// floor(sqrt(x)) exactly, for any x up to 9e18 (fixes sqrtl rounding errors).
ll isqrt(ll x) {
    ll r = (ll)sqrtl((long double)x);
    while (r * r > x) r--;
    while ((r + 1) * (r + 1) <= x) r++;
    return r;
}

// Floor and ceil division that are correct for NEGATIVE numbers (b != 0).
// C++ '/' truncates toward zero, which is wrong for these.
ll floor_div(ll a, ll b) { return a / b - ((a % b != 0) && ((a < 0) != (b < 0))); }
ll ceil_div(ll a, ll b)  { return a / b + ((a % b != 0) && ((a < 0) == (b < 0))); }

// sum_{i=1}^{n} floor(n / i) in O(sqrt n). The value floor(n/i) takes only
// O(sqrt n) distinct values, constant on blocks [l, r]. Use the same loop shape
// for any sum of f(floor(n / i)) * g(i).
ll sum_floor_div(ll n) {
    ll s = 0;
    for (ll l = 1, r; l <= n; l = r + 1) {
        ll q = n / l;
        r = n / q;                 // largest i with floor(n / i) == q
        s += q * (r - l + 1);
    }
    return s;
}

#ifdef LOCAL
int main() {
    for (auto [p, e] : factorize(360)) cout << p << "^" << e << " ";  // 2^3 3^2 5^1
    cout << "\n";
    cout << euler_phi(36) << " " << count_divisors(36) << " " << sum_divisors(12) << "\n"; // 12 9 28
    cout << isqrt(1'000'000'000'000'000'000LL) << "\n";               // 1000000000
    cout << floor_div(-7, 2) << " " << ceil_div(-7, 2) << " " << ceil_div(7, 2) << "\n";   // -4 -3 4
    cout << sum_floor_div(10) << "\n";                                // 27
}
#endif
