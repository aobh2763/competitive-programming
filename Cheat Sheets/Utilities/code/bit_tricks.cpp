// Bit manipulation helpers + two classic bit techniques:
//  - submask / k-bit-combination enumeration
//  - SOS DP (sum over subsets) in O(n 2^n)
//  - XOR basis (linear basis over GF(2)): max xor, "can I build x?"
// 0-indexed bits. Use the ll versions (1LL << k) when masks can exceed 31 bits.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// Number of set bits.
inline int popcount(ull x) { return __builtin_popcountll(x); }

// Index of the lowest set bit (x != 0).
inline int lowest_bit_index(ull x) { return __builtin_ctzll(x); }

// Index of the highest set bit = floor(log2(x)) (x != 0).
inline int highest_bit_index(ull x) { return 63 - __builtin_clzll(x); }

// Lowest set bit as a value: 12 (1100) -> 4 (0100).
inline ull lowbit(ull x) { return x & (~x + 1); }

// True if x is a power of two (x > 0).
inline bool is_pow2(ull x) { return x && !(x & (x - 1)); }

// Smallest power of two >= x (x >= 1).
inline ull next_pow2(ull x) { return x <= 1 ? 1 : 1ULL << (64 - __builtin_clzll(x - 1)); }

// Gray code of i: consecutive values differ in exactly one bit.
inline ull gray(ull i) { return i ^ (i >> 1); }

// Call f(sub) for every non-empty submask of mask, in decreasing order. O(2^popcount(mask))
// Iterating all masks and all their submasks costs O(3^n) in total.
template<class F>
void for_each_submask(ull mask, F f) {
    for (ull sub = mask; sub > 0; sub = (sub - 1) & mask) f(sub);
}

// Call f(m) for every n-bit mask with exactly k set bits (Gosper's hack). O(C(n, k))
template<class F>
void for_each_combination(int n, int k, F f) {
    if (k == 0) { f(0ULL); return; }
    ull m = (1ULL << k) - 1, limit = 1ULL << n;
    while (m < limit) {
        f(m);
        ull c = m & -m, r = m + c;
        m = (((r ^ m) >> 2) / c) | r;
    }
}

// SOS DP (sum over subsets): after the call, f[mask] = sum of original f[sub] for all
// submasks sub of mask. f has size 2^bits. O(bits * 2^bits)
void sos_subset_sum(vector<ll>& f, int bits) {
    for (int b = 0; b < bits; b++)
        for (int mask = 0; mask < (1 << bits); mask++)
            if (mask >> b & 1) f[mask] += f[mask ^ (1 << b)];
}

// XOR basis: keeps a set of numbers whose XOR-span equals the span of everything inserted.
struct XorBasis {
    static const int B = 62;
    ull b[B + 1] = {};      // b[i] has highest bit i (or 0 if unused)
    int rank = 0;

    // Insert x. Returns true if it was independent (the span grew). O(B)
    bool insert(ull x) {
        for (int i = B; i >= 0 && x; i--) {
            if (!(x >> i & 1)) continue;
            if (!b[i]) { b[i] = x; rank++; return true; }
            x ^= b[i];
        }
        return false;
    }

    // Can x be written as an XOR of inserted numbers? O(B)
    bool can_make(ull x) const {
        for (int i = B; i >= 0 && x; i--)
            if (x >> i & 1) { if (!b[i]) return false; x ^= b[i]; }
        return true;
    }

    // Largest XOR obtainable from the inserted numbers. O(B)
    ull max_xor() const {
        ull r = 0;
        for (int i = B; i >= 0; i--) if (!(r >> i & 1) && b[i]) r ^= b[i];
        return r;
    }
};

#ifdef LOCAL
int main() {
    cout << popcount(255) << lowest_bit_index(8) << highest_bit_index(1000) << "\n";  // 839
    cout << lowbit(12) << is_pow2(64) << next_pow2(17) << gray(3) << "\n";             // 4 1 32 2
    int cnt = 0; for_each_submask(0b1011, [&](ull) { cnt++; }); cout << cnt << "\n";  // 7
    cnt = 0; for_each_combination(5, 2, [&](ull) { cnt++; }); cout << cnt << "\n";     // 10
    vector<ll> f = {1, 2, 3, 4};                    // bits = 2
    sos_subset_sum(f, 2);
    cout << f[3] << "\n";                                                              // 10
    XorBasis xb; xb.insert(5); xb.insert(3); xb.insert(6);
    cout << xb.rank << " " << xb.max_xor() << " " << xb.can_make(2) << "\n";           // 2 6 1
}
#endif
