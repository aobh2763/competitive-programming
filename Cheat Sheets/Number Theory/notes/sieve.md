# Sieves

**File:** `sieve.cpp`

## What it does
- `Sieve(n)`: **linear sieve** in O(n) producing `spf` (smallest prime factor), the list of primes, Euler's `phi` and Moebius `mu` for every number up to `n`.
- `factorize(x)` via `spf` in O(log x), and `divisors(x)`.
- `simple_sieve(n)`: classic Eratosthenes, just the prime list.
- `segmented_sieve(L, R)`: primes inside a window, for `R` up to about 1e12.

## Use it when
- You need primality or factorization for **many** numbers up to 1e6 - 1e7.
- You need `phi(i)` or `mu(i)` for all `i` (counting coprime pairs, gcd sums).
- The range is large but the **window** `R - L` is small (about 1e7): segmented sieve.

## Complexity
| What                 | Time / Memory                       |
|----------------------|-------------------------------------|
| Linear sieve         | O(n) time, ~4 ints per number       |
| `factorize`          | O(log x)                            |
| Segmented sieve      | O((R-L) log log R + sqrt(R))        |

At `n = 1e7` the four int arrays take about 160 MB. Pass `with_phi_mu = false` or use `simple_sieve` when memory is tight.

## Formulas
- `phi(p^k) = p^k - p^(k-1)`, and phi is **multiplicative**.
- `mu(n) = 0` if `n` has a squared prime factor, else `(-1)^(number of distinct primes)`.
- **Moebius inversion:** if `F(n) = sum_{d | n} f(d)` then `f(n) = sum_{d | n} mu(d) F(n/d)`.
- **Count pairs with gcd = 1:** `#{(a, b) <= n : gcd(a, b) = 1} = sum_{d=1}^{n} mu(d) * floor(n/d)^2`.
- **Sum of gcds / lcm-style sums:** rewrite using `sum_{d | n} phi(d) = n`.

## Harmonic-sum sieves (O(n log n))
Many "for all numbers" tasks are easiest by looping multiples:
```
for (int d = 1; d <= n; d++)
    for (int m = d; m <= n; m += d)
        divisor_count[m]++;        // or sigma[m] += d, etc.
```

## Pitfalls
- `spf[x]` is only valid for `2 <= x <= n`; `factorize(1)` returns empty.
- Inside the sieve `i * p` must be done in `long long`, otherwise `i * p` overflows for `n` near 2^31.
- `is_prime(x)` only works for `x <= n`. For larger values use `primality.cpp`.
- A segmented sieve must not cross off the primes themselves (the code starts at `max(p*p, ...)`).
- `divisors(x)` returns an **unsorted** list.
