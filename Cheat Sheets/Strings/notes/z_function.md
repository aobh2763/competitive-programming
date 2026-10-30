# Z-Function

**File:** `z_function.cpp`

## What it does
`z[i]` is the length of the longest common prefix of `s` and the suffix starting at `i` (with `z[0] = n` by convention). It gives pattern search, periods and prefix-matching information in O(n).

Functions: `z_function`, `z_search`, `smallest_period_z`, `sum_of_z`.

## Use it when
- Pattern matching (same job as KMP), when you find Z easier to think about.
- "For every suffix, how much of the beginning of `s` does it match?"
- Counting or checking prefix-related structure: periods, "prefix equals suffix" checks.

## The idea
Keep the rightmost window `[l, r)` that matched the prefix of `s`. For a new position `i` inside it, the mirror position `i - l` already tells you a lower bound for `z[i]`, so you only compare characters beyond `r`. Each character is compared a bounded number of times, so O(n).

## Z vs prefix function
They contain the same information and convert into each other in O(n).
| Prefix function (`pi`)                | Z-function                               |
|---------------------------------------|------------------------------------------|
| Longest border of each **prefix**     | Prefix-match length of each **suffix**   |
| Natural for automata, periods         | Natural for "compare suffixes to the start" |

## Quick formulas
- `s` has period `p` (with `p < n`) iff `p + z[p] == n`.
- Pattern `p` occurs at position `i` in `t` iff `z[|p| + 1 + i] >= |p|` in the Z-array of `p + sep + t`.
- Number of distinct characters in a prefix-related sum: `sum_of_z` counts pairs (suffix, matching prefix length).

## Complexity
O(n) time and memory.

## Pitfalls
- `z[0]` is `n` here (some texts define it as 0). Ignore it when you do not need it.
- The separator must not occur in either string.
- Do not confuse "period" (`p + z[p] == n`) with "the string is `n/p` repetitions of a block". That also needs `n % p == 0`.
