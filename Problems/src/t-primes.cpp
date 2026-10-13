#include <bits/stdc++.h>

/* Types */
#define ll long long
#define ld long double
#define vi vector<int>
#define vll vector<ll>
#define vvi vector<vi>

/* Loops */
#define REP(var, start, end) for (var = start; var < end; var++)
#define RREP(var, start, end) for (var = end - 1; var >= start; var--)

/* Debugging */
#define debugSep cout << "-----------------" << endl
#define debugCom(c) cout << (c) << endl
#define debugVal(a) cout << #a << "=" << a << endl
#define debugCol(a)       \
    cout << #a << " : ";  \
    for (auto e : a)      \
        cout << e << " "; \
    cout << endl

/* General */
#define all(x) (x).begin(), (x).end()
#define fixed(n) fixed << setprecision(n)
#define el '\n'

#define YES cout << "YES" << endl
#define NO cout << "NO" << endl

#define Alice cout << "Alice" << endl
#define Bob cout << "Bob" << endl

using namespace std;

/* Constants */
const int oo = 1e9 + 1;
const ll OO = 1e18 + 1;
const int N = 1e6;
const ll MOD = 998244353;

/* Primes */
vi primes, sieve(N, 1);
void initPrimes();

/* Combinatorics */
vll fact(N + 1), inv_fact(N + 1);
void initFact();
ll C(ll n, ll k);
ll P(ll n, ll k);

/* Exponentiation */
ll mod_pow(ll base, ll exp, ll mod);

// GCD function using Euclidean algorithm
ll gcd(ll a, ll b)
{
    while (b)
    {
        a %= b;
        swap(a, b);
    }
    return a;
}

// LCM function: LCM(a, b) = (a*b) / GCD(a, b)
ll lcm(ll a, ll b)
{
    if (a == 0 || b == 0)
        return 0;
    // Divide before multiplying to prevent overflow
    return (a / gcd(a, b)) * b;
}

void solve()
{
    vector<ll> s;
    ll n, m;

    cin >> n;

    ll min = LONG_LONG_MAX;

    for (ll i = 0; i < n; i++)
    {
        cin >> m;
        s.push_back(m);

        if (m < min)
        {
            min = m;
        }
    }

    min++;

    for (ll i = 2; i <= min; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            if (gcd(s[j], i) == 1)
            {
                cout << i << endl;
                return;
            }
        }
    }
}

bool isprime4(ll n)
{
    if (n == 2)
        return true;

    if (n < 2 || n % 2 == 0)
        return false;

    for (ll i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // int t = 1;
    // cin >> t;
    // cin.ignore();

    ll n, x;

    cin >> n;

    for (ll i = 0; i < n; i++)
    {
        cin >> x;

        double sqrtOfX = sqrt(x);

        if (floor(sqrtOfX) == ceil(sqrtOfX))
        {
            ll intSqrtOfX = (ll)sqrtOfX;

            if (isprime4(intSqrtOfX))
            {
                cout << "YES" << "\n";
            }
            else
            {
                cout << "NO" << "\n";
            }
        }
        else
        {
            cout << "NO" << "\n";
        }
    }

    return 0;
}