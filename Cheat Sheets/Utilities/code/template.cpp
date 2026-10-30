// Contest template: typedefs, short macros, constants, chmin/chmax, a debug printer that
// only exists when compiled with -DLOCAL (so judges never see it), and a multi-test skeleton.
// Compile locally with:  g++ -std=c++17 -O2 -Wall -Wextra -DLOCAL template.cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define rep(i, a, b) for (int i = (a); i < (b); i++)     // i = a .. b-1
#define per(i, a, b) for (int i = (b) - 1; i >= (a); i--) // i = b-1 .. a

const int INF = 1e9;
const ll LINF = 1e18;
const ll MOD = 1'000'000'007;
const double EPS = 1e-9;

// a = min(a, b); returns true if a changed. Handy in DP: chmin(dp[i], dp[j] + w);
template<class T> bool chmin(T& a, const T& b) { if (b < a) { a = b; return true; } return false; }

// a = max(a, b); returns true if a changed.
template<class T> bool chmax(T& a, const T& b) { if (a < b) { a = b; return true; } return false; }

#ifdef LOCAL
// Forward declarations so printers can nest (vector<pair<int, vector<int>>> etc.).
template<class A, class B> ostream& operator<<(ostream& os, const pair<A, B>& p);
template<class T, class = decltype(declval<T>().begin()),
         class = typename enable_if<!is_same<T, string>::value>::type>
ostream& operator<<(ostream& os, const T& c);

// Prints a pair as (a, b).
template<class A, class B> ostream& operator<<(ostream& os, const pair<A, B>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

// Prints any container (vector, set, map, array, ...) as {a, b, c}. Strings are excluded.
template<class T, class, class>
ostream& operator<<(ostream& os, const T& c) {
    os << '{';
    bool first = true;
    for (auto& x : c) { if (!first) os << ", "; first = false; os << x; }
    return os << '}';
}

// Recursion ends: print newline.
void dbg_out() { cerr << endl; }

// Prints the remaining arguments separated by spaces.
template<class H, class... T> void dbg_out(H h, T... t) { cerr << ' ' << h; dbg_out(t...); }

// dbg(x, v) prints:  [x, v]: 5 {1, 2, 3}   to stderr (not stdout, so output stays clean).
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...) ((void)0)
#endif

// Solve one test case. Read input, compute, print.
void solve() {
    int n;
    cin >> n;
    vi a(n);
    for (auto& x : a) cin >> x;
    dbg(n, a);
    ll s = 0;
    for (int x : a) s += x;
    cout << s << '\n';
}

int main() {
    ios::sync_with_stdio(false);    // don't mix cin/cout with scanf/printf after this
    cin.tie(nullptr);               // don't flush cout before every cin
    int T = 1;
    // cin >> T;                    // uncomment for multi-test problems
    while (T--) solve();
#ifdef LOCAL
    cerr << "Time: " << (double)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
#endif
}
