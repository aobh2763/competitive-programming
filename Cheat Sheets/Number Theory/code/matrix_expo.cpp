// Matrix exponentiation: compute M^e mod p in O(k^3 log e) for a k x k matrix.
// Uses: linear recurrences (Fibonacci-like) for huge n, counting walks of length L
// in a graph, linear DP transitions repeated many times.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1'000'000'007;

struct Mat {
    int n;
    vector<vector<ll>> a;

    // n x n zero matrix.
    Mat(int n = 0) : n(n), a(n, vector<ll>(n, 0)) {}

    // n x n identity matrix.
    static Mat identity(int n) {
        Mat I(n);
        for (int i = 0; i < n; i++) I.a[i][i] = 1;
        return I;
    }

    // Matrix product mod MOD. O(n^3). Accumulates with one % per inner step
    // (MOD^2 < 9.2e18 so a single product fits in a signed 64-bit).
    Mat operator*(const Mat& o) const {
        Mat r(n);
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++) {
                if (a[i][k] == 0) continue;
                for (int j = 0; j < n; j++)
                    r.a[i][j] = (r.a[i][j] + a[i][k] * o.a[k][j]) % MOD;
            }
        return r;
    }

    // this^e by repeated squaring. O(n^3 log e)
    Mat pow(ll e) const {
        Mat r = identity(n), b = *this;
        for (; e > 0; e >>= 1, b = b * b) if (e & 1) r = r * b;
        return r;
    }
};

// n-th Fibonacci number mod MOD (F0 = 0, F1 = 1) using [[1,1],[1,0]]^n. O(log n)
ll fib(ll n) {
    Mat M(2);
    M.a = {{1, 1}, {1, 0}};
    return M.pow(n).a[0][1];
}

// k-th term of a linear recurrence  x_n = c[0]*x_{n-1} + ... + c[d-1]*x_{n-d}
// given initial terms init[0..d-1]. Builds the companion matrix. O(d^3 log k)
ll linear_recurrence(const vector<ll>& c, const vector<ll>& init, ll k) {
    int d = c.size();
    if (k < d) return init[k] % MOD;
    Mat M(d);
    for (int j = 0; j < d; j++) M.a[0][j] = c[j] % MOD;
    for (int i = 1; i < d; i++) M.a[i][i - 1] = 1;
    Mat P = M.pow(k - d + 1);
    // state vector = (x_{d-1}, x_{d-2}, ..., x_0); answer is first entry after the power
    ll res = 0;
    for (int j = 0; j < d; j++) res = (res + P.a[0][j] * (init[d - 1 - j] % MOD)) % MOD;
    return res;
}

// Number of walks of exactly L edges from u to v in a graph with adjacency matrix A.
ll count_walks(const Mat& A, int u, int v, ll L) { return A.pow(L).a[u][v]; }

#ifdef LOCAL
int main() {
    cout << fib(10) << " " << fib(90) << "\n";                  // 55 and F90 mod 1e9+7
    cout << linear_recurrence({1, 1}, {0, 1}, 10) << "\n";      // 55
    cout << linear_recurrence({2, 3, 1}, {1, 1, 2}, 20) << "\n";
    Mat A(3);   // triangle graph: walks of length 2 from 0 to 0 = 2
    A.a = {{0, 1, 1}, {1, 0, 1}, {1, 1, 0}};
    cout << count_walks(A, 0, 0, 2) << "\n";                    // 2
}
#endif
