# DP Optimizations: Divide & Conquer and Knuth

**File:** `dp_optimizations.cpp`

## What it does
Two techniques that make a **correct but slow** DP fast:
- `dc_optimization`: layered DP `dp[j][i] = min_p dp[j-1][p] + cost(p, i)`, in O(k * n log n) instead of O(k * n^2).
- `knuth_optimization`: interval DP, in O(n^2) instead of O(n^3).

## Use it when
- You already have a correct O(k n^2) or O(n^3) DP, the limits are too big, and the transition has a **monotone optimal split point**.
- Typical: "split an array into `k` groups minimizing a cost" (D&C), "merge adjacent piles / optimal binary search tree" (Knuth).

## Divide & conquer optimization
Let `opt(i)` be the best split point `p` for `i`. If `opt(i) <= opt(i+1)` (monotone), compute `opt(mid)` by scanning its allowed range, then recurse: the left half only looks at `p <= opt(mid)`, the right half at `p >= opt(mid)`. Each recursion level scans O(n) total, so a layer costs O(n log n).

**Condition (sufficient):** `cost(a, c) + cost(b, d) <= cost(a, d) + cost(b, c)` for `a <= b <= c <= d` (the quadrangle inequality). Costs like (sum of a segment)^2 satisfy it.

## Knuth optimization
For `dp[i][j] = min_{i<=m<j} dp[i][m] + dp[m+1][j] + cost(i, j)`, the optimum satisfies `opt[i][j-1] <= opt[i][j] <= opt[i+1][j]`. Scanning only that range totals O(n^2).

**Condition:** `cost` satisfies the quadrangle inequality and is monotone on nested intervals (`cost(b, c) <= cost(a, d)` for `a <= b <= c <= d`). A positive segment sum works.

## Complexity
| Technique   | Before          | After           |
|-------------|-----------------|-----------------|
| D&C         | O(k * n^2)      | O(k * n log n)  |
| Knuth       | O(n^3)          | O(n^2)          |

## How to be sure it is allowed
1. Prove the quadrangle inequality, **or**
2. Write the slow DP and the fast DP, then **stress test** them on random small inputs (see `utilities/stress/`). Almost every wrong application shows up within a few hundred tests.

## Related techniques
- **Convex hull trick / Li Chao:** when the cost splits into line-like terms (`convex_hull_trick`).
- **Monotone queue (sliding window) DP:** `dp[i] = min over j in [i-w, i)`, use a deque (see `utilities/array_utils.cpp`).
- **Aliens trick (Lagrangian relaxation):** removes the layer count `k` when the answer is convex in `k`.

## Pitfalls
- A wrong assumption does **not** crash. It just returns a slightly wrong answer.
- `dc_optimization` needs `k <= n` (every group non-empty).
- The cost function is called O(n log n) times per layer: make it O(1) (prefix sums).
- Keep `INF` safe from overflow; layer 1 is handled directly as `cost(0, i)`.
- Knuth needs `opt[i][i] = i` as the base and fills by increasing length.
