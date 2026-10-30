# Combinatorics (mod prime)

**File:** `combinatorics.cpp`

## What it does
Precomputes factorials and inverse factorials up to `N`, then answers `nCr`, `nPr`, Catalan, stars-and-bars and multinomial in O(1). Also has Lucas' theorem and Pascal's triangle for the cases factorial tables can't handle.

## Use it when
- "Number of ways to choose / arrange ... modulo 1e9+7".
- Lattice paths, balanced brackets (Catalan), distributing identical items, anagram counting.
- `n` is huge (1e18) but the prime modulus is small: **Lucas**.
- The modulus is **composite** and `n <= ~5000`: **Pascal**.

## Complexity
| What                  | Cost         |
|-----------------------|--------------|
| Build `Comb(N)`       | O(N + log p) |
| `nCr`, `nPr`, ...     | O(1)         |
| `lucas`               | O(log_p n)   |
| `pascal(n)`           | O(n^2)       |

## Formula cheat sheet
| Counting question                                       | Formula                        |
|---------------------------------------------------------|--------------------------------|
| Choose r of n (order ignored)                           | `C(n, r)`                      |
| Arrange r of n (order matters)                          | `n! / (n-r)!`                  |
| Non-negative solutions of `x1+...+xk = n`               | `C(n+k-1, k-1)`                |
| Positive solutions of `x1+...+xk = n`                   | `C(n-1, k-1)`                  |
| Arrangements of a multiset                              | `n! / (k1! k2! ...)`           |
| Balanced bracket sequences with n pairs                 | Catalan `C(2n, n) / (n+1)`     |
| Monotone paths in an `a x b` grid                       | `C(a+b, a)`                    |
| Derangements                                            | `D(n) = (n-1)(D(n-1)+D(n-2))`  |
| Permutations with no restriction on cycles              | `n!`                           |

## Identities that save time
- **Hockey stick:** `sum_{i=r}^{n} C(i, r) = C(n+1, r+1)`.
- **Vandermonde:** `sum_k C(m, k) C(n, r-k) = C(m+n, r)`.
- **Symmetry:** `C(n, r) = C(n, n-r)`.
- **Row sum:** `sum_r C(n, r) = 2^n`.
- **Inclusion-exclusion:** count "none of the bad properties" as an alternating sum over subsets of properties.

## Composite modulus
- `n` small: Pascal's triangle (`pascal(n, m)`), no division needed.
- `n` large: factor `m` into prime powers, compute `C(n, r)` modulo each (by the exponent of `p` using Legendre's formula plus a factorial-without-p trick), then merge with CRT from `gcd_crt`.

## Pitfalls
- `Comb` needs `N >= max n` you will ever query, and the modulus must be **prime and larger than N**.
- `nCr(n, r)` returns 0 for `r > n` or `r < 0`, which is usually what you want for counting.
- For Catalan you need `N >= 2n`; for stars and bars you need `N >= n + k - 1`.
- Lucas needs `Comb` built with `mod = p` and `N >= p - 1`. Don't use it with big `p` (table too large).
- Don't multiply three residues without reducing after each product.
