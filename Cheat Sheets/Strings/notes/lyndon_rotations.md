# Lyndon Words & Minimal Rotation

**File:** `lyndon_rotations.cpp`

## What it does
- `duval(s)`: splits a string into its **Lyndon factorization**, a non-increasing list of Lyndon words.
- `min_rotation_index(s)` / `min_rotation(s)`: the lexicographically smallest cyclic rotation.
- `same_necklace(a, b)`: are two strings rotations of each other?

## Definitions
- A **Lyndon word** is strictly smaller than every one of its proper suffixes (and than all its rotations). Examples: `a`, `ab`, `aab`, `abb`. Not Lyndon: `aa`, `ba`, `aba`.
- **Factorization theorem:** every string is uniquely a concatenation `w1 w2 ... wk` of Lyndon words with `w1 >= w2 >= ... >= wk`. Example: `banana` = `b`, `an`, `an`, `a`.

## Use it when
- "Smallest string obtainable by rotating", "canonical form of a cyclic string".
- Comparing or hashing **necklaces** (cyclic strings): equal canonical forms mean equal necklaces.
- Lyndon-based problems: smallest suffix, minimal string by cutting and rearranging.

## Complexity
O(n) time, O(1) extra memory (besides the output).

## Alternatives
| Task                               | Other tools                                      |
|------------------------------------|--------------------------------------------------|
| Minimal rotation                   | suffix array of `s + s`, or hashing + binary search |
| Is `b` a rotation of `a`?          | `b` occurs in `a + a` (KMP / Z) with equal lengths |

## Pitfalls
- Rotation index is the **smallest** index among ties (e.g. `abab` gives 0).
- `duval` allocates substrings, fine for 1e6 characters but use index pairs if memory is tight.
- Compare strings only of equal length in `same_necklace` (the function checks it).
- Lexicographic order here is plain ASCII order.
