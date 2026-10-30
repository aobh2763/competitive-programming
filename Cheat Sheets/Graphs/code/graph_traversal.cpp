// Graph traversal toolkit: BFS shortest paths (unweighted), path reconstruction,
// connected components, bipartite check, grid BFS. All iterative, 0-indexed.
// Complexity: O(n + m) for everything on Graph, O(R * C) for grid_bfs.
#include <bits/stdc++.h>
using namespace std;

struct Graph {
    int n;
    vector<vector<int>> adj;

    // Graph with n nodes (0-indexed), no edges.
    Graph(int n = 0) : n(n), adj(n) {}

    // Add edge u - v (or u -> v when directed = true).
    void add_edge(int u, int v, bool directed = false) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }

    // BFS from src. Returns dist (edges), -1 = unreachable.
    // If par != nullptr it is filled with BFS-tree parents (-1 for src/unreached).
    vector<int> bfs(int src, vector<int>* par = nullptr) {
        vector<int> dist(n, -1);
        if (par) par->assign(n, -1);
        queue<int> q;
        dist[src] = 0;
        q.push(src);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int u : adj[v]) if (dist[u] < 0) {
                dist[u] = dist[v] + 1;
                if (par) (*par)[u] = v;
                q.push(u);
            }
        }
        return dist;
    }

    // Rebuild the path src -> t from a BFS/Dijkstra parent array.
    // Returns an empty vector if t is unreachable from src.
    static vector<int> path(const vector<int>& par, int src, int t) {
        vector<int> p;
        if (t != src && par[t] == -1) return p;
        for (int v = t; v != -1; v = par[v]) p.push_back(v);
        reverse(p.begin(), p.end());
        return p;
    }

    // Label connected components (undirected graphs). Returns (comp id per node, count).
    pair<vector<int>, int> components() {
        vector<int> comp(n, -1);
        int c = 0;
        for (int s = 0; s < n; s++) {
            if (comp[s] != -1) continue;
            vector<int> st = {s};
            comp[s] = c;
            while (!st.empty()) {
                int v = st.back(); st.pop_back();
                for (int u : adj[v]) if (comp[u] == -1) { comp[u] = c; st.push_back(u); }
            }
            c++;
        }
        return {comp, c};
    }

    // 2-colour the graph with BFS. Returns false if an odd cycle exists.
    // color[v] is 0 or 1 when the graph is bipartite.
    bool bipartite(vector<int>& color) {
        color.assign(n, -1);
        for (int s = 0; s < n; s++) {
            if (color[s] != -1) continue;
            queue<int> q;
            q.push(s); color[s] = 0;
            while (!q.empty()) {
                int v = q.front(); q.pop();
                for (int u : adj[v]) {
                    if (color[u] == -1) { color[u] = color[v] ^ 1; q.push(u); }
                    else if (color[u] == color[v]) return false;
                }
            }
        }
        return true;
    }
};

// BFS on a grid from (sr, sc). '#' is a wall, anything else is free.
// Returns a matrix of step counts, -1 = unreachable. 4-directional moves.
vector<vector<int>> grid_bfs(const vector<string>& g, int sr, int sc) {
    int R = g.size(), C = g[0].size();
    const int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
    vector<vector<int>> d(R, vector<int>(C, -1));
    queue<pair<int, int>> q;
    d[sr][sc] = 0;
    q.push({sr, sc});
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nc < 0 || nr >= R || nc >= C) continue;
            if (g[nr][nc] == '#' || d[nr][nc] != -1) continue;
            d[nr][nc] = d[r][c] + 1;
            q.push({nr, nc});
        }
    }
    return d;
}

#ifdef LOCAL
int main() {
    Graph g(6);
    g.add_edge(0, 1); g.add_edge(1, 2); g.add_edge(0, 3); g.add_edge(3, 2); g.add_edge(4, 5);
    vector<int> par;
    auto d = g.bfs(0, &par);
    cout << d[2] << " " << d[4] << "\n";                       // 2 -1
    for (int v : Graph::path(par, 0, 2)) cout << v << " ";     // 0 1 2
    cout << "\n" << g.components().second << "\n";             // 2
    vector<int> col;
    cout << g.bipartite(col) << "\n";                          // 1 (even cycle)
    vector<string> grid = {"..#", ".#.", "..."};
    cout << grid_bfs(grid, 0, 0)[2][2] << "\n";                // 4
}
#endif
