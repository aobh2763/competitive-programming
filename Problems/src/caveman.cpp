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

vector<vector<int>> G;

void dfs(int node, int n, vector<bool> &visited)
{
    visited[node] = 1;

    for (int neighbor : G[node])
    {
        if (visited[neighbor] == 0)
        {
            dfs(neighbor, n, visited);
        }
    }
}

bool isConnected(int n)
{
    vector<bool> visited = vector<bool>(n, 0);

    dfs(0, n, visited);

    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
            return false;
    }

    return true;
}

bool isSoloNode(vector<bool> soloNode, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (soloNode[i] == 1)
            return true;
    }

    return false;
}

bool isStar(vector<int> degree, int n)
{
    // not solo node
    bool nonOneFound = false;

    for (int i = 0; i < n; i++)
    {
        if (!nonOneFound)
        {
            if (degree[i] != 1)
                nonOneFound = true;
        }
        else
        {
            if (degree[i] != 1)
                return false;
        }
    }

    return true;
}

void solve()
{
    int n, m;

    cin >> n >> m;

    G = vector<vector<int>>(n, vector<int>());

    vector<bool> soloNode = vector<bool>(n, 1);

    vector<int> degree = vector<int>(n, 0);

    int a, b;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;

        a--;
        b--;

        G[a].push_back(b);
        G[b].push_back(a);

        soloNode[a] = 0;
        soloNode[b] = 0;

        degree[a]++;
        degree[b]++;
    }

    if (isSoloNode(soloNode, n))
    {
        cout << "Brain Melt" << endl;
        return;
    }

    if (!isConnected(n))
    {
        cout << "Many" << endl;
        return;
    }

    if (isStar(degree, n))
    {
        cout << "2" << endl;
    }
    else
    {
        cout << "Many" << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }
    return 0;
}