# Sparse Table

**File:** `sparse_table.cpp`

## What it does
Answers range min / max / gcd queries on a **static array** in **O(1)** after an O(n log n) build.

## Use it when
- The array never changes and there are many queries (up to ~1e6).
- The op is **idempotent**: `op(x, x) == x`. That means min, max, gcd, bitwise and/or.
- You need the fastest possible queries (for example as the backend of an O(1) LCA).

## Why O(1)
For `[l, r]`, pick `j = floor(log2(length))` and combine two blocks of size 2^j: one starting at `l`, one ending at `r`. They overlap, which is harmless for idempotent ops.

## Complexity
| Operation | Time       |
|-----------|------------|
| build     | O(n log n) |
| query     | O(1)       |
| Memory    | O(n log n) |

## Don't use it for
- **Sum or xor:** the overlap would count elements twice. Use prefix sums (or prefix xors).
- **Arrays with updates:** use a segment tree.

## Tricks
- **Argmin (index of the minimum):** store pairs `(value, index)`, and `min` on pairs works directly.
- **O(1) LCA:** run it over the Euler tour of depths and return the node with minimum depth in the range between two first occurrences.

## Pitfalls
- `query(l, r)` is **inclusive** and requires `l <= r`.
- Memory: n = 1e6 gives 20 levels, so 20M elements (about 80 MB for ints). Too much for some judges.
- Change the body of `op()` to switch the operation; do not assume it is min everywhere.
