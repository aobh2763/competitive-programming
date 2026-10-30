# Number Theoretic Transform (NTT)

**File:** `ntt.cpp`

## What it does
Multiplies two polynomials (or computes a **convolution**) modulo `998244353` in O(n log n), instead of the O(n^2) schoolbook method.

## Use it when
- You must compute `c[k] = sum_{i + j = k} a[i] * b[j]` for arrays of length 1e5 - 1e6.
- Counting problems that combine independent choices: "number of ways to reach sum k using one element from each of two sets".
- Big-integer multiplication (digits as coefficients, then carry).
- String matching with wildcards, or counting pairs with a given difference or sum.

## Complexity
O((n + m) log(n + m)). For lengths 2^20, it runs in a few hundred ms.

## Setup
`998244353 = 119 * 2^23 + 1`, primitive root `3`. Because `2^23` divides `p - 1`, the roots of unity exist for any power-of-two length up to about 8 million.

## Usage
```
vector<int> c = multiply(a, b);   // coefficients mod 998244353
```
The result has `a.size() + b.size() - 1` entries.

## Tricks
- **Power of a polynomial / generating functions:** multiply repeatedly or use binary exponentiation of polynomials.
- **Product of many polynomials:** divide and conquer, multiply the halves with NTT (total O(n log^2 n)).
- **Other modulus (e.g. 1e9+7):** compute the convolution under several NTT primes and merge with CRT (see `gcd_crt`), or use FFT with `double` and split the coefficients.
- **Counting by value:** put a `1` at index `value` in each array, then `c[s]` counts pairs summing to `s`.
- **Difference instead of sum:** reverse one array before multiplying.

## Pitfalls
- All input coefficients must be in `[0, 998244353)`. Reduce negatives first.
- If the real answer exceeds the modulus (for exact counts of pairs), the result is only correct mod `998244353`.
- The transform length is a power of two at least `a.size() + b.size() - 1`. Forgetting that causes wrap-around errors.
- This simple version recomputes twiddle factors per stage. It is fast enough for 1e6, but for tight limits precompute the roots.
- For tiny sizes (below ~64) schoolbook multiplication is faster.
