# Binary Search & Ternary Search

**File:** `binary_search.cpp`

## What it does
- `first_true(lo, hi, pred)`: smallest `x` with `pred(x)` true, for a monotone predicate `F F F T T T`.
- `last_true(lo, hi, pred)`: largest `x` with `pred(x)` true, for `T T T F F F`.
- `bisect_real`: the same on real numbers, with a fixed number of iterations.
- `ternary_int`, `ternary_real`: minimum of a unimodal function.

## Use it when
- The answer is a number and "is `x` big enough?" is easy to check (**binary search on the answer**): minimize the largest group, maximize the minimum distance, smallest time to finish all work.
- You search in a sorted array (also see `lower_bound` / `upper_bound`).
- You optimize a function that goes down then up (convex), like a cost vs position.

## Complexity
O(log(hi - lo)) calls to `pred`. Total cost = that times the cost of `pred`.

## How to design `pred`
1. Phrase the question as "is value `x` **feasible**?".
2. Check that feasibility is **monotone**: if `x` works then every larger (or every smaller) value works.
3. Write `pred(x)` as a greedy or simulation in O(n).

Example: "minimum time so that `k` workers finish all tasks":
```
ll ans = first_true(1, 1e18, [&](ll t) { return workers_needed(t) <= k; });
```

## STL equivalents
```
lower_bound(a.begin(), a.end(), x)   // first element >= x
upper_bound(a.begin(), a.end(), x)   // first element >  x
count of x in sorted a = upper_bound - lower_bound
```

## Pitfalls
- The midpoint is computed as `l + (r - l) / 2` to avoid overflow.
- The helpers return `hi + 1` (first_true) or `lo - 1` (last_true) when nothing satisfies `pred`. Check for that.
- A non-monotone `pred` makes binary search silently return garbage.
- For doubles, use a fixed iteration count (100). `while (hi - lo > eps)` can loop forever at large magnitudes.
- Ternary search needs a **strictly** unimodal function. Plateaus (flat regions) break it. For integers with plateaus, use binary search on `f(x+1) - f(x)`.
- Set `hi` high enough: answers up to 1e18 need `hi = 1e18`, and `pred` must not overflow at that value.
