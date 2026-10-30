# Graph Traversal (BFS, Components, Bipartite, Grid)

**File:** `graph_traversal.cpp`

## What it does
- `bfs`: shortest distance (in edges) from a source to every node, plus optional parent array.
- `path`: rebuilds the actual path from the parent array.
- `components`: labels connected components.
- `bipartite`: 2-colours the graph or reports an odd cycle.
- `grid_bfs`: BFS on a character grid.

## Use it when
- "Minimum number of moves / steps / edges" and every move costs the same.
- Maze, grid, or knight-move problems (model each cell or state as a node).
- "How many groups / islands / components?"
- "Can we split people into two teams so enemies are on opposite sides?" (bipartite)
- Any "is this graph connected?" question.

## Complexity
O(n + m) for the graph functions, O(R * C) for the grid.

## Tricks
- **Multi-source BFS:** push all sources into the queue at distance 0 (for "distance to the nearest X" for every cell).
- **State-space BFS:** a node can be a tuple like `(position, keys_held)` or `(r, c, direction)`. Encode it as one integer.
- **Reconstruct a path:** keep `par`, then walk back from the target.
- **BFS order = nondecreasing distance**, which is why it is correct only with equal weights.

## Bipartite check
A graph is bipartite iff it has **no odd cycle**. BFS alternates colours, and an edge between two same-coloured nodes proves an odd cycle.

## Pitfalls
- BFS gives shortest paths only for **unweighted** graphs. For weights use Dijkstra.
- Mark nodes visited **when pushing** to the queue, not when popping, or the queue can blow up.
- Edges are undirected by default in `add_edge`.
- `components()` is for undirected graphs. For directed graphs use SCC.
- Grid input: confirm which characters are walls (`#` here) and how many directions are allowed (4 or 8).
