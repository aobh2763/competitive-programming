# String Hashing

**File:** `string_hashing.cpp`

## What it does
Turns every prefix of a string into a number so that the hash of **any substring** can be computed in O(1). Equal substrings have equal hashes, so you compare numbers instead of characters.

Functions: `StringHash` (`get`, `equal`, `lcp`), `hash_of`, `hash_search` (Rabin-Karp style), `count_distinct_of_length`.

## Use it when
- You need to compare many pairs of substrings quickly.
- **Binary search on the answer** where the check is "does some substring of length `L` occur twice / in both strings?" (longest repeated substring, longest common substring).
- Checking palindromes with a forward and a reverse hash.
- 2D or "equal up to rotation" matching where KMP does not apply directly.

## How it works
Treat the string as a number in base `B` modulo `p`:
```
h[i+1] = h[i] * B + s[i]
hash(l, r) = h[r] - h[l] * B^(r - l)      (mod p)
```
This implementation uses `p = 2^61 - 1` (fast 128-bit reduction) and a **random base** `B`, so a collision on one comparison has probability about `length / 2^61`.

## Complexity
| Operation        | Time      |
|------------------|-----------|
| Build            | O(n)      |
| `get` / `equal`  | O(1)      |
| `lcp(i, j)`      | O(log n)  |
| `hash_search`    | O(n + m)  |

## Longest common substring of two strings (idea)
Binary search on the length `L`: put all hashes of length-`L` substrings of `a` in a set, and check whether any substring of `b` of length `L` is in it. Monotone in `L`, so O(n log n) total.

## Pitfalls
- **Never** use a fixed base with modulus `1e9+7` or natural 64-bit overflow: anti-hash tests (e.g. Thue-Morse strings) break them. Keep the random base and `2^61 - 1`.
- To compare hashes from **two different strings**, both must use the **same base** (pass it in, or use `hash_of(p, H.base)`).
- Ranges are **half-open** `[l, r)`.
- Characters are mapped to `value + 1`, so a character with value 0 never looks like "nothing".
- Hashing is probabilistic. If a problem needs a guaranteed answer, use KMP, Z or a suffix array.
- Subtracting hashes needs the `+ HMOD` correction (already done in `get`).
