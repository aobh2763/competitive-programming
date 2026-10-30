# Tries (Prefix Trees) & XOR Trie

**File:** `trie.cpp`

## What it does
- `Trie`: a tree where each edge is a letter and each path from the root spells a prefix. Supports `insert`, `erase`, exact `count`, `count_prefix` and `longest_common_prefix`.
- `XorTrie`: a binary trie of numbers (bit by bit from the highest), used for **maximum XOR** queries.

## Use it when
- "How many stored words start with this prefix?", autocomplete, dictionary lookups.
- "Does any word begin with this?", prefix-free checks.
- **Maximum XOR of two numbers** in an array, or of `x` with any stored number.
- DP or counting over words that share prefixes.

## Complexity
| Operation                 | Time                 |
|---------------------------|----------------------|
| `Trie` insert / count / erase | O(length of the word) |
| `XorTrie` insert / max_xor| O(bits)              |
| Memory                    | O(total characters * alphabet) |

## How max XOR works
To maximize `x XOR y`, you want `y` to differ from `x` at the highest bit possible. Walk the trie from the top bit: if the child with the **opposite** bit exists, take it (that bit becomes 1 in the result), otherwise take the other child. Greedy works because a higher bit outweighs all lower bits together.

## Tricks
- **Max XOR of any pair:** insert numbers one by one, querying before each insert.
- **Max XOR subarray:** insert prefix XORs, then query each prefix XOR (a subarray XOR is `pref[r] ^ pref[l]`).
- **Count pairs with XOR < K:** store counts per node and walk the bits of `K`.
- **Persistent / offline versions** (versioned tries) answer "max XOR with a number from the range `[l, r]`".

## Pitfalls
- The string trie expects lowercase `a-z`. A node holds 26 ints, so 1e6 characters can take about 100 MB. For big alphabets use `map<char,int>` per node, or sort words and use a suffix array instead.
- `erase` only decrements counters, nodes stay allocated.
- `XorTrie(bits)` needs every number to be `< 2^bits` (use 30 for values up to ~1e9, 60 for up to ~1e18) and non-negative.
- `max_xor` needs at least one stored number.
- The root's `pass` counter counts the number of words, so `count_prefix("")` is the total.
