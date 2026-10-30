# Interval DP

**File:** `interval_dp.cpp`

## What it does
Solves problems where the state is a **segment** `[i, j]`: `matrix_chain`, `merge_piles` (merge adjacent piles), `min_palindrome_cuts` and `burst_balloons`.

## Use it when
- "Merge/split/remove elements of a segment, and the order matters."
- The best answer for `[i, j]` comes from splitting it into `[i, k]` and `[k+1, j]`.
- Constraints are small (n up to ~400-500), because the cost is O(n^3).

## The idea
Compute segments by increasing **length**, so every shorter segment is ready:
```
for len = 2..n:
  for i = 0 .. n-len:
    j = i + len - 1
    dp[i][j] = best over split k of (dp[i][k] + dp[k+1][j] + cost(i, j))
```

## Choosing the split
| Problem            | What the split means                                                     |
|--------------------|--------------------------------------------------------------------------|
| Matrix chain       | the **last multiplication** happens between `k` and `k+1`                 |
| Merge piles        | the **last merge** joins `[i, k]` and `[k+1, j]`                          |
| Burst balloons     | `k` is the **last balloon burst** in the open interval (that trick makes the two sides independent) |
| Palindrome cuts    | the last piece is `s[i..j]` (needs a palindrome table)                    |

## Complexity
O(n^3) time, O(n^2) memory (palindrome cuts is O(n^2)). For merge-type costs, Knuth optimization (see `dp_optimizations`) reduces it to O(n^2).

## Pitfalls
- Think **"last operation"** (what happens last in the segment), not the first. It is what splits the problem into independent parts.
- `merge_piles` only allows merging **adjacent** piles. If any two piles may merge, a min-heap greedy solves it (Huffman).
- `burst_balloons` pads the array with 1s at both ends, and works on the interval strictly between `i` and `j`.
- Circular versions: duplicate the array (length `2n`) and take the best window of length `n`.
- Keep `INF` small enough that `INF + cost` does not overflow.
