# Basic DP: 1D and Grid Problems

**File:** `basic_dp.cpp`

## What it does
Starter DP problems that show the whole recipe: `climb_stairs` (counting ways), `max_sum_no_adjacent` (house robber), `min_path_sum` (cheapest grid path), `count_paths` (grid paths with obstacles) and `largest_square` (biggest all-ones square).

## Use it when
- The answer for position `i` depends on a few earlier positions (`i-1`, `i-2`, ...).
- You move through a grid right/down and want a count or a minimum.
- A choice at one step restricts the next one ("cannot take two adjacent").

## The idea in one example
**Climbing stairs:** to stand on step `i` you came from `i-1` or `i-2`, so `dp[i] = dp[i-1] + dp[i-2]` (Fibonacci). Base: `dp[0] = 1`. Answer: `dp[n]`.

## Common 1D / grid patterns
| Pattern                            | Transition                                         |
|------------------------------------|----------------------------------------------------|
| Count ways to reach `i`            | `dp[i] = sum of dp[i - step]`                      |
| Min cost to reach `i`              | `dp[i] = min(dp[i - step] + cost)`                 |
| Skip-adjacent selection            | `take = skip_prev + a[i]`, `skip = max(skip_prev, take_prev)` |
| Grid right/down count              | `dp[i][j] = dp[i-1][j] + dp[i][j-1]` (0 on walls)  |
| Grid right/down min cost           | `dp[i][j] = g[i][j] + min(dp[i-1][j], dp[i][j-1])` |
| Largest square                     | `dp[i][j] = 1 + min(up, left, up-left)` if the cell is `1` |

## Complexity
O(n) for 1D, O(R * C) for grids. Memory can be reduced to O(C) (keep only the previous row) or O(1) for the 1D recurrences.

## Pitfalls
- Check the first row and column separately (no `i-1` or `j-1`).
- For "count paths", a blocked start cell means 0 paths.
- `max_sum_no_adjacent` allows taking nothing, so the answer is at least 0 even if all numbers are negative. Change that if the problem forces at least one element.
- Counting problems usually ask for the answer modulo 1e9+7. Reduce after every addition.
- If moves can go in all four directions (not only right/down), plain DP over cells does not work (use BFS/Dijkstra).
