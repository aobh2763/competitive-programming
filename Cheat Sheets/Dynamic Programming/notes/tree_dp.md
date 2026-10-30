# DP on Trees & Rerooting

**File:** `tree_dp.cpp`

## What it does
Roots a tree and computes answers bottom-up. Includes subtree sizes, `max_independent_set`, `diameter`, and `sum_of_distances` (rerooting).

## Use it when
- "For each subtree, the best choice depends on its children's best choices."
- "Pick nodes with no two adjacent" (independent set), "longest path", "color/choose per node".
- "For **every** node as root, compute X" (sum of distances, farthest node, ...): **rerooting**.

## The idea: process children first
`root()` stores the nodes in BFS order (parents before children). Looping over that order **backwards** guarantees every child is finished before its parent. No recursion, so it is safe for path-shaped trees with 2e5 nodes.

## Typical states
| Problem              | State                                         |
|----------------------|-----------------------------------------------|
| Independent set      | `dp0[v]` (v not chosen), `dp1[v]` (v chosen)  |
| Diameter             | `down[v]` = longest downward path from `v`; combine the best two children |
| Subtree sum / size   | `sum[v] = a[v] + sum of children`             |
| Distance sums        | `down[v]`, then fix with the parent's answer  |

## Rerooting in two passes
1. **Bottom-up:** compute everything for the tree rooted at node 0.
2. **Top-down:** the answer for child `c` equals the parent `v`'s full answer with `c`'s subtree "moved" to the other side. For distance sums: `ans[c] = ans[v] - sz[c] + (n - sz[c])`, because `sz[c]` nodes get one step closer and `n - sz[c]` get one step farther.

For harder cases (max, not sums) keep prefix and suffix aggregates over a node's children.

## Complexity
O(n) time and memory for everything.

## Pitfalls
- Recursive DFS overflows the stack on deep trees; this file avoids recursion.
- `max_independent_set` assumes **non-negative** weights.
- Node numbers are 0-indexed. Rooting at a different node changes `par` and `order`.
- A forest needs one `root()` per component.
- Tree knapsack (choose `k` nodes) is O(n * k) with a careful merge, a separate technique.
