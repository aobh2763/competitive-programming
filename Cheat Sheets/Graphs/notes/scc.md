# Strongly Connected Components (Tarjan)

**File:** `scc.cpp`

## What it does
Groups the nodes of a **directed** graph into strongly connected components: sets of nodes where each can reach every other. Collapsing each component to a single node gives a **DAG** (the condensation).

## Use it when
- "Which nodes are mutually reachable?"
- "Minimum number of edges to add so everything is strongly connected."
- Directed graph with cycles where you want to run DP anyway: condense first, then DP on the DAG.
- **2-SAT:** variables are nodes `x` and `not x`; the formula is satisfiable iff no variable shares an SCC with its negation.
- "Count nodes reachable from v", "which nodes can reach everything?" (look at the source and sink SCCs).

## Complexity
O(n + m).

## Component order
Tarjan finishes **sinks first**. So `comp` ids are in reverse topological order: every edge between different components goes from a **higher** id to a **lower** id.
- Iterate ids from high to low for a source-to-sink pass.
- Iterate ids from low to high for sink-to-source.

## Useful facts about the condensation
- A source SCC (no incoming edges) must be reached from outside.
- To make the graph strongly connected, add `max(#sources, #sinks)` edges (when more than one SCC exists).
- Number of SCCs = 1 means the whole graph is strongly connected.

## 2-SAT mapping (quick recipe)
For each clause `(a or b)` add `not a -> b` and `not b -> a`. After `run()`, if `comp[x] == comp[not x]` for any `x`, it is unsatisfiable. Otherwise set `x = true` iff `comp[x] < comp[not x]` (with Tarjan's numbering).

## Pitfalls
- It is for directed graphs only. For undirected connectivity use components. For 2-edge-connected parts use bridges.
- The condensation can have duplicate edges between the same two components, `condensation()` removes them.
- The DFS is iterative on purpose. A recursive Tarjan crashes on a long chain.
- Self-loops are harmless.
