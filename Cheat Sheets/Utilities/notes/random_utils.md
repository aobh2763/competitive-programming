# Random Utilities

**File:** `random_utils.cpp`

## What it does
- `rng` / `rnd(l, r)`: a good random number generator (`mt19937_64`) and an inclusive random integer.
- `rand_array`, `rand_perm`, `rand_string`: random test data.
- `rand_tree(n, shape)`: random tree as an edge list (random, path, star, deep, binary-ish).
- `rand_connected_graph(n, m)`: simple connected graph.
- `custom_hash`: a hash for `unordered_map` / `unordered_set` that anti-hash tests cannot break.

## Use it when
- You write a generator (`gen.cpp`) for a stress test.
- You use `unordered_map` on a judge with hacks (Codeforces): the default hash can be attacked and made O(n) per operation.
- A randomized algorithm needs good random numbers (random pivots, hashing, Pollard rho).

## Why `mt19937_64`, not `rand()`
`rand()` is low quality, often limited to 32767 on Windows, and `rand() % n` is biased. `mt19937_64` plus `uniform_int_distribution` is uniform and fast.

## Test-shape advice
Different tree shapes break different solutions:
| Shape   | Catches                                            |
|---------|----------------------------------------------------|
| path    | Recursion depth, O(n) depth assumptions            |
| star    | O(deg^2) loops, one huge adjacency list            |
| random  | General correctness                                |
| deep    | Long chains with small branches (HLD, LCA)         |

## Usage
```
unordered_map<long long, int, custom_hash> mp;
ll x = rnd(1, 100);
auto edges = rand_tree(10, 1);                  // path on 10 nodes
auto g = rand_connected_graph(8, 12);
```

## Pitfalls
- `rng` is seeded from the clock, so tests are **not reproducible**. In a generator, seed with `argv[1]` (see `stress/gen.cpp`), so a failing test number can be rerun.
- `rnd(l, r)` requires `l <= r`.
- `rand_connected_graph` needs `n - 1 <= m <= n(n-1)/2` or it loops forever.
- Nodes are labelled `1..n`. Subtract 1 for 0-indexed solutions.
- `custom_hash` takes `unsigned long long`: ints are converted automatically, but for `pair` keys you need a pair hash (combine two `splitmix64` calls).
