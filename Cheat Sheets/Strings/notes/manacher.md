# Manacher's Algorithm (Palindromes)

**File:** `manacher.cpp`

## What it does
Finds **every** palindromic substring in O(n). It computes two arrays:
- `d1[i]`: number of odd-length palindromes centred at `i` (the radius, counting the single character).
- `d2[i]`: number of even-length palindromes centred **between** `i-1` and `i`.

From them: `longest()`, `count_palindromes()` and an O(1) `is_palindrome(l, r)`.

## Use it when
- "Longest palindromic substring."
- "Count palindromic substrings" (counted by position, so `aaa` has 6).
- Many queries "is `s[l..r]` a palindrome?" (the O(1) test).
- Palindrome-based DP (e.g. minimum palindromic cuts) where you need the palindrome table quickly.

## The idea
Keep the palindrome with the **rightmost end** seen so far. For a new centre inside it, the mirror centre's radius gives a free lower bound, so only the characters beyond the boundary need comparing. Each extension moves the boundary right, so O(n) total.

## Reading the arrays
For `s = "abacaba"`:
- `d1[3] = 4`: the odd palindromes centred at index 3 are `c`, `aca`, `bacab`, `abacaba`.
- A radius `d` at centre `i` means the longest odd palindrome is `s[i-d+1 .. i+d-1]`, length `2d - 1`.
- For `d2[i] = k`, the longest even palindrome is `s[i-k .. i+k-1]`, length `2k`.

## Complexity
O(n) time and memory.

## Pitfalls
- `is_palindrome(l, r)` uses **inclusive** indices.
- The number of palindromic substrings can be about `n^2 / 2`, so use `long long`.
- `longest()` returns the first longest one when there are ties.
- It handles only contiguous substrings. For palindromic **subsequences**, use DP (see `dynamic_programming/sequence_dp`).
- Alternative: hashing with a reverse hash answers `is_palindrome` probabilistically.
