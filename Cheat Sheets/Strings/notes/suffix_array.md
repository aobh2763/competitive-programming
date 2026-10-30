# Suffix Array & LCP Array

**File:** `suffix_array.cpp`

## What it does
- `suffix_array(s)`: the starting positions of all suffixes of `s` in sorted order.
- `lcp_array(s, sa)`: `lcp[k]` = longest common prefix of the `k`-th and `(k+1)`-th suffix in that order (Kasai's algorithm).
- `count_distinct_substrings`, `find_occurrences` (all matches of a pattern), `longest_repeated_substring`.

## Use it when
- Many queries on **one fixed text**: "where does pattern `p` occur?", "how many distinct substrings?", "longest repeated substring".
- The problem is about **comparing suffixes** (lexicographically smallest rotation or suffix, k-th smallest substring).
- You need a deterministic tool that does more than a single pattern search.

## Key facts
- Sorted suffixes that share a prefix are **adjacent**. So all occurrences of a pattern form a contiguous range in the suffix array (`find_occurrences` finds it by binary search).
- **Distinct substrings** = `n(n+1)/2 - sum(lcp)`.
- **LCP of any two suffixes** `i` and `j` = minimum of `lcp` over the range between their ranks. Combine with a sparse table (`trees/sparse_table.cpp`) for O(1) queries.
- **Longest common substring of `a` and `b`:** build the suffix array of `a + '#' + b` and take the maximum `lcp` between neighbours that come from different strings.

## Complexity
| Operation            | Time          |
|----------------------|---------------|
| `suffix_array`       | O(n log n)    |
| `lcp_array`          | O(n)          |
| `find_occurrences`   | O(m log n)    |
| Memory               | O(n)          |

## Pitfalls
- The string must not contain `'\0'` (it is used as the sentinel).
- When joining two strings use a separator character that appears in neither.
- `lcp` has size `n - 1`: `lcp[k]` relates neighbours `k` and `k+1`.
- For one pattern on one text, KMP or Z is simpler. Use the suffix array when you have many different queries.
- For 1e6+ characters the O(n log n) doubling is fine but memory heavy (several int arrays). SA-IS or a suffix automaton are alternatives for tight limits.
