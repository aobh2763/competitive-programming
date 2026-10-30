# Primitive Roots & Discrete Logarithm

**File:** `discrete_log.cpp`

## What it does
- `primitive_root(p)`: the smallest generator of the multiplicative group modulo prime `p`.
- `discrete_log(a, b, m)`: the smallest `x >= 0` with `a^x = b (mod m)`, or `-1`. Works even when `gcd(a, m) > 1`.

## Use it when
- "Find x such that `a^x = b (mod m)`" (the discrete logarithm problem).
- You need a generator to turn multiplication into addition: with `g` primitive, every nonzero `a = g^k`, so products become sums of exponents.
- You need a root of unity for NTT with a different prime.
- Counting solutions of `x^k = a (mod p)`: take logs with respect to a primitive root, then solve a linear congruence.

## Complexity
O(sqrt(m)) time and memory for BSGS. `primitive_root` is O(sqrt p) for the factorization of `p - 1`, plus a small number of exponentiations.

## How BSGS works
Write `x = n*p - q` with `n = ceil(sqrt(m))`. Then `a^x = b` becomes `a^(n*p) = b * a^q`.
1. **Baby steps:** store `b * a^q` for `q = 0..n` in a hash map.
2. **Giant steps:** for `p = 1..n`, look up `a^(n*p)`.

For `gcd(a, m) > 1` the code first divides common factors out of `a`, `b` and `m` (tracking a shift), until the modulus is coprime to `a`, then runs the steps above.

## Primitive roots
- Exist exactly for `m = 1, 2, 4, p^k, 2p^k` (p an odd prime). This file handles prime moduli.
- `g` is a primitive root of prime `p` iff `g^((p-1)/q) != 1` for every prime `q | p - 1`.
- 998244353 has root 3, 1e9+7 has root 5.

## Pitfalls
- Intermediate products use plain `long long`, so keep `m` below about 3e9.
- The hash map can be attacked by anti-hash tests on some judges. Use a custom hash, or sort a vector of pairs and binary search.
- `discrete_log` returns the **smallest** `x >= 0`. For the full solution set, find the multiplicative order of `a` and add multiples of it.
- Edge cases: `m = 1` returns 0, and `b = 1` returns 0 (since `a^0 = 1`).
- If no solution exists it returns `-1`, which is not a valid exponent, so check it.
