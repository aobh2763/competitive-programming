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

bool isUniqueOutsideOf(vector<long long> v, int r, int l, int n)
{
    map<long long, bool> found = map<long long, bool>();

    bool isUnique = true;

    for (long long i = 0; i < n; i++)
    {
        if (i >= r && i <= l)
            continue;

        if (found[v[i]])
        {
            isUnique = false;
            break;
        }

        found[v[i]] = true;
    }

    return isUnique;
}

// ==========================================
//             SOLVE FUNCTION
// ==========================================
void solve()
{
    int n;

    cin >> n;

    vector<long long> v(n);
    map<long long, bool> seen1;
    map<long long, bool> seen2;

    for (long long i = 0; i < n; i++)
    {
        cin >> v[i];

        seen1[v[i]] = false;
        seen2[v[i]] = false;
    }

    map<long long, bool> found = map<long long, bool>();

    bool isUnique = true;

    for (long long i = 0; i < n; i++)
    {
        if (found[v[i]])
        {
            isUnique = false;
            break;
        }

        found[v[i]] = true;
    }

    if (isUnique)
    {
        cout << 0 << endl;
        return;
    }

    long long firstSeenFromLeft = -1;
    long long firstSeenFromRight = -1;
    long long secondSeenFromLeft = -1;
    long long secondSeenFromRight = -1;

    for (long long i = 0; i < n; i++)
    {
        if (seen1[v[i]])
        {
            firstSeenFromLeft = i;
            break;
        }

        seen1[v[i]] = true;
    }

    for (long long i = n - 1; i >= 0; i--)
    {
        if (seen1[v[i]])
        {
            firstSeenFromRight = i;
            break;
        }

        seen1[v[i]] = true;
    }

    for (long long i = n - 1; i >= 0; i--)
    {
        if (seen2[v[i]])
        {
            secondSeenFromRight = i;
            break;
        }

        seen2[v[i]] = true;
    }

    for (long long i = 0; i < n; i++)
    {
        if (seen2[v[i]])
        {
            secondSeenFromLeft = i;
            break;
        }

        seen2[v[i]] = true;
    }

    long long res1 = abs(firstSeenFromLeft - firstSeenFromRight);
    long long res2 = abs(secondSeenFromLeft - secondSeenFromRight);

    long long res = n;

    map<long long, int> pref, suff;

    int badSuffix = 0;
    int overlap = 0;

    for (long long x : v)
    {
        suff[x]++;
        if (suff[x] == 2)
            badSuffix++;
    }

    int r = 0;

    for (int l = 0; l <= n; l++)
    {
        while (r < l)
        {
            long long x = v[r];

            if (suff[x] == 2)
                badSuffix--;

            if (suff[x] == 1 && pref[x] > 0)
                overlap--;

            suff[x]--;
            r++;
        }

        while (r < n && (badSuffix > 0 || overlap > 0))
        {
            long long x = v[r];

            if (suff[x] == 2)
                badSuffix--;

            if (suff[x] == 1 && pref[x] > 0)
                overlap--;

            suff[x]--;
            r++;
        }

        res = min(res, (long long)r - l);

        if (l == n)
            break;

        long long x = v[l];

        if (pref[x] > 0)
            break;

        pref[x]++;

        if (suff[x] > 0)
            overlap++;
    }

    cout << res << '\n';
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