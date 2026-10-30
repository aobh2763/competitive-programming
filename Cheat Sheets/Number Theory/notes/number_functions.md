# Number Functions (trial division)

**File:** `number_functions.cpp`

## What it does
Quick, sieve-free tools for **one number at a time**: `factorize`, `euler_phi`, `count_divisors`, `sum_divisors`, `divisors`, plus integer helpers `isqrt`, `floor_div`, `ceil_div`, and the `sum_floor_div` divisor-block loop.

## Use it when
- You have one or a few numbers up to ~1e12 and need their factorization, phi, or divisors.
- You need an exact integer square root (instead of `sqrt()` rounding errors).
- You do floor or ceil division with **negative** numbers.
- You need `sum of floor(n / i)` or any sum over `floor(n / i)` for `n` up to 1e12.

## Complexity
Factorization-based functions are O(sqrt n). `divisors` is O(sqrt n + d log d). `sum_floor_div` is O(sqrt n).

## Multiplicative function formulas
For `n = p1^e1 * ... * pk^ek`:

| Function              | Formula                                 |
|-----------------------|-----------------------------------------|
| number of divisors    | `prod (e_i + 1)`                        |
| sum of divisors       | `prod (p_i^(e_i+1) - 1) / (p_i - 1)`    |
| Euler phi             | `n * prod (1 - 1/p_i)`                  |
| product of divisors   | `n^(d(n)/2)`                            |
| n is a perfect square | all `e_i` even (equivalently `d(n)` odd)|

## The divisor-block trick
`floor(n / i)` takes only about `2 * sqrt(n)` distinct values. Loop over blocks:
```
for (ll l = 1, r; l <= n; l = r + 1) {
    ll q = n / l;
    r = n / q;          // block [l, r] shares the value q
    // use q and the block length (r - l + 1)
}
```
Same trick works for `n / i` and `m / i` simultaneously with `r = min(n / (n/l), m / (m/l))`.

## Pitfalls
- Factorizing by trial division up to `sqrt(n)` for 1e18 is too slow, use `primality.cpp`.
- `sqrtl` can be off by one for large inputs. `isqrt` corrects it.
- C++ integer division truncates toward zero. `-7 / 2 = -3`, but `floor(-3.5) = -4`. Use `floor_div`.
- `sum_divisors` can overflow `long long` for large `n`. Reduce mod `p` or use `__int128`.
- `euler_phi` computes `r / p * (p - 1)`, dividing first on purpose to avoid overflow.
