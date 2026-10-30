# Bellman-Ford

**File:** `bellman_ford.cpp`

## What it does
Single-source shortest paths that work with **negative edge weights**, and detect **negative cycles**.

## Use it when
- Any edge may have negative weight.
- The problem asks "is there a negative cycle / arbitrage / profit loop?"
- "Is the distance unbounded (can be made arbitrarily small)?" The nodes marked `-INF` are exactly those.
- Constraints are small enough: `n * m` up to about 1e7.

## Complexity
O(n * m). Memory O(n + m).

## How it works
Relax every edge `n - 1` times. Any shortest path has at most `n - 1` edges, so that is enough when there is no negative cycle. If something still relaxes on the n-th pass, a negative cycle exists. Running extra rounds spreads the `-INF` mark to every node reachable from a negative cycle.

## Return values of `run`
| Value in `dist` | Meaning                                              |
|-----------------|------------------------------------------------------|
| finite number   | normal shortest distance                             |
| `INF`           | unreachable from src                                 |
| `-INF`          | reachable, but a negative cycle makes it unbounded   |

The function returns `true` iff a negative cycle is reachable from `src`.

## Tricks
- **Negative cycle anywhere (not just from src):** set all `dist = 0` initially (a virtual source connected to all nodes with weight 0) and check whether the n-th round still relaxes.
- **Difference constraints:** `x_v - x_u <= w` becomes edge `u -> v` with weight `w`. A feasible system exists iff there is no negative cycle.
- **SPFA** (queue-based Bellman-Ford) is often faster in practice but has an O(n * m) worst case that adversarial tests can hit. Prefer plain Bellman-Ford on judges.

## Pitfalls
- An **undirected** negative edge is itself a negative cycle (go back and forth).
- Do not run Dijkstra when negative edges exist, even a single one.
- The early `return false` after a round with no change is what keeps this fast on normal inputs.
- `-INF` means "unbounded", not an actual number. Don't print it as an answer.
