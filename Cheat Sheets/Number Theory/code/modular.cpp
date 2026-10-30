// Modular arithmetic toolkit: fast power, 128-bit mulmod, modular inverse (prime mod),
// all inverses 1..n in O(n), and a Mint<M> struct that does the % for you.
// Default modulus 1e9+7. Many problems use 998244353 instead (NTT-friendly).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u64 = unsigned long long;
using u128 = unsigned __int128;

const ll MOD = 1'000'000'007;

// (a * b) mod m without overflow, valid for any m < 2^63. Uses 128-bit math.
u64 mulmod(u64 a, u64 b, u64 m) { return (u128)a * b % m; }

// a^e mod m by repeated squaring. O(log e).
// Plain ll multiplication: safe only when m < ~3e9 (so that (m-1)^2 fits in ll).
// Negative a is handled. e must be >= 0.
ll binpow(ll a, ll e, ll m = MOD) {
    ll r = 1 % m;
    a %= m; if (a < 0) a += m;
    while (e > 0) {
        if (e & 1) r = r * a % m;
        a = a * a % m;
        e >>= 1;
    }
    return r;
}

// Same as binpow but safe for moduli up to ~9e18 (uses mulmod). Slower.
ll binpow64(ll a, ll e, ll m) {
    u64 r = 1 % m, b = ((a % m) + m) % m;
    while (e > 0) {
        if (e & 1) r = mulmod(r, b, m);
        b = mulmod(b, b, m);
        e >>= 1;
    }
    return r;
}

// Modular inverse of a when m is PRIME (Fermat: a^(m-2)). O(log m).
// For a non-prime modulus use mod_inv in gcd_crt.cpp.
ll inv_prime(ll a, ll m = MOD) { return binpow(a, m - 2, m); }

// inv[i] = i^{-1} mod m for all i in 1..n (m prime, n < m). O(n) total.
// Uses  inv[i] = -(m / i) * inv[m % i]  (mod m).
vector<ll> inverses_upto(int n, ll m = MOD) {
    vector<ll> inv(n + 1, 0);
    if (n >= 1) inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = (m - (m / i) * inv[m % i] % m) % m;
    return inv;
}

// Integer that is automatically reduced mod M (M prime if you use / or inv()).
// Usage:  using mint = Mint<998244353>;  mint x = 5; x = x * x + 3; cout << x;
template<int M>
struct Mint {
    int v;

    // Construct from any long long (negatives are normalised into [0, M)).
    Mint(ll x = 0) { v = (int)(x % M); if (v < 0) v += M; }

    Mint& operator+=(const Mint& o) { v += o.v; if (v >= M) v -= M; return *this; }
    Mint& operator-=(const Mint& o) { v -= o.v; if (v < 0) v += M; return *this; }
    Mint& operator*=(const Mint& o) { v = (int)((ll)v * o.v % M); return *this; }

    // this^e, e >= 0. O(log e).
    Mint pow(ll e) const {
        Mint r(1), b = *this;
        for (; e > 0; e >>= 1, b *= b) if (e & 1) r *= b;
        return r;
    }

    // Multiplicative inverse (M must be prime and v != 0).
    Mint inv() const { return pow(M - 2); }

    Mint& operator/=(const Mint& o) { return *this *= o.inv(); }
    friend Mint operator+(Mint a, const Mint& b) { return a += b; }
    friend Mint operator-(Mint a, const Mint& b) { return a -= b; }
    friend Mint operator*(Mint a, const Mint& b) { return a *= b; }
    friend Mint operator/(Mint a, const Mint& b) { return a /= b; }
    friend bool operator==(const Mint& a, const Mint& b) { return a.v == b.v; }
    friend bool operator!=(const Mint& a, const Mint& b) { return a.v != b.v; }
    friend ostream& operator<<(ostream& os, const Mint& a) { return os << a.v; }
    friend istream& operator>>(istream& is, Mint& a) { ll x; is >> x; a = Mint(x); return is; }
};

#ifdef LOCAL
int main() {
    cout << binpow(2, 10) << "\n";                       // 1024
    cout << binpow64(2, 62, 4'611'686'018'427'387'847LL) << "\n";
    cout << inv_prime(3) * 3 % MOD << "\n";              // 1
    auto inv = inverses_upto(10);
    cout << inv[7] * 7 % MOD << "\n";                    // 1
    using mint = Mint<998244353>;
    mint a = 5, b = 7;
    cout << a / b * b << " " << (a - b) << "\n";         // 5 998244351
}
#endif
