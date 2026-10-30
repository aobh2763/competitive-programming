# LCA (Binary Lifting)

**File:** `lca.cpp`

## What it does
Answers "lowest common ancestor of u and v" in O(log n) after O(n log n) preprocessing. Also gives k-th ancestor and distance.

## Use it when
- "Distance between two nodes" -> `dist(u, v)`.
- "Is node x on the path from u to v?" -> `dist(u,x) + dist(x,v) == dist(u,v)`.
- "Jump k steps up from v" -> `kth_ancestor`.
- Path queries that are **not** updated (see the extension below).

## Complexity
| Operation        | Time        |
|------------------|-------------|
| `build`          | O(n log n)  |
| `lca`            | O(log n)    |
| `kth_ancestor`   | O(log n)    |
| `dist`           | O(log n)    |
| Memory           | O(n log n)  |

For n = 2e5, `LOG` is 18, so the table holds about 3.6M ints (roughly 14 MB).

## How it works
`up[j][v]` is the 2^j-th ancestor of v. To find the LCA, if neither node is an ancestor of the other, lift `u` as high as possible while its ancestor is **not** an ancestor of `v`; the parent of where it stops is the LCA.

## Extension: path aggregates
Store a second table `mx[j][v]` = max edge weight on the 2^j jump. While lifting in `lca`, fold the maximum from each jump. This gives "max edge on path u-v" for static weights (classic: MST path queries).

## Alternatives
| Method                      | Preprocess | Query    | Notes                                 |
|-----------------------------|-----------:|---------:|---------------------------------------|
| Binary lifting (this file)  | n log n    | log n    | Simplest, supports k-th ancestor       |
| Euler tour + sparse table   | n log n    | **O(1)** | Best when you have many LCA queries    |
| HLD                         | n          | log n    | O(n) memory, also does path updates    |

## Pitfalls
- The root's ancestors are set to the root itself, so over-lifting stays at the root rather than going to -1.
- Call `build(root)` after **all** `add_edge` calls.
- 0-indexed. Nodes in the input may be 1-indexed.
- Reset the structure per test case.
