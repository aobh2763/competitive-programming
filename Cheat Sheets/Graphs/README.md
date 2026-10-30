# Graph Algorithms Cheat Sheet

Each `.cpp` file has a matching `.md` with the "when and why".

## Which algorithm do I need?

| Problem looks like...                                          | Use                          | File |
|----------------------------------------------------------------|------------------------------|------|
| Shortest path, **unweighted** / grid / min number of moves     | BFS                          | `graph_traversal` |
| Shortest path, weights are only **0 or 1**                     | 0-1 BFS                      | `dijkstra` |
| Shortest path, **non-negative** weights                        | Dijkstra                     | `dijkstra` |
| Shortest path with **negative** edges / detect negative cycle  | Bellman-Ford                 | `bellman_ford` |
| Shortest paths between **all pairs**, n <= ~500                | Floyd-Warshall               | `floyd_warshall` |
| Connected components, 2-colouring, "is it bipartite?"          | BFS / DFS                    | `graph_traversal` |
| Order tasks with dependencies, detect cycle in directed graph  | Topological sort             | `toposort` |
| Mutually reachable groups in a **directed** graph              | SCC (Tarjan)                 | `scc` |
| Critical roads / critical vertices in an **undirected** graph  | Bridges & articulation points| `bridges` |
| Cheapest way to connect everything                             | MST (Kruskal)                | `mst` |

## Shortest path decision flow

1. Unweighted (or all weights equal)? **BFS**.
2. Weights only 0 and 1? **0-1 BFS**.
3. Any negative weight? **Bellman-Ford** (or Floyd if n is tiny and you need all pairs).
4. Otherwise **Dijkstra**.

## Graph size guide

| Constraint            | Typical choice                       |
|-----------------------|--------------------------------------|
| n, m <= 2e5 - 1e6     | BFS, DFS, Dijkstra, SCC, toposort    |
| n <= 5,000            | O(n^2) algorithms OK                 |
| n <= 400 - 500       | Floyd-Warshall O(n^3)                |
| n * m <= ~1e7         | Bellman-Ford OK                      |

## Pitfalls that apply to everything here

- **Directed vs undirected:** `add_edge` defaults to undirected in most files. Pass `directed = true` when the problem says "from a to b".
- **INF overflow:** `INF` is `LLONG_MAX / 4`, so `INF + w` stays safe. Do not use `INT_MAX` with `long long` distances.
- **Indexing:** all structures are 0-indexed. Convert 1-indexed input.
- **Multi-edges and self-loops:** the files handle them, but make sure your problem's definition matches (e.g. do parallel edges make something "not a bridge"?).
- **Recursion depth:** every DFS here is iterative, since a path graph with 2e5 nodes overflows a recursive DFS on many judges.
- **Multiple test cases:** build a fresh struct per test or clear everything.
