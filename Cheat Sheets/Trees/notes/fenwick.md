# Fenwick Tree (BIT)

**File:** `fenwick.cpp`

## What it does
Maintains an array under **point updates** and **prefix sums**. Range sum = `sum(r) - sum(l-1)`.

## Use it when
- You see "update one element, query the sum of a range".
- Counting inversions: iterate left to right, `add(a[i], 1)`, and count how many earlier elements are greater via `sum(a[i]+1, max)`.
- You need the k-th smallest in a dynamic multiset (`lower_bound` on counts).

## Complexity
| Operation        | Time     |
|------------------|----------|
| `add`            | O(log n) |
| `sum`            | O(log n) |
| `lower_bound`    | O(log n) |
| Memory           | O(n)     |

## Tricks
- **Range add, point query:** `add(l, v)`, `add(r+1, -v)`; the value at `i` is `sum(i)`.
- **Range add, range sum:** use two BITs. With `B1` and `B2`, for a range add of `v` on `[l, r]`: `B1.add(l, v)`, `B1.add(r+1, -v)`, `B2.add(l, v*l)`, `B2.add(r+1, -v*(r+1))`. Then `prefix(i) = (i+1)*B1.sum(i) - B2.sum(i)`.
- **Large values:** coordinate-compress first (sort, unique, `lower_bound`).
- **2D BIT:** nest two loops over the same `i & -i` pattern.

## Pitfalls
- It is **1-indexed**. `add(0, v)` loops forever.
- Only works for invertible ops (sum, xor). **No range min/max**, use a segment tree.
- `lower_bound` needs non-negative values.
- Use `Fenwick<long long>` when sums can exceed 2^31.

## vs segment tree
Fenwick is shorter, faster, and uses less memory, but only supports sum-like ops. If the problem needs min/max or range updates with range queries, go to a segment tree.
