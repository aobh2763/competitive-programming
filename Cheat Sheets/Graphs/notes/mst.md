# Minimum Spanning Tree (Kruskal)

**File:** `mst.cpp`

## What it does
Picks `n - 1` edges that connect all nodes with the **minimum total weight**. If the graph is disconnected it returns a minimum spanning forest and sets `connected = false`.

## Use it when
- "Connect all cities/computers with minimum total cost."
- "Minimize the maximum edge on a path between two nodes." The MST path minimizes the bottleneck (minimax path).
- Clustering: stop Kruskal early after `n - k` merges to get `k` groups.
- "Second best MST", "is this edge in some MST?" (see tricks).

## Complexity
O(m log m) for the sort, near-constant per DSU operation. Memory O(n + m).

## How it works
Sort edges by weight. Walk through them; keep an edge iff its endpoints are in different DSU components (so it does not create a cycle).

## Tricks
- **Max spanning tree:** sort in descending order.
- **Bottleneck path between u and v:** the largest edge on the MST path between them. Use LCA with max-edge tracking (see `lca.md` in the trees folder).
- **Edge in some MST?** An edge `(u, v, w)` belongs to some MST iff `w <=` the bottleneck between `u` and `v` in the MST built without it. Equivalent: process edges in equal-weight groups, check connectivity before uniting.
- **Unique MST?** All MSTs share the same multiset of weights. The MST is unique iff, for every group of equal-weight edges, each edge that is accepted could not have been swapped for another edge of the same weight that connects the same two components.
- **Prim:** O(n^2) with a matrix or O(m log n) with a heap, useful for dense graphs.

## Pitfalls
- `used` stores indices into the **input** edge vector, not positions after sorting.
- Check `connected` before trusting `cost`: a disconnected graph has no spanning tree.
- Use `long long` for cost.
- Ties are broken arbitrarily. If the problem asks for a specific MST (e.g. lexicographically smallest edge list), sort with a secondary key.
- Self-loops and multi-edges are fine, the DSU ignores useless ones.
