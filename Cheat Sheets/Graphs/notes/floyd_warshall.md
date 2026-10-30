# Floyd-Warshall

**File:** `floyd_warshall.cpp`

## What it does
Computes the shortest distance between **every pair** of nodes.

## Use it when
- `n <= ~400-500` and you need many different source/target pairs.
- Negative edges are allowed (no negative cycles needed for correct values).
- You need **transitive closure**: is there any path from i to j? (Use booleans or bitsets.)
- Graph is dense, so O(n^3) beats running Dijkstra from every node.

## Complexity
| What   | Cost    |
|--------|---------|
| Time   | O(n^3)  |
| Memory | O(n^2)  |

For n = 500 that is about 1.25e8 operations, which is fine in C++.

## How it works
After processing node `k`, `d[i][j]` is the best path using only nodes `0..k` as intermediates. The loop order is **k outermost**, then `i`, then `j`. Swapping the order gives wrong answers.

## Tricks
- **Path reconstruction:** `nxt[i][j]` stores the first step of the best path. `path(u, v)` follows it.
- **Negative cycles:** after `run()`, `d[i][i] < 0` for some `i` means a negative cycle through `i`.
- **Transitive closure:** replace `+`/`min` with `&&`/`||`, and use `bitset` rows for a 64x speedup: `if (r[i][k]) r[i] |= r[k];`.
- **Minimax / bottleneck paths:** replace the update with `d[i][j] = min(d[i][j], max(d[i][k], d[k][j]))`.

## Pitfalls
- Skip `INF` entries before adding (the file does), otherwise values overflow.
- Path reconstruction is not reliable when negative cycles exist.
- `add_edge` keeps the **minimum** weight for parallel edges.
- Do not use it when `n` is large. Run Dijkstra from the nodes you actually need.
