// Polynomial rolling hash modulo 2^61 - 1 with a RANDOM base.
// After O(n) preprocessing, the hash of any substring is available in O(1), so you can
// compare two substrings, find the longest common prefix of two suffixes (binary search),
// count distinct substrings, etc. A collision is possible but has probability ~ n / 2^61
// per comparison, and the random base defeats anti-hash tests.
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

const ull HMOD = (1ULL << 61) - 1;

// (a * b) mod (2^61 - 1) using a 128-bit product and the identity 2^61 = 1 (mod p).
ull mulmod61(ull a, ull b) {
    __uint128_t t = (__uint128_t)a * b;
    ull r = (ull)(t & HMOD) + (ull)(t >> 61);
    if (r >= HMOD) r -= HMOD;
    if (r >= HMOD) r -= HMOD;
    return r;
}

struct StringHash {
    vector<ull> h, pw;      // h[i] = hash of the first i characters, pw[i] = base^i
    ull base;

    // Precompute prefix hashes of s. The base is random unless you pass one. O(n)
    StringHash(const string& s, ull base_ = 0) {
        static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        base = base_ ? base_ : rng() % (HMOD - 1000) + 500;
        int n = s.size();
        h.assign(n + 1, 0); pw.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            h[i + 1] = mulmod61(h[i], base) + (ull)(unsigned char)s[i] + 1;   // +1 so 'char 0' still counts
            if (h[i + 1] >= HMOD) h[i + 1] -= HMOD;
            pw[i + 1] = mulmod61(pw[i], base);
        }
    }

    // Hash of the substring s[l, r) (half-open). O(1)
    ull get(int l, int r) const {
        ull x = h[r] + HMOD - mulmod61(h[l], pw[r - l]);
        return x >= HMOD ? x - HMOD : x;
    }

    // Are s[l1, r1) and s[l2, r2) equal? (probabilistic) O(1)
    bool equal(int l1, int r1, int l2, int r2) const {
        return r1 - l1 == r2 - l2 && get(l1, r1) == get(l2, r2);
    }

    // Length of the longest common prefix of the suffixes starting at i and j.
    // Binary search on the length, comparing hashes. O(log n)
    int lcp(int i, int j) const {
        int n = h.size() - 1;
        int lo = 0, hi = n - max(i, j);
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (get(i, i + mid) == get(j, j + mid)) lo = mid; else hi = mid - 1;
        }
        return lo;
    }
};

// Hash of a whole string with the same base and scheme (to compare against substrings of another
// StringHash built with the SAME base). Pass the base of the text's StringHash.
ull hash_of(const string& p, ull base) {
    ull x = 0;
    for (unsigned char c : p) { x = mulmod61(x, base) + (ull)c + 1; if (x >= HMOD) x -= HMOD; }
    return x;
}

// All start positions where pattern p occurs in text t, by comparing hashes of every window.
// O(n + m). (KMP / Z give the same result deterministically; hashing is handy for 2D or
// "equal up to something" variants.)
vector<int> hash_search(const string& t, const string& p) {
    StringHash H(t);
    int n = t.size(), m = p.size();
    vector<int> res;
    if (m > n) return res;
    ull hp = hash_of(p, H.base);
    for (int i = 0; i + m <= n; i++) if (H.get(i, i + m) == hp) res.push_back(i);
    return res;
}

// Number of DISTINCT substrings of length len in s (collect hashes, sort, unique). O(n log n)
int count_distinct_of_length(const string& s, int len) {
    StringHash H(s);
    vector<ull> v;
    for (int i = 0; i + len <= (int)s.size(); i++) v.push_back(H.get(i, i + len));
    sort(v.begin(), v.end());
    return unique(v.begin(), v.end()) - v.begin();
}

#ifdef LOCAL
int main() {
    string s = "abracadabra";
    StringHash H(s);
    cout << H.equal(0, 4, 7, 11) << "\n";                    // 1 ("abra" == "abra")
    cout << H.lcp(0, 7) << " " << H.lcp(1, 4) << "\n";       // 4 0
    for (int i : hash_search(s, "abra")) cout << i << " ";   // 0 7
    cout << "\n" << count_distinct_of_length(s, 3) << "\n";  // 7
}
#endif
