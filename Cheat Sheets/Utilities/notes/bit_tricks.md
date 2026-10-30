# Bit Tricks

**File:** `bit_tricks.cpp`

## What it does
Bit helpers (`popcount`, `lowbit`, `highest_bit_index`, `next_pow2`, `gray`), mask enumeration (`for_each_submask`, `for_each_combination`), `sos_subset_sum`, and an `XorBasis`.

## Quick reference
| Task                      | Expression                              |
|---------------------------|------------------------------------------|
| Test bit `k`              | `x >> k & 1`                             |
| Set / clear / flip bit    | `x \| (1LL << k)`, `x & ~(1LL << k)`, `x ^ (1LL << k)` |
| Lowest set bit            | `x & -x`                                 |
| Remove lowest set bit     | `x & (x - 1)`                            |
| Is power of two           | `x && !(x & (x - 1))`                    |
| Count set bits            | `__builtin_popcountll(x)`                |
| `floor(log2(x))`          | `63 - __builtin_clzll(x)`                |
| All-ones mask of n bits   | `(1LL << n) - 1`                         |
| Swap without temp         | `a ^= b; b ^= a; a ^= b;` (just use `swap`) |

## Use it when
- `n <= 20` and you try every subset (bitmask DP, brute force over subsets).
- Subset DP: "for each mask, combine over its submasks" is O(3^n) total.
- "Sum over all subsets / supersets" for every mask: **SOS DP** in O(n 2^n).
- XOR problems: maximum XOR of a subset, can I reach value `x`, size of the XOR span.
- Counting numbers with a given popcount, Gray codes, power-of-two checks.

## XOR basis facts
- After inserting numbers, `rank` is the dimension of their span, and the span has `2^rank` elements.
- Max XOR of any subset: greedily XOR a basis vector whenever it increases the value (`max_xor`).
- Max XOR of a subset **with** some fixed value `v`: start from `v` instead of `0`.

## Complexity
| Operation                  | Time                       |
|----------------------------|----------------------------|
| `for_each_submask(mask)`   | O(2^popcount(mask))        |
| all masks and submasks     | O(3^n) total               |
| `for_each_combination`     | O(C(n, k))                 |
| `sos_subset_sum`           | O(bits * 2^bits)           |
| XorBasis insert / query    | O(62)                      |

## Pitfalls
- Use `1LL << k` (not `1 << k`) when `k >= 31`, or you overflow an `int`.
- `__builtin_clz` / `__builtin_ctz` are **undefined for 0**. Check `x != 0` first.
- `for_each_submask` skips the empty submask `0`. Handle it separately if you need it.
- Operator precedence: `x & 1 == 0` parses as `x & (1 == 0)`. Always parenthesize comparisons with bit operators.
- Right shift of a negative signed number is implementation-defined. Keep masks unsigned.
- `sos_subset_sum` computes sums over **sub**masks. For supermasks, iterate `mask` bits the other way (`f[mask] += f[mask | (1 << b)]` when bit b is not set).
