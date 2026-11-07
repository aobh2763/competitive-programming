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

struct Tree
{
    int n;
    vector<vector<int>> adj;
    vector<int> par, depth, sz, tin, tout, order;

    // Empty tree with n nodes (0-indexed).
    Tree(int n) : n(n), adj(n) {}

    // Add an undirected edge u - v.
    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Iterative DFS from root. Fills par, depth, sz, tin, tout, order. O(n)
    // order[i] = node visited i-th; tout[v] = one past the last tin in v's subtree.
    void dfs(int root = 0)
    {
        par.assign(n, -1);
        depth.assign(n, 0);
        sz.assign(n, 1);
        tin.assign(n, 0);
        tout.assign(n, 0);
        order.clear();
        vector<int> st = {root}, it(n, 0);
        par[root] = -1;
        tin[root] = 0;
        order.push_back(root);
        while (!st.empty())
        {
            int v = st.back();
            if (it[v] < (int)adj[v].size())
            {
                int u = adj[v][it[v]++];
                if (u == par[v])
                    continue;
                par[u] = v;
                depth[u] = depth[v] + 1;
                tin[u] = order.size();
                order.push_back(u);
                st.push_back(u);
            }
            else
            {
                tout[v] = order.size();
                if (par[v] != -1)
                    sz[par[v]] += sz[v];
                st.pop_back();
            }
        }
        sz.clear();
        order.clear();
    }

    // BFS from src. Returns (farthest node, its distance in edges). O(n)
    pair<int, int> farthest(int src)
    {
        vector<int> d(n, -1);
        queue<int> q;
        q.push(src);
        d[src] = 0;
        int best = src;
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            if (d[v] > d[best])
                best = v;
            for (int u : adj[v])
                if (d[u] < 0)
                {
                    d[u] = d[v] + 1;
                    q.push(u);
                }
        }
        return {best, d[best]};
    }

    // Tree diameter in edges: BFS to the farthest node a, then BFS from a. O(n)
    // (For weighted trees, swap BFS for a DFS that sums weights.)
    int diameter()
    {
        int a = farthest(0).first;
        return farthest(a).second;
    }

    // True if u is an ancestor of v (or u == v). Needs dfs() first. O(1)
    bool is_ancestor(int u, int v)
    {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }
};

// ==========================================
//             SOLVE FUNCTION
// ==========================================
void solve()
{
    int n;
    cin >> n;

    Tree tree = Tree(n + 1);

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;

        tree.add_edge(u - 1, v - 1);
    }

    tree.dfs(0);

    map<int, vector<int>> res;
    for (int i = 0; i < n; i++)
    {
        // cout << tree.adj[i] << "\n";
        if (tree.adj[i].size() == 1 && i != 0)
        {
            // cout << i + 1 << " ";
            for (int j = 0; j < n; j++)
            {
                if (tree.is_ancestor(j, i) && j != i)
                {
                    res[j + 1].push_back(i + 1);
                }
            }
        }
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        int x, y;
        cin >> x >> y;

        int c = res[x].size() * res[y].size();
        cout << c << "\n";
    }
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