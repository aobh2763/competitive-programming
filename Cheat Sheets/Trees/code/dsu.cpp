// DSU (Disjoint Set Union / Union-Find)
// Path compression + union by size: ~O(alpha(n)) per op, effectively O(1).
// Uses: connected components, Kruskal's MST (sort edges, unite if find differs),
//       cycle detection, offline connectivity.
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;      // p[v] = parent (p[root] = root), sz[root] = component size
    int comps;              // current number of components

    // n singleton components, nodes 0..n-1.
    DSU(int n) : p(n), sz(n, 1), comps(n) { iota(p.begin(), p.end(), 0); }

    // Root of v's component, with path compression (iterative, no stack risk).
    int find(int v) {
        while (p[v] != v) v = p[v] = p[p[v]];
        return v;
    }

    // Merge the components of a and b. Returns false if already in the same one.
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        comps--;
        return true;
    }

    // True if a and b are in the same component.
    bool same(int a, int b) { return find(a) == find(b); }

    // Size of v's component.
    int size(int v) { return sz[find(v)]; }
};

#ifdef LOCAL
int main() {
    DSU d(6);
    d.unite(0, 1); d.unite(1, 2); d.unite(3, 4);
    cout << d.same(0, 2) << "\n";   // 1
    cout << d.same(0, 3) << "\n";   // 0
    cout << d.size(1) << "\n";      // 3
    cout << d.comps << "\n";        // 3
}
#endif
