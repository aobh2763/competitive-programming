# GCD, Extended Euclid, Diophantine, CRT

**File:** `gcd_crt.cpp`

## What it does
- `gcd_ll`, `lcm_ll`: basics.
- `ext_gcd(a, b, x, y)`: returns `g = gcd(a, b)` and finds `x, y` with `a*x + b*y = g`.
- `mod_inv(a, m)`: inverse modulo **any** `m` (returns -1 if it does not exist).
- `diophantine`: solves `a*x + b*y = c`.
- `crt` / `crt_all`: Chinese Remainder Theorem, including **non-coprime** moduli.

## Use it when
- The modulus is **not prime**, so Fermat's inverse does not work.
- "Find integers x, y with ax + by = c" (buying two item types for an exact total).
- "x leaves remainder r1 mod m1 and r2 mod m2 (and more)": CRT.
- A modulus is composite, so you split it into prime powers, solve each, and CRT the answers back.

## Complexity
All O(log min(a, b)).

## Diophantine: all solutions
If `g = gcd(a, b)` divides `c`, there are infinitely many solutions:

```
x = x0 + k * (b / g)
y = y0 - k * (a / g)         for any integer k
```
To get the **smallest non-negative x**: `x = ((x0 % (b/g)) + (b/g)) % (b/g)`, then recompute `y = (c - a*x) / b`.

## CRT behavior
`crt(r1, m1, r2, m2)` returns `{r, lcm}` with `0 <= r < lcm`, or `{-1, -1}` if the system is inconsistent. Inconsistent exactly when `r1 != r2 (mod gcd(m1, m2))`. `crt_all` folds it over many congruences.

## Pitfalls
- `ext_gcd` expects **non-negative** arguments.
- In `diophantine`, `x *= c / g` can overflow when `c` is large. Use `__int128` if needed.
- `lcm` can overflow `long long` when combining many moduli. `crt` uses 128-bit intermediate math but the returned lcm must still fit in `long long`.
- `gcd_ll(0, 0) = 0`. Guard against `a = b = 0`.
- `mod_inv` returns `-1` for "no inverse", so check before using it.
