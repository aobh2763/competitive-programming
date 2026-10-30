# DSU (Union-Find)

**File:** `dsu.cpp`

## What it does
Maintains a partition of `n` elements into groups. Supports merging two groups and asking whether two elements are in the same group, in nearly O(1).

## Use it when
- "Are u and v connected?" with edges only being **added**.
- **Kruskal's MST:** sort edges by weight, `unite(u, v)` and keep the edge if it returned `true`.
- Counting connected components (`comps`).
- Cycle detection in an undirected graph: if `unite(u, v)` returns `false`, that edge closes a cycle.
- Grouping equivalent items (e.g. "accounts merge", "same-letter positions").

## Complexity
Path compression + union by size gives about O(alpha(n)) per operation, which is effectively constant.

## Kruskal template
```
sort(edges.begin(), edges.end());          // by weight
DSU d(n); long long cost = 0;
for (auto [w, u, v] : edges)
    if (d.unite(u, v)) cost += w;
```

## Variants worth knowing
- **Deletions are not supported.** If edges are removed, process **offline in reverse** (turn deletions into additions).
- **DSU with rollback:** union by size **without** path compression, store a history stack; gives O(log n) per op and allows undo (used in offline dynamic connectivity).
- **Weighted DSU:** store each node's offset to its parent to handle relations like "a - b = x".
- **Bipartite check:** use 2n nodes (v and v + n); unite `u` with `v+n` and `u+n` with `v`.

## Pitfalls
- Always call `find` before comparing roots; never read `p[v]` directly.
- `size(v)` must go through `find(v)`, since only roots hold the size.
- Not a replacement for shortest paths or anything that needs the actual path.
