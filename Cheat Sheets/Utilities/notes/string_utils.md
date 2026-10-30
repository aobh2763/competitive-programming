# String Utilities

**File:** `string_utils.cpp`

## What it does
`split` (one delimiter, keeps empty pieces), `split_ws` (any whitespace), `join`, `trim`, `to_lower`/`to_upper`, `rle` (run-length encoding), `to_base`/`from_base`, `is_subsequence`, `is_palindrome`.

## Use it when
- Parsing input lines like `"3,4,,5"` or `"cmd arg1 arg2"`.
- Compressing runs: `"aaabcc"` gives `a3 b1 c2`.
- Problems with number bases (2 to 36) or palindromes and subsequence checks.

## Tricks
- **Read a whole line with spaces:** after `cin >> n`, call `cin.ignore()` (or `getline(cin >> ws, s)`) before `getline`.
- **Character arithmetic:** `c - 'a'` is the letter index, `'a' + i` converts back.
- **Frequency count:** `int cnt[26] = {}; for (char c : s) cnt[c - 'a']++;`
- **Is it an anagram?** Compare two frequency arrays.
- **Longest palindromic substring, pattern matching, hashing:** these need real string algorithms (KMP, Z, hashing, Manacher), which belong in a separate strings sheet.

## Pitfalls
- `to_lower` and `to_upper` work for ASCII only.
- `split` keeps empty pieces (`"a,,b"` gives 3 parts). Filter them out if you do not want them.
- `from_base` does no validation: an invalid character gives garbage.
- Mixing `cin >> x` and `getline` without `ignore` reads an **empty** line.
- Passing `char` to `isspace` / `tolower` as a negative value is undefined. The code casts to `unsigned char` for that reason.
- `string::substr` and concatenation in a loop can be O(n^2). Use `push_back` or `reserve` in hot paths.
