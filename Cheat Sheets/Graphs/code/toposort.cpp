// Topological sort of a directed graph (Kahn's algorithm). O(n + m)
// If the result has fewer than n nodes, the graph has a cycle.
// Also: lexicographically smallest order, and longest path in a DAG.
#include <bits/stdc++.h>
using namespace std;

struct DAG {
    int n;
    vector<vector<int>> adj;

    // n nodes (0-indexed), no edges.
    DAG(int n = 0) : n(n), adj(n) {}

    // Directed edge u -> v ("u must come before v").
    void add_edge(int u, int v) { adj[u].push_back(v); }

    // Kahn's algorithm: repeatedly remove nodes with in-degree 0.
    // Returns the order; order.size() < n means a cycle exists.
    vector<int> kahn() {
        vector<int> indeg(n, 0), order;
        for (int v = 0; v < n; v++) for (int u : adj[v]) indeg[u]++;
        queue<int> q;
        for (int v = 0; v < n; v++) if (indeg[v] == 0) q.push(v);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            order.push_back(v);
            for (int u : adj[v]) if (--indeg[u] == 0) q.push(u);
        }
        return order;
    }

    // Same, but always takes the smallest available label (min-heap). O((n + m) log n)
    // To get the lexicographically LARGEST order, take the largest label or reverse
    // the graph and label order as the problem requires (don't just reverse the output).
    vector<int> kahn_lex() {
        vector<int> indeg(n, 0), order;
        for (int v = 0; v < n; v++) for (int u : adj[v]) indeg[u]++;
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int v = 0; v < n; v++) if (indeg[v] == 0) pq.push(v);
        while (!pq.empty()) {
            int v = pq.top(); pq.pop();
            order.push_back(v);
            for (int u : adj[v]) if (--indeg[u] == 0) pq.push(u);
        }
        return order;
    }

    // Longest path (in edges) ending at each node, via DP in topological order.
    // Returns an empty vector if the graph has a cycle.
    vector<int> longest_path_ending_at() {
        vector<int> order = kahn();
        if ((int)order.size() < n) return {};
        vector<int> len(n, 0);
        for (int v : order) for (int u : adj[v]) len[u] = max(len[u], len[v] + 1);
        return len;
    }
};

#ifdef LOCAL
int main() {
    DAG g(6);
    g.add_edge(5, 2); g.add_edge(5, 0); g.add_edge(4, 0);
    g.add_edge(4, 1); g.add_edge(2, 3); g.add_edge(3, 1);
    for (int v : g.kahn_lex()) cout << v << " ";     // 4 5 0 2 3 1
    cout << "\n";
    auto len = g.longest_path_ending_at();
    cout << len[1] << "\n";                          // 3 (5->2->3->1)
    g.add_edge(1, 5);
    cout << (g.kahn().size() < 6) << "\n";           // 1 (cycle)
}
#endif
