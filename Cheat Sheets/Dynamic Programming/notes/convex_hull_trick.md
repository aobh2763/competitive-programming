# Convex Hull Trick (Li Chao Tree)

**File:** `convex_hull_trick.cpp`

## What it does
Stores many lines `y = m*x + b`, accepts new lines in **any order**, and answers "what is the **minimum** value at `x`?" quickly. Also includes `split_cost_dp`, a full example DP.

## Use it when
A DP transition looks like
```
dp[i] = min over j < i of ( dp[j] + cost(j, i) )
```
and `cost(j, i)` can be expanded into **(something with only j) + (something with only i) + (j-part) * (i-part)**. Then each `j` is a line and each `i` is a query point.

## Worked example
`dp[i] = min_j dp[j] + (x_i - x_j)^2 + C`
Expand: `dp[j] + x_j^2 - 2*x_j*x_i + x_i^2 + C`
- line for `j`: slope `-2*x_j`, intercept `dp[j] + x_j^2`
- query at `x_i`, then add `x_i^2 + C`.

This turns O(n^2) into O(n log range).

## Complexity
| Operation  | Time                |
|------------|---------------------|
| `add_line` | O(log(hi - lo))     |
| `query`    | O(log(hi - lo))     |
| Memory     | O(number of lines)  |

## Li Chao vs the classic monotone hull
| Method                          | Needs                               | Speed        |
|---------------------------------|-------------------------------------|--------------|
| Li Chao tree (this file)        | integer query range                 | O(log) each  |
| Monotone deque hull             | slopes sorted and queries monotone  | O(1) amortized |
Li Chao is slower by a log factor but has no ordering requirement, so it is the safe default.

## Tricks
- **Maximum:** insert the negated lines `(-m, -b)` and negate the answer.
- **Huge x range:** works for `x` up to about 1e9 and beyond, as long as `m * x + b` fits in 64 bits.
- **Query only on a segment of the time axis:** use a Li Chao tree on a segment tree (add a line to a range of positions), a more advanced use.

## Pitfalls
- Values must stay below about 4e18. Check `|m * x| + |b|`.
- Queries must lie in `[lo, hi]` given at construction.
- Equal slopes are fine, the better intercept wins.
- If the cost cannot be split as described, this trick does not apply.
