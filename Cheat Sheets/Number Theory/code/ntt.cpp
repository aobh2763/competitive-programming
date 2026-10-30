// Number Theoretic Transform: polynomial multiplication mod 998244353 in O(n log n).
// 998244353 = 119 * 2^23 + 1 with primitive root 3, so sizes up to 2^23 work.
// For a different modulus you need another NTT-friendly prime (or use FFT with doubles).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int NTT_MOD = 998244353;
const int NTT_G = 3;

// a^e mod NTT_MOD.
ll pw(ll a, ll e) {
    ll r = 1; a %= NTT_MOD;
    for (; e > 0; e >>= 1, a = a * a % NTT_MOD) if (e & 1) r = r * a % NTT_MOD;
    return r;
}

// In-place iterative NTT of a (size must be a power of two). invert = true gives the
// inverse transform. Cooley-Tukey butterflies after a bit-reversal permutation. O(n log n)
void ntt(vector<int>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll w = pw(NTT_G, (NTT_MOD - 1) / len);
        if (invert) w = pw(w, NTT_MOD - 2);
        for (int i = 0; i < n; i += len) {
            ll wn = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i + j];
                int v = (int)(a[i + j + len / 2] * wn % NTT_MOD);
                a[i + j] = u + v < NTT_MOD ? u + v : u + v - NTT_MOD;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + NTT_MOD;
                wn = wn * w % NTT_MOD;
            }
        }
    }
    if (invert) {
        ll ninv = pw(n, NTT_MOD - 2);
        for (int& x : a) x = (int)(x * ninv % NTT_MOD);
    }
}

// Product of two polynomials (coefficients mod 998244353, a[i] = coeff of x^i).
// Result has size a.size() + b.size() - 1. O((n + m) log(n + m))
vector<int> multiply(vector<int> a, vector<int> b) {
    if (a.empty() || b.empty()) return {};
    int need = a.size() + b.size() - 1, n = 1;
    while (n < need) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = (int)((ll)a[i] * b[i] % NTT_MOD);
    ntt(a, true);
    a.resize(need);
    return a;
}

#ifdef LOCAL
int main() {
    // (1 + 2x + 3x^2) * (4 + 5x) = 4 + 13x + 22x^2 + 15x^3
    auto c = multiply({1, 2, 3}, {4, 5});
    for (int x : c) cout << x << " ";                           // 4 13 22 15
    cout << "\n";
}
#endif
