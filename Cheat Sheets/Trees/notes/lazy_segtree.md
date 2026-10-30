# Lazy Segment Tree

**File:** `lazy_segtree.cpp`

## What it does
**Range update + range query** in O(log n). The provided version does range add and range sum.

## Use it when
- "Add v to every element in [l, r], then ask for the sum / max of [a, b]".
- "Set every element in [l, r] to x" (needs the assign variant below).
- Anything where one update touches many elements and you cannot afford O(n) per update.

## Complexity
| Operation | Time     |
|-----------|----------|
| `build`   | O(n)     |
| `update`  | O(log n) |
| `query`   | O(log n) |
| Memory    | O(4n)    |

## The idea
Each node stores its answer plus a **pending tag** that has been applied to the node but not yet to its children. Before going down into children you `push` the tag; after coming back you `pull` to recompute.

Three functions define the whole behavior, change these to adapt it:
- `apply(x, l, r, v)`: how a tag changes the node's stored answer and tag.
- `push(x, l, r)`: send the tag to children.
- `pull(x)`: combine children into the parent.

## Common variants
| Update / Query      | Change                                                                      |
|---------------------|------------------------------------------------------------------------------|
| add / **max**       | `pull` uses `max`; `apply` does `mx[x] += v` (no multiplication by length)    |
| **assign** / sum    | tag = (has_assign, value); `apply` sets `sum = v*len`; assign overrides add   |
| add + assign        | assign clears the add tag; add on top of assign adds to the assigned value     |

## Pitfalls
- Ranges are **inclusive** `[l, r]` here (unlike `segtree.cpp`).
- Always `push` before recursing into children, or you read stale values.
- Use `long long`: `v * (r - l + 1)` overflows int fast.
- Size is `4n`; with n = 2e5 that is fine, but for several trees watch memory.
- For assign, a tag value of `0` is a valid assignment, so use a separate flag (or a sentinel like `LLONG_MIN`).
- If you only need range add with **point** query, a Fenwick is far simpler.
