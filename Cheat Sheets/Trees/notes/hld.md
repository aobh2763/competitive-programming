# Heavy-Light Decomposition

**File:** `hld.cpp`

## What it does
Splits a tree into **chains** so that any root-to-node path crosses at most O(log n) chains. Each chain is a contiguous range in a position array, so a segment tree can answer **path queries and updates**.

## Use it when
- "Update the value of a node, query the sum / max on the path u-v".
- "Query the subtree of v" and path queries in the same problem.
- Binary lifting cannot handle it because values **change**.

## Complexity
| Operation        | Time        |
|------------------|-------------|
| `build`          | O(n)        |
| `query_path`     | O(log^2 n)  |
| `query_subtree`  | O(log n)    |
| `lca`            | O(log n)    |
| Memory           | O(n)        |

## How it works
1. Compute subtree sizes. The **heavy child** of a node is its largest-subtree child.
2. Heavy edges form chains. Number nodes so that each chain is contiguous, with the heavy child **right after** its parent. That also makes every subtree contiguous: `[pos[v], pos[v] + sz[v])`.
3. A path query jumps from the deeper chain head to its parent, repeating until both nodes share a chain, then takes one last range.

## Edge weights instead of node values
Store each edge's weight on its **child** node. For a path `u-v`, query the path **excluding the LCA node**:
- Run the same loop but, at the final step, use `pos[u] + 1` as the left end (skip the LCA).

## Extensions
- **Path update:** replace the segment tree with a lazy one and do range updates in the same chain loop.
- **Max instead of sum:** change the combine in the segment tree and the `res +=` lines.
- **Non-commutative ops** (e.g. ordered concatenation): you must keep track of which side each chain segment belongs to (left half from `u`, right half from `v`).

## Pitfalls
- It is more code than anything else here. Prefer binary lifting if there are no updates.
- The loop must always lift the chain whose **head is deeper**, not the node that is deeper.
- Reset all vectors between tests (`build` reassigns them, but `adj` must be cleared by you).
- Make sure to call `build` after all `add_edge` calls.
- If you need both `val` and updates, `build(root, val)` loads initial values; otherwise they start at 0.
