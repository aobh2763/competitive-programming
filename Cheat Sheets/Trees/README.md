# Trees & Range-Query Cheat Sheet

Each `.cpp` file has a matching `.md` with the "when and why".

## Which structure do I need?

| Problem looks like...                                   | Use                          | File |
|---------------------------------------------------------|------------------------------|------|
| Point update + prefix/range **sum**                     | Fenwick                      | `fenwick` |
| Point update + range min/max/gcd/any associative op     | Iterative segment tree       | `segtree` |
| **Range** update + range query                          | Lazy segment tree            | `lazy_segtree` |
| Static array, many range **min/max/gcd** queries        | Sparse table                 | `sparse_table` |
| Static array, range **sum**                             | Plain prefix sums            | (no file needed) |
| Connectivity, merging groups, Kruskal                   | DSU                          | `dsu` |
| Subtree sizes, depth, diameter, subtree = range         | DFS / Euler tour             | `tree_basics` |
| LCA, distance between nodes, k-th ancestor              | Binary lifting               | `lca` |
| Path update/query on a tree (sum, max...), subtree query| Heavy-light decomposition    | `hld` |

## Constraint -> complexity guide

| n               | Aim for              |
|-----------------|----------------------|
| n <= 10         | O(n!)                |
| n <= 20         | O(2^n * n)           |
| n <= 500        | O(n^3)               |
| n <= 5,000      | O(n^2)               |
| n <= 2e5 - 1e6  | O(n log n)           |
| n <= 1e7        | O(n)                 |

Rule of thumb: about 1e8 simple operations per second in C++.

## Pitfalls that apply to everything here

- **Overflow:** sums of up to 2e5 values of 1e9 need `long long`.
- **Indexing:** Fenwick is 1-indexed, the segment tree is 0-indexed half-open `[l, r)`, the lazy tree is 0-indexed inclusive `[l, r]`. Check before you call.
- **Multiple test cases:** reset or rebuild every structure per test. Forgetting to clear `adj` is the classic bug.
- **Recursion depth:** a path-shaped tree with n = 2e5 overflows a recursive DFS on many judges. These files use iterative DFS for that reason.
- **Forests / disconnected graphs:** a single `dfs(0)` only covers one component.
