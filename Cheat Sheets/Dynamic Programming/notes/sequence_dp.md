# Sequence DP: LCS, Edit Distance, Palindromes, LIS

**File:** `sequence_dp.cpp`

## What it does
- `lcs`: longest common **subsequence** of two strings (returns the string itself).
- `edit_distance`: fewest insert/delete/replace operations to turn `a` into `b`.
- `longest_palindromic_subsequence`: longest palindrome you can get by deleting characters.
- `longest_common_substring`: longest common **contiguous** piece.
- `lis_indices`: one longest strictly increasing subsequence (positions).

## Use it when
- Two sequences are compared: "how similar are they?", diff tools, spell checking.
- "Delete the fewest characters to make X": it is usually `n - LCS` of something.
- "Longest increasing / chain / nested sequence".

## Subsequence vs substring
- **Subsequence:** characters in order, gaps allowed (`ace` is a subsequence of `abcde`).
- **Substring:** consecutive characters (`bcd`).

## The tables
| Problem                | State                                  | Transition                                      |
|------------------------|----------------------------------------|-------------------------------------------------|
| LCS                    | `dp[i][j]` for prefixes `a[0..i)`, `b[0..j)` | match: `dp[i-1][j-1] + 1`, else `max(dp[i-1][j], dp[i][j-1])` |
| Edit distance          | same prefixes                          | `min(delete, insert, replace-or-match)`         |
| Palindromic subsequence| `dp[i][j]` for the window `s[i..j]`    | ends equal: `dp[i+1][j-1] + 2`, else `max(dp[i+1][j], dp[i][j-1])` |
| Common substring       | suffix length ending at `(i, j)`       | match: `prev + 1`, else `0` (answer = max cell) |

## Complexity
| Function                          | Time        | Memory     |
|-----------------------------------|-------------|------------|
| `lcs`                             | O(n * m)    | O(n * m)   |
| `edit_distance`                   | O(n * m)    | O(m)       |
| `longest_palindromic_subsequence` | O(n^2)      | O(n^2)     |
| `longest_common_substring`        | O(n * m)    | O(m)       |
| `lis_indices`                     | O(n log n)  | O(n)       |

## Tricks
- **Shortest common supersequence** length = `n + m - LCS`.
- **Minimum deletions to make a palindrome** = `n - LPS`.
- **LPS = LCS of the string and its reverse.**
- **LCS of two permutations** reduces to LIS (map positions), which gives O(n log n).
- **LIS non-decreasing:** replace the strict `<` with `<=` in the comparison (see `lis_length` in `utilities/array_utils.cpp`).
- **Weighted edit costs:** replace the `+ 1` terms with the problem's costs.

## Pitfalls
- DP tables are **(n+1) x (m+1)**: row 0 and column 0 are the empty prefix (base cases).
- `lcs` backtracking has several correct answers when ties exist. Any one is valid.
- A 5,000 x 5,000 int table is 100 MB. Roll the rows if you only need the length.
- `lis_indices` is strictly increasing. For equal values allowed, use `upper_bound` logic.
- The functions take `string`. For `vector<int>` sequences, copy the code and change the types.
