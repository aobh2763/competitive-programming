# Dijkstra and 0-1 BFS

**File:** `dijkstra.cpp`

## What it does
Single-source shortest paths with **non-negative** weights. Also includes **0-1 BFS** for graphs whose weights are only 0 or 1.

## Use it when
- Weighted shortest path, all weights >= 0 (roads, costs, times).
- Weights of 0/1 (e.g. "free to go straight, cost 1 to turn", "cost 1 to flip an edge direction"): use `zero_one_bfs`.

## Complexity
| Algorithm   | Time               |
|-------------|--------------------|
| Dijkstra    | O((n + m) log n)   |
| 0-1 BFS     | O(n + m)           |

## How it works
A min-heap always pops the closest unfinished node. Once popped with its best distance, that distance is final. Outdated heap entries are skipped (`if (dv > d[v]) continue;`), which is called lazy deletion.

## Tricks
- **Dijkstra on states:** nodes can be `(vertex, extra)`, e.g. `(city, fuel)` or `(vertex, used_free_ticket)`. Flatten into one index `v * K + extra`.
- **Counting shortest paths:** keep `cnt[v]`. When `d[v] + w == d[u]`, add `cnt[v]` to `cnt[u]`; on a strictly smaller distance, reset it.
- **Multiple sources:** push all of them with distance 0.
- **Shortest path in a DAG:** topological order + DP is simpler and faster.
- **Max of products / "most reliable path":** take logs, or use a max-heap with probabilities.

## Pitfalls
- **Negative weights break Dijkstra silently.** It will return wrong answers without any error. Use Bellman-Ford.
- Use `long long` distances. `INF = LLONG_MAX / 4` so `INF + w` does not overflow, but still do not relax **from** an unreachable node.
- Don't forget `directed = true` for one-way roads.
- If edges are parallel, Dijkstra handles it naturally (it just takes the best).
- 0-1 BFS only works if **every** weight is exactly 0 or 1.
