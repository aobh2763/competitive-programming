# Dynamic Programming Cheat Sheet

Each `.cpp` file has a matching `.md` with the "when and why". Start with `basic_dp` and `knapsack`.

## What is dynamic programming?
Break a problem into **smaller versions of itself**, solve each small version **once**, store the answer, and build bigger answers from stored ones. It beats brute force when the same sub-problem would otherwise be solved over and over.

## The 5-step recipe (use it every time)
1. **State:** what do the indices of `dp[...]` mean? ("`dp[i]` = best answer for the first `i` items")
2. **Transition:** how does `dp[state]` come from smaller states?
3. **Base cases:** the smallest states you can answer directly.
4. **Order:** compute states so dependencies are ready (increasing `i`, increasing length, increasing mask...).
5. **Answer:** which state(s) hold the final answer?

Two ways to write it: **bottom-up** (loops, usually faster) or **top-down** (recursion + memoization, easier to write when the order is awkward, as in digit DP).

## Which DP is this?

| Problem looks like...                                                       | Use                      | File |
|-----------------------------------------------------------------------------|--------------------------|------|
| Count ways / min cost along a line or grid, "step i depends on step i-1..." | 1D / grid DP             | `basic_dp` |
| Choose items under a weight/budget limit; make an amount from coins         | Knapsack                 | `knapsack` |
| Two strings/arrays: common subsequence, edit distance, palindromes, LIS     | Sequence DP              | `sequence_dp` |
| "Merge/split a segment" where the answer for [i, j] uses smaller segments   | Interval DP              | `interval_dp` |
| n <= 20 items, state = which items are used (visit all cities, assign jobs) | Bitmask DP               | `bitmask_dp` |
| "How many numbers up to N have property P?" (property of the digits)        | Digit DP                 | `digit_dp` |
| Tree: best choice per subtree, distances from every node                    | Tree DP + rerooting      | `tree_dp` |
| `dp[i] = min_j (dp[j] + line in terms of i)`, n up to 1e5                   | Li Chao / convex hull    | `convex_hull_trick` |
| Layered/interval DP is correct but too slow (O(k n^2), O(n^3))              | D&C or Knuth optimization| `dp_optimizations` |

## DP vs greedy vs brute force
- **Greedy** works when a local best choice is always safe (provable). If you can find a counterexample, use DP.
- **DP** works when the problem has **optimal substructure** (best answer built from best sub-answers) and **overlapping subproblems**.
- **Brute force over subsets** is the fallback when n <= 20 (that is bitmask DP).

## Estimating complexity
Number of states x work per transition. 1e8 simple operations per second is a safe guess.

| States                     | Typical limit                     |
|----------------------------|-----------------------------------|
| `dp[n]`                    | n up to 1e7                       |
| `dp[n][m]`                 | n, m up to ~5,000 (25M cells)     |
| `dp[n][W]` (knapsack)      | n * W up to ~1e7 - 1e8            |
| `dp[2^n][n]`               | n up to ~16 - 20                  |
| interval `dp[n][n]` + split| n up to ~400 (O(n^3)); 5,000 with Knuth |

## Pitfalls that apply to everything here

- **Initial values:** use `INF` (not 0) for "minimum" tables and `-INF` or 0 deliberately for "maximum". Do not add to INF without checking (`INF + x` overflows if INF is too big; these files use `LLONG_MAX / 4`).
- **Loop order matters:** 0/1 knapsack goes downward, unbounded goes upward, coin combinations versus sequences differ only by loop nesting.
- **Overflow:** counts explode. Use `long long` and take `% MOD` after every addition or multiplication.
- **Memory:** a `dp[5000][5000]` of `long long` is 200 MB. Use `int`, or keep only the previous row (rolling array) when you only need the last layer.
- **Reconstruction:** to print the actual choices, store where each state came from (a parent pointer, or recompute by walking backwards).
- **Off-by-one on the state:** decide whether `dp[i]` means "first i items" (size n+1, empty prefix = base case) or "item i" (size n), and stay consistent.
- **Verify with brute force:** DP bugs are subtle. Use the stress-testing setup in `utilities/stress/`.
