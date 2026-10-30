# Matrix Exponentiation

**File:** `matrix_expo.cpp`

## What it does
Raises a `k x k` matrix to a power in O(k^3 log e). Includes `fib(n)`, `linear_recurrence(c, init, k)` and `count_walks` as examples.

## Use it when
- A sequence is defined by a **linear recurrence** and `n` is up to 1e18 (Fibonacci, tribonacci, `x_n = 2x_{n-1} + 3x_{n-2} + ...`).
- "How many walks of length exactly L from u to v?" (`L` huge, graph small).
- A DP transition is the same linear step repeated `n` times (states <= ~50).

## Complexity
O(k^3 log e). With `k = 50` and `e = 1e18` that is about 125,000 * 60 = 7.5e6 operations, fine.

## How to build the matrix
Pick a state vector holding everything the next step needs, then write the step as a matrix.

**Fibonacci:** state `(F_n, F_{n-1})`
```
[F_{n+1}]   [1 1] [F_n    ]
[F_n    ] = [1 0] [F_{n-1}]
```

**Recurrence with a constant:** `x_n = a*x_{n-1} + b*x_{n-2} + c`
Add a constant `1` to the state vector (3x3 matrix with a row `[0, 0, 1]`).

**Prefix sums of a sequence:** add a state entry for the running sum.

**Counting walks:** the answer is `A^L[u][v]`, where `A` is the adjacency matrix.

## Tricks
- **Larger `k` (up to ~1e4) with huge `n`:** Kitamasa or Berlekamp-Massey + polynomial exponentiation, O(k^2 log n).
- **DP with min/max (shortest walk of exactly L edges):** replace `(+, *)` with `(min, +)`. The same code shape works, with identity `0` on the diagonal and `INF` elsewhere.
- **Many queries on the same matrix:** precompute `M^(2^i)` and multiply vector-by-matrix instead (O(k^2) per bit).

## Pitfalls
- The code reduces mod the fixed constant `MOD`. Change it at the top if the problem uses another modulus.
- Each term `a[i][k] * o.a[k][j]` is below ~1e18, so adding it to a value below `MOD` still fits in signed 64-bit. Don't "optimize" by delaying the `%` over many terms.
- `linear_recurrence` assumes `init` has exactly `c.size()` terms starting from index 0.
- Matrix multiplication is not commutative. Keep the order consistent with how you built the transition.
- For `k = 1e3` or more, O(k^3 log n) is too slow, switch to the techniques above.
