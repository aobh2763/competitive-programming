# Bridges and Articulation Points

**File:** `bridges.cpp`

## What it does
Finds, in an **undirected** graph:
- **Bridges:** edges whose removal disconnects their component.
- **Articulation points (cut vertices):** vertices whose removal disconnects their component.

## Use it when
- "Which roads are critical? / Which single link failure splits the network?"
- "Minimum number of edges to add so the graph has no bridges."
- Building the **bridge tree**: contract every 2-edge-connected component, and the result is a tree (then use LCA, diameter, etc.).

## Complexity
O(n + m).

## The idea: low-link values
`tin[v]` is the DFS discovery time. `low[v]` is the earliest discovery time reachable from `v`'s DFS subtree using at most one back edge.

| Condition                    | Meaning                                         |
|------------------------------|-------------------------------------------------|
| `low[child] > tin[parent]`   | edge `parent - child` is a **bridge**            |
| `low[child] >= tin[parent]`  | `parent` is an **articulation point** (non-root) |
| root with >= 2 DFS children  | the root is an articulation point               |

The root is a special case because it has no ancestors to fall back on.

## Multi-edges
The code skips the **edge id** you arrived by, not the parent vertex. That makes two parallel edges between `u` and `v` correctly **not** bridges.

## Tricks
- **2-edge-connected components:** remove the bridges and take connected components (e.g. with `components()` from `graph_traversal.cpp`).
- **Bridge tree:** one node per component, one edge per bridge. It is a tree, so many hard path problems become easy.
- **Biconnected components (blocks)** need an extra stack of edges; that is a separate algorithm.

## Pitfalls
- Undirected graphs only. For directed graphs think SCC / dominators.
- Disconnected graphs are handled (it starts a DFS from every unvisited node).
- Edge ids come from `add_edge` call order, so output ids refer to your input order (0-indexed).
- A bridge's two endpoints are not necessarily articulation points when the endpoint has degree 1.
