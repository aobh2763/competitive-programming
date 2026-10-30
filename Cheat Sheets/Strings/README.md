# Strings Cheat Sheet

Each `.cpp` file has a matching `.md` with the "when and why". Start with `kmp` (or `z_function`) and `string_hashing`.

## Which tool do I need?

| Problem looks like...                                                      | Use                         | File |
|----------------------------------------------------------------------------|-----------------------------|------|
| Find a pattern in a text, periods, borders, "does s repeat?"               | Prefix function / KMP       | `kmp` |
| Same, plus "how does each suffix match the start of s?"                    | Z-function                  | `z_function` |
| Compare many substrings, find the longest common substring, 2D matching    | Rolling hash                | `string_hashing` |
| Palindromic substrings, longest palindrome, "is s[l..r] a palindrome?"     | Manacher                    | `manacher` |
| Store many words, prefix counts, autocomplete, max XOR of two numbers      | Trie / XOR trie             | `trie` |
| Many pattern searches, distinct substrings, longest repeated substring     | Suffix array + LCP          | `suffix_array` |
| Find a whole DICTIONARY of patterns in one text at once                    | Aho-Corasick                | `aho_corasick` |
| Smallest rotation, "are these two necklaces equal?", Lyndon factorization  | Duval                       | `lyndon_rotations` |

## KMP vs Z vs hashing

| Method        | Deterministic | Speed        | Best for                                              |
|---------------|---------------|--------------|-------------------------------------------------------|
| KMP (prefix function) | yes   | O(n + m)     | Borders, periods, pattern search, string automata      |
| Z-function    | yes           | O(n + m)     | Prefix-matching of every suffix, easier to reason about |
| Rolling hash  | no (tiny risk)| O(1) per substring after O(n) | Comparing arbitrary substrings, binary search on length |
| Suffix array  | yes           | O(n log n) build | Many different queries on one fixed text            |

## Complexity guide
| n (length)    | Aim for                                   |
|---------------|-------------------------------------------|
| up to 1e6     | O(n) or O(n log n): KMP, Z, Manacher, hash, suffix array |
| up to 5,000   | O(n^2) DP over substrings is fine         |
| several strings, total length 1e6 | Aho-Corasick, or a suffix array of a concatenation |

## Pitfalls that apply to everything here

- **Indexing:** all code is 0-indexed. Check half-open `[l, r)` (hash) vs inclusive `[l, r]` (Manacher).
- **Separators:** concatenating `p + '#' + t` only works if the separator does not appear in either string. The files use `'\x01'` and `'\0'`; change them if your input can contain those.
- **Alphabet:** the trie and Aho-Corasick assume lowercase `a-z`. For other alphabets change `26` or use `map<char, int>`.
- **Hash safety:** never use a fixed base with a small modulus, or the default overflow-based hash. Use the random base and `2^61 - 1` from `string_hashing.cpp`.
- **Slow substrings:** `s.substr(...)` copies (O(length)), and `s = s + c` in a loop can be O(n^2). Work with indices or `string_view` in hot loops.
- **Reading input:** use `getline` for lines with spaces. After `cin >> n` call `cin.ignore()` first.
- **Memory:** a trie node with 26 ints is 104 bytes. One million characters can be about 100 MB.
