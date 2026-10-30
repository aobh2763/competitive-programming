# Bitmask DP

**File:** `bitmask_dp.cpp`

## What it does
Uses an integer as a **set** (bit `i` = "item `i` is used/visited") to run DP over all subsets. Includes `tsp` (Held-Karp), `assignment`, `count_hamiltonian_paths` and `min_bins` (bin packing).

## Use it when
- `n <= 20` (about 16 if the transition costs another factor of `n`).
- "Visit every city once", "assign each worker one job", "split items into the fewest groups".
- The order you pick items in matters less than **which** items are already picked.

## Complexity
| Problem                  | Time             | Memory       |
|--------------------------|------------------|--------------|
| `tsp`                    | O(2^n * n^2)     | O(2^n * n)   |
| `assignment`             | O(2^n * n)       | O(2^n)       |
| `count_hamiltonian_paths`| O(2^n * n^2)     | O(2^n * n)   |
| `min_bins`               | O(2^n * n)       | O(2^n)       |

2^20 is about 1 million masks, which is fine. 2^20 * 20 states of `long long` is 160 MB, so check memory.

## The patterns
- **State:** `dp[mask]` or `dp[mask][last]`.
- **Transition:** add one item `u` not in `mask`: `dp[mask | 1 << u] = best(dp[mask] + cost)`.
- **Order:** increasing `mask` works, because `mask | bit` is always bigger than `mask`.
- **Counting the item index:** in assignment, `popcount(mask)` tells you which worker is next.

## Tricks
- **Submask DP** (partition a set into groups): `for (sub = mask; sub; sub = (sub-1) & mask)`. Total cost O(3^n). See `bit_tricks`.
- **SOS DP** for sums over subsets: see `utilities/bit_tricks.cpp`.
- **TSP path instead of cycle:** take the best end node without adding the return edge.
- **Fix the start node** (here node 0) to avoid counting rotations.
- **Broken-profile DP** (tilings) is bitmask DP over a row of a grid.

## Pitfalls
- `1 << n` is an `int`. Use `1LL << n` when `n >= 31` (you will not reach that here, but masks of 40+ bits appear in meet-in-the-middle).
- Skip unreachable states (`INF`) before transitioning, or `INF + cost` can overflow.
- `tsp` expects a complete graph. Use a large `INF` weight for missing edges and check for `INF` in the result.
- `assignment` is O(2^n * n). For n up to ~200 use the Hungarian algorithm.
- Memory is the usual limit. Use `int` where possible.
