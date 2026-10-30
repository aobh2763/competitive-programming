# Knapsack Family & Coin Change

**File:** `knapsack.cpp`

## What it does
- `knapsack01`: each item used at most once, maximize value under a weight limit. `knapsack01_items` also returns which items.
- `knapsack_unbounded`: unlimited copies of each item.
- `knapsack_bounded`: item `i` has `cnt[i]` copies (binary splitting).
- `min_coins`: fewest coins to reach an amount.
- `count_combinations` / `count_sequences`: ways to make an amount (order ignored vs order counted).
- `subset_sums`: which totals are reachable, with a bitset.

## Use it when
- "Pick items, limited capacity/budget, maximize value."
- "Can we choose some numbers that sum exactly to `S`?" (subset sum, equal partition).
- "Fewest coins", "number of ways to make change".

## The key trick: loop direction
All of them use one array `dp[capacity]`.
| Variant        | Capacity loop                | Why                                           |
|----------------|------------------------------|-----------------------------------------------|
| 0/1 knapsack   | **downward** `W ... w[i]`    | `dp[c - w]` still holds the "before this item" value, so an item is used at most once |
| Unbounded      | **upward** `w[i] ... W`      | `dp[c - w]` may already include this item, so it can be reused |

## Coin change: combinations vs sequences
| Question                              | Loop nesting                         |
|---------------------------------------|--------------------------------------|
| Combinations (1+2 = 2+1, one way)     | coins **outer**, amount inner        |
| Sequences (1+2 and 2+1 differ)        | amount **outer**, coins inner        |

## Complexity
| Problem             | Time              | Memory |
|---------------------|-------------------|--------|
| 0/1, unbounded      | O(n * W)          | O(W)   |
| Reconstruct items   | O(n * W)          | O(n * W) |
| Bounded             | O(n * log(cnt) * W)| O(W)  |
| Subset sum bitset   | O(n * S / 64)     | O(S / 64) |

## Tricks
- **Exact weight instead of "at most":** initialize `dp[0] = 0` and everything else `-INF`.
- **Huge weights, small values:** swap the roles: `dp[value]` = minimum weight to reach that value.
- **Equal-sum partition:** total sum must be even; check subset sum for `total / 2`.
- **Multiple constraints (weight and volume):** use a 2D `dp[w][v]` (loop both downward).
- **Large W (up to 1e9) but few items:** meet in the middle, or switch the DP dimension.

## Pitfalls
- Using the unbounded loop direction for 0/1 items silently reuses items.
- `min_coins` returns `-1` for impossible, not 0.
- The reconstruction table costs O(n * W) memory, so use it only when the sizes allow.
- `subset_sums<N>` needs `N` larger than the total sum, and `N` is a compile-time constant.
- Counting with big amounts: remember the modulus.
