// Random utilities for stress testing and for hashing:
//  - rng, rnd(l, r), shuffle, random array / permutation / string / tree / graph
//  - custom_hash: anti-hack hash for unordered_map / unordered_set
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// Seeded from the clock so each run differs. For reproducible tests use mt19937_64 rng(seed).
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// Uniform random integer in [l, r] (inclusive).
ll rnd(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(rng); }

// Uniform random real in [l, r).
double rnd_real(double l, double r) { return uniform_real_distribution<double>(l, r)(rng); }

// Random array of n integers in [lo, hi].
vector<ll> rand_array(int n, ll lo, ll hi) {
    vector<ll> a(n);
    for (auto& x : a) x = rnd(lo, hi);
    return a;
}

// Random permutation of 1..n (or 0..n-1 if base = 0).
vector<int> rand_perm(int n, int base = 1) {
    vector<int> p(n);
    iota(p.begin(), p.end(), base);
    shuffle(p.begin(), p.end(), rng);
    return p;
}

// Random string of length n over the first `alpha` lowercase letters.
string rand_string(int n, int alpha = 26) {
    string s(n, 'a');
    for (auto& c : s) c = 'a' + rnd(0, alpha - 1);
    return s;
}

// Random tree on nodes 1..n as edge list. shape: 0 = random, 1 = path, 2 = star,
// 3 = "deep" (parent is one of the last few nodes, long chains), 4 = binary-ish.
vector<pair<int, int>> rand_tree(int n, int shape = 0) {
    vector<pair<int, int>> e;
    for (int v = 2; v <= n; v++) {
        int p;
        if (shape == 0) p = rnd(1, v - 1);
        else if (shape == 1) p = v - 1;
        else if (shape == 2) p = 1;
        else if (shape == 3) p = rnd(max(1, v - 3), v - 1);
        else p = v / 2;
        e.push_back({p, v});
    }
    // relabel randomly so node 1 is not always the root, and shuffle the edge order
    auto perm = rand_perm(n);
    for (auto& [a, b] : e) { a = perm[a - 1]; b = perm[b - 1]; if (rnd(0, 1)) swap(a, b); }
    shuffle(e.begin(), e.end(), rng);
    return e;
}

// Random connected simple graph with n nodes and m edges (n - 1 <= m <= n(n-1)/2), nodes 1..n.
vector<pair<int, int>> rand_connected_graph(int n, int m) {
    auto e = rand_tree(n, 0);
    set<pair<int, int>> used;
    for (auto [a, b] : e) used.insert({min(a, b), max(a, b)});
    while ((int)e.size() < m) {
        int a = rnd(1, n), b = rnd(1, n);
        if (a == b) continue;
        if (a > b) swap(a, b);
        if (used.insert({a, b}).second) e.push_back({a, b});
    }
    return e;
}

// Hash for unordered_map / unordered_set that resists anti-hash tests (splitmix64 + random seed).
// Usage: unordered_map<ll, int, custom_hash> mp;
struct custom_hash {
    // One round of the splitmix64 mixing function.
    static ull splitmix64(ull x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(ull x) const {
        static const ull FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

#ifdef LOCAL
int main() {
    for (ll x : rand_array(5, 1, 10)) cout << x << " ";
    cout << "\n";
    for (int x : rand_perm(5)) cout << x << " ";
    cout << "\n" << rand_string(8, 3) << "\n";
    for (auto [a, b] : rand_tree(5, 1)) cout << a << "-" << b << " ";
    cout << "\n";
    unordered_map<ll, int, custom_hash> mp;
    mp[123456789012LL] = 7;
    cout << mp[123456789012LL] << "\n";                       // 7
}
#endif
