
#include <bits/stdc++.h>
using namespace std;

const int LOG = 20;

int n, m;
vector<vector<int>> tree;
vector<vector<int>> up;
vector<int> depth, rootChild;

void dfs(int u, int p, int child)
{
    up[0][u] = p;
    rootChild[u] = (u == 1 ? 1 : child);

    for (int v : tree[u])
    {
        if (v == p)
            continue;

        depth[v] = depth[u] + 1;
        dfs(v, u, (u == 1 ? v : child));
    }
}

int lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);

    int diff = depth[u] - depth[v];

    for (int j = 0; j < LOG; j++)
        if (diff & (1 << j))
            u = up[j][u];

    if (u == v)
        return u;

    for (int j = LOG - 1; j >= 0; j--)
    {
        if (up[j][u] != up[j][v])
        {
            u = up[j][u];
            v = up[j][v];
        }
    }

    return up[0][u];
}

int dist(int u, int v)
{
    int w = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[w];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        cin >> n >> m;

        tree.assign(n + 1, {});
        up.assign(LOG, vector<int>(n + 1, 0));
        depth.assign(n + 1, 0);
        rootChild.assign(n + 1, 0);

        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            cin >> u >> v;

            tree[u].push_back(v);
            tree[v].push_back(u);
        }

        dfs(1, 1, 1);

        for (int j = 1; j < LOG; j++)
        {
            for (int v = 1; v <= n; v++)
                up[j][v] = up[j - 1][up[j - 1][v]];
        }

        int ans = depth[n];

        for (int i = 0; i < m; i++)
        {
            int v;
            cin >> v;

            if (rootChild[v] == rootChild[n])
                ans = max(ans, 1 + dist(v, n));
        }

        cout << ans << '\n';
    }

    return 0;
}
