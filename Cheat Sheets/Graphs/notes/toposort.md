# Topological Sort

**File:** `toposort.cpp`

## What it does
Orders the nodes of a directed graph so every edge `u -> v` has `u` before `v`. Also detects cycles. Includes the lexicographically smallest order and a DAG longest-path DP.

## Use it when
- "Order tasks / courses / builds given prerequisites."
- "Is there a circular dependency?" (cycle detection in a directed graph)
- DP over a DAG: longest path, number of paths, minimum cost to reach each node.
- Lexicographically smallest valid ordering (`kahn_lex`).

## Complexity
O(n + m), or O((n + m) log n) for the lexicographic version.

## How it works (Kahn)
Compute in-degrees. Repeatedly remove a node with in-degree 0 and decrease its neighbours' in-degrees. If you removed all `n` nodes, you have a valid order. If not, the leftover nodes lie on or behind a cycle.

## DAG DP pattern
Process nodes in topological order so each node's dependencies are finished first:
```
for (int v : order)
    for (int u : adj[v])
        dp[u] = max(dp[u], dp[v] + 1);     // longest path, or min / += for other DPs
```
- **Count paths from s to t:** `ways[s] = 1`, then `ways[u] += ways[v]` along edges, modulo if needed.
- **Longest path** is easy on a DAG and NP-hard on general graphs.

## Pitfalls
- Always check `order.size() == n` before trusting the order.
- "Lexicographically smallest" means the smallest **sequence**, so use the min-heap version. Plain BFS order is not smallest.
- Lexicographically **largest** order is not just a reversed output. Think about whether the problem wants the largest label first, and reverse the graph if needed.
- Edges are directed. Be careful with "A depends on B" meaning `B -> A` (B comes first).
- Duplicated edges are fine, they just add to the in-degree consistently.
