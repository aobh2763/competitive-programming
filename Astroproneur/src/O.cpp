#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <numeric>
#include <unordered_set>
#include <cmath>
#include <iterator>

using namespace std;

// --- Speed Optimization ---
#define FAST_IO                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

// --- Type Aliases ---
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;

// --- Macros ---
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define sz(x) ((int)(x).size())

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "[";
    for (size_t i = 0; i < v.size(); ++i)
    {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    return os << "]";
}

// ==========================================
//             SOLVE FUNCTION
// ==========================================
void solve()
{
    int n, k;
    cin >> n >> k;

    if (k == 0)
    {
        for (int i = 1; i <= n; i++)
        {
            cout << i << " ";
        }
        return;
    }

    if (k == n - 1)
    {
        for (int i = n; i > 0; i--)
        {
            cout << i << " ";
        }
        return;
    }

    vi a;
    for (int i = 2; i <= n - k; i++)
    {
        a.push_back(i);
    }
    a.push_back(1);
    for (int i = n; i > n - k; i--)
    {
        a.push_back(i);
    }

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
}

int main()
{
    FAST_IO

    int t = 1;
    // cin >> t; // Comment this out if the problem has only 1 test case
    while (t--)
    {
        solve();
    }

    return 0;
}