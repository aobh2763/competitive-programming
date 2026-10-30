# Aho-Corasick (Multi-Pattern Matching)

**File:** `aho_corasick.cpp`

## What it does
Searches for **many patterns** in a text in one pass. It builds a trie of the patterns, adds **suffix links** (where to continue after a mismatch, like KMP's fallback), and completes the transitions so each text character costs O(1).

Functions: `add`, `build`, `count_occurrences` (per pattern), `contains_any`.

## Use it when
- A dictionary of forbidden/target words and one text: count or detect all matches.
- "Count strings of length `n` that avoid every pattern" (automaton DP: state = automaton node).
- Filtering text for a list of banned words.

## How it works
- **Suffix link** of a node = the longest proper suffix of its string that is also a trie prefix.
- **Full automaton:** if a node has no edge for `c`, use the transition of its suffix link. Then scanning needs no fallback loops.
- **Counting:** every visit to a node is also a visit to all nodes on its suffix-link chain. So count visits per node, then add each node's count to its link in reverse BFS order, and read the count at each pattern's end node.

## Complexity
| Step                 | Time                         |
|----------------------|------------------------------|
| Build                | O(total length * alphabet)   |
| Scan a text          | O(text length)               |
| Counting occurrences | O(nodes + text length)       |

## Automaton DP pattern
`dp[i][v]` = number of strings of length `i` ending in automaton state `v` without hitting a forbidden node. Transition over each letter with `go[v][c]`, skipping nodes that are (or link to) a pattern end.

## Pitfalls
- Call `build()` **after** adding all patterns and before scanning.
- Equal patterns share a node, and both get the same count (fine).
- Occurrence **counts** are easy, listing every **position** needs extra output-link traversal.
- Alphabet is `a-z`. Memory is `26 ints` per node.
- Overlapping matches are counted (`aa` appears 3 times in `aaaa`).
