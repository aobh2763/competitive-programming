# KMP & the Prefix Function

**File:** `kmp.cpp`

## What it does
Computes the **prefix function** `pi`, where `pi[i]` is the length of the longest proper prefix of `s[0..i]` that is also a suffix of it (a "border"). From it you get pattern search, periods, borders and occurrence counts, all deterministically in O(n).

Functions: `prefix_function`, `kmp_search`, `smallest_period`, `smallest_repeating_unit`, `borders`, `count_prefix_occurrences`.

## Use it when
- "Find all occurrences of a pattern in a text" (with overlaps).
- "Is the string a repetition of a smaller block?" (`abcabcabc`).
- "What is the longest prefix that is also a suffix?" (border).
- "How many times does each prefix appear inside the string?"

## The idea
When a match fails after `k` matched characters, you do not restart. You fall back to the **longest border** of the matched part, `pi[k-1]`, because that part of the pattern already matches the text. Each step either grows the match or shortens it, and the total shrinking is bounded by the total growing, so it is O(n).

## Quick formulas
| Question                              | Answer                                           |
|---------------------------------------|--------------------------------------------------|
| Smallest period `p` (`s[i] = s[i+p]`) | `n - pi[n-1]`                                    |
| `s` is a repetition of a block        | `n % p == 0` with `p` the smallest period, and `p < n` |
| All borders                           | `pi[n-1]`, then `pi[pi[n-1] - 1]`, ...           |
| Pattern occurrences                   | positions where `pi` of `p + sep + t` equals `|p|` |

## Complexity
O(n) for the prefix function, O(n + m) for search. Memory O(n + m).

## Pitfalls
- `pi` is **proper** prefix only (never the whole string).
- The separator in `p + sep + t` must not occur in either string.
- `smallest_period` is the period in the "borderline" sense (`abcab` has period 3 though 3 does not divide 5). Use `smallest_repeating_unit` for "repeated block" questions.
- Match positions from `kmp_search` are start indices in the text.
- For many patterns at once, use Aho-Corasick instead.
