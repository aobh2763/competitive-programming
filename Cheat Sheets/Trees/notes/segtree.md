# Iterative Segment Tree

**File:** `segtree.cpp`

## What it does
Point update and range query for **any associative operation**: sum, min, max, gcd, xor, matrix product, "merge two nodes of a custom struct".

## Use it when
- "Update one element, query min/max/gcd of a range".
- The operation is not invertible (so Fenwick cannot do it).
- You can describe the answer for a segment as a combination of two halves.

## Complexity
| Operation | Time     |
|-----------|----------|
| `build`   | O(n)     |
| `set`     | O(log n) |
| `query`   | O(log n) |
| Memory    | O(2n)    |

## How to plug in an operation
You only need two things: the **op** (associative) and its **identity**.

| Goal   | identity          | op                       |
|--------|-------------------|--------------------------|
| sum    | `0`               | `a + b`                  |
| min    | `INF`             | `min(a, b)`              |
| max    | `-INF`            | `max(a, b)`              |
| gcd    | `0`               | `__gcd(a, b)`            |
| xor    | `0`               | `a ^ b`                  |

For a custom node (e.g. max subarray sum), make a struct with `sum, prefix, suffix, best` and write the merge function. Order matters there, and this implementation preserves it.

## Pitfalls
- Queries are **half-open `[l, r)`**. For an inclusive range `[l, r]` call `query(l, r+1)`.
- `set` **replaces**; it does not add. For "a[i] += v", keep your own array and call `set(i, a[i] += v)`.
- Pick an identity that cannot win: `INF` must be larger than any real value, and keep it small enough not to overflow when combined.
- Not suitable for range updates. Use the lazy tree.
- This version cannot "descend" (e.g. find first index with value >= x). For that, use a recursive tree.
