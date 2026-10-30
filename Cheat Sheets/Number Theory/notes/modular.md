# Modular Arithmetic

**File:** `modular.cpp`

## What it does
- `binpow`: `a^e mod m` in O(log e).
- `binpow64` / `mulmod`: the same for moduli beyond 3e9, using 128-bit products.
- `inv_prime`: inverse of `a` modulo a prime (Fermat).
- `inverses_upto`: all inverses `1..n` in O(n).
- `Mint<M>`: a number type that reduces itself mod `M`, so you write normal arithmetic.

## Use it when
- The statement says "print the answer modulo 1e9+7 (or 998244353)".
- You need `a / b mod p` (compute `a * inv(b)`).
- You need a huge power: `2^(10^18)`, `3^n`, etc.
- You write a long formula and keep forgetting `% MOD`: use `Mint`.

## Complexity
| Operation        | Time      |
|------------------|-----------|
| `binpow`         | O(log e)  |
| `inv_prime`      | O(log p)  |
| `inverses_upto`  | O(n)      |

## Rules of modular arithmetic
| Operation | Rule                                    |
|-----------|-----------------------------------------|
| add       | `(a + b) % m`                           |
| subtract  | `((a - b) % m + m) % m`                 |
| multiply  | `(a % m) * (b % m) % m`                 |
| divide    | `a * inv(b) % m`, needs `gcd(b, m) = 1` |
| compare   | **not allowed** after reducing (can't tell which was bigger) |

## Tricks
- **Many inverses:** use `inverses_upto`, or build factorial tables (see `combinatorics`). Calling `inv_prime` N times costs O(N log m).
- **Exponent too big for `long long`:** if the exponent is itself a huge power `a^(b^c) mod p`, reduce the exponent mod `p - 1` (when `p` is prime and `p` does not divide `a`).
- **Sum of a geometric series:** `(r^n - 1) * inv(r - 1)`, or divide and conquer when `r = 1 (mod p)`.
- **Switching modulus:** change `MOD`, or use `Mint<998244353>`.

## Pitfalls
- `binpow` uses plain `long long` multiplication. That is safe only for `m < ~3e9`. For bigger moduli call `binpow64`.
- `inv_prime(a)` is wrong if `m` is not prime, or if `a` is a multiple of `m`.
- `Mint` does `%` on construction, so `Mint(x)` is fine for negative `x`.
- `Mint` division by zero silently returns 0.
- Don't compare residues with `<` and expect real ordering.
