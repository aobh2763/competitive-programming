# Tree Basics: DFS, Euler Tour, Diameter

**File:** `tree_basics.cpp`

## What it does
One iterative DFS computes: `par`, `depth`, `sz` (subtree size), `tin`/`tout` (Euler tour), and `order` (DFS visit order). Also finds the diameter.

## Key fact: subtree = contiguous range
The subtree of `v` is exactly positions `[tin[v], tout[v])` in `order`. This turns tree problems into array problems:
- **Subtree sum / min / max:** put values at `tin[v]` in a BIT or segment tree.
- **Is u an ancestor of v?** `tin[u] <= tin[v] && tout[v] <= tout[u]`.
- **Update a whole subtree:** range update on `[tin[v], tout[v])` with a lazy tree.

## Use it when
- "For each node, compute something over its subtree" (subtree sums, counts).
- "Query/update the subtree of v".
- You need depth, parent, or an ordering with children before parents.

## Tree DP pattern (no recursion needed)
`order` lists parents before children. To do bottom-up DP, loop **backwards** over `order` and push each node's value into `par[v]`:

```
for (int i = n - 1; i > 0; i--) {
    int v = order[i];
    dp[par[v]] += dp[v];     // or max, etc.
}
```

## Diameter
Two BFS passes: BFS from any node to find the farthest node `a`, then BFS from `a`; the largest distance is the diameter.
- Works for unweighted trees, and for **non-negative** weighted trees if you swap BFS for a weighted traversal.
- Fails with negative weights.

## Complexity
All O(n) time and memory.

## Pitfalls
- A recursive DFS overflows the stack on a path of 2e5 nodes. Keep it iterative.
- `tout` is **exclusive** (one past the last `tin`). Subtree size equals `tout - tin`.
- 0-indexed nodes. Convert if the input is 1-indexed.
- On forests, run `dfs` per component (this file handles a single root).
- Reset `adj` between test cases.
