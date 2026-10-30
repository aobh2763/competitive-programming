# Primality & Factorization up to 1e18

**File:** `primality.cpp`

## What it does
- `is_prime(n)`: **deterministic** Miller-Rabin, exact for every 64-bit integer.
- `factorize(n)`: Pollard's rho (Brent's variant with batched gcd) plus Miller-Rabin, for `n` up to about 1e18.

## Use it when
- A single number can be as large as 1e18 and you must decide if it is prime.
- Trial division up to `sqrt(n)` would be too slow (`sqrt(1e18) = 1e9`).
- Problems like "count divisors / sum of divisors / phi of a number up to 1e18" or "factor many numbers up to 1e12 - 1e18".

## Complexity
| What          | Cost                                             |
|---------------|--------------------------------------------------|
| `is_prime`    | O(12 * log n) multiplications                    |
| `factorize`   | about O(n^(1/4)) expected for the hardest inputs |

Roughly 1e18 factors in a few milliseconds, so thousands of such numbers are fine.

## How it works
- **Miller-Rabin:** write `n - 1 = d * 2^s`. A prime passes for every base `a`: either `a^d = 1`, or `a^(d * 2^r) = -1` for some `r < s`. Testing the first 12 primes as bases is provably enough for all `n < 3.3e24`.
- **Pollard rho:** iterate `x -> x^2 + c (mod n)`. Two sequences collide modulo a hidden prime factor `p` before they collide modulo `n`, so `gcd(x - y, n)` reveals a factor. Brent's cycle detection plus multiplying 128 differences per gcd makes it fast.

## Tricks
- **Smaller bases for smaller n:** for `n < 2^32` the bases `{2, 7, 61}` suffice, for `n < 3.4e14` use `{2, 3, 5, 7, 11, 13, 17}`.
- **Count / sum of divisors of a huge number:** `factorize`, then the formulas in `number_functions.md`.
- **phi of a huge number:** same, `n / p * (p - 1)` per prime.

## Pitfalls
- It uses `unsigned __int128` for `mulmod`. This is a GCC/Clang feature and is fine on Codeforces (64-bit), but not available on MSVC.
- `rho` is randomized. It can return `n` itself on a bad polynomial, so the code retries. Never call it on a prime (check `is_prime` first).
- `factorize` strips primes below 100 by trial division first, because that avoids awkward tiny cases and speeds things up.
- `factorize(1)` returns an empty vector.
- Factorization of **many** numbers below 1e7 is faster with the spf sieve in `sieve.cpp`.
