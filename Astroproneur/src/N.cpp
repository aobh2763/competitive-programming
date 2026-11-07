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

vector<int> stringxor(string v1, string v2, int n)
{
    vector<int> v = vector<int>(n, 0);

    for (int i = 0; i < n; i++)
    {
        if (v1[i] == v2[i])
        {
            v[i] = 0;
        }
        else
        {
            v[i] = 1;
        }
    }

    return v;
}

long long count(vector<int> v, ll n)
{
    long long zeroCount = 0;
    long long oneCount = 0;

    for (ll i = 0; i < n; i++)
    {
        if (v[i] == 0)
            zeroCount++;
        if (v[i] == 1)
            oneCount++;
    }

    return zeroCount * oneCount;
}

long long countstr(string v, ll n)
{
    long long zeroCount = 0;
    long long oneCount = 0;

    for (ll i = 0; i < n; i++)
    {
        if (v[i] == '0')
            zeroCount++;
        if (v[i] == '1')
            oneCount++;
    }

    return zeroCount * oneCount;
}

void solve()
{
    int n, k;

    cin >> n >> k;

    string a_1, a_last;

    cin >> a_1;
    cin >> a_last;

    // vector<int> a_1_vec = vector<int>(n, 0);
    // vector<int> a_last_vec = vector<int>(n, 0);

    vector<int> a_both_vec = stringxor(a_1, a_last, n);

    ll lencodes = (1LL << k) + 1;

    long long first_count = countstr(a_1, n);
    long long last_count = countstr(a_last, n);
    long long both_count = count(a_both_vec, n);

    /*
    for (int i = 0; i < lencodes; i++)
    {
        if (i % 3 == 0)
        {
            first_present[lencodes - 1 - i] = false;
            last_present[i] = false;
        }
        else
        {
            first_present[lencodes - 1 - i] = true;
            last_present[i] = true;
        }
    }
        */

    ll sum = 0;

    if (lencodes % 3 == 0)
    {
        sum = (lencodes / 3) * (first_count + last_count + both_count);
    }
    else
    {
        sum = (lencodes / 3) * (first_count + last_count + both_count) + first_count + last_count;
    }

    cout << sum << endl;
}

int main()
{
    FAST_IO

    int t = 1;
    cin >> t; // Comment this out if the problem has only 1 test case
    while (t--)
    {
        solve();
    }

    return 0;
}