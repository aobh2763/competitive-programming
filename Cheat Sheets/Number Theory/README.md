# Number Theory Cheat Sheet

Each `.cpp` file has a matching `.md` with the "when and why".

## Which tool do I need?

| Problem looks like...                                          | Use                              | File |
|----------------------------------------------------------------|----------------------------------|------|
| "print answer modulo 1e9+7", big powers, divisions mod p       | `binpow`, `inv_prime`, `Mint`    | `modular` |
| gcd, lcm, inverse mod a non-prime, `ax + by = c`, system of congruences | ext. Euclid, CRT        | `gcd_crt` |
| nCr, nPr, Catalan, stars & bars, huge n with small prime       | Factorial tables, Lucas          | `combinatorics` |
| Primes up to 1e7, many factorizations, phi / mu for all numbers| Linear sieve                     | `sieve` |
| Primes in a window [L, R] with R up to 1e12                    | Segmented sieve                  | `sieve` |
| Factor / phi / divisors of **one** number up to ~1e12          | Trial division                   | `number_functions` |
| Is this 1e18 number prime? Factor a 1e18 number                | Miller-Rabin + Pollard rho       | `primality` |
| n-th term of a recurrence for n up to 1e18, walks of length L  | Matrix exponentiation            | `matrix_expo` |
| Multiply polynomials / convolution of size 1e5 - 1e6           | NTT                              | `ntt` |
| Solve a^x = b mod m, find a primitive root                     | BSGS, primitive root             | `discrete_log` |

## Choosing the right factorization

| Situation                                  | Use                                  |
|--------------------------------------------|--------------------------------------|
| Many numbers, each <= ~1e7                 | `Sieve::factorize` (spf), O(log x)   |
| A few numbers, each <= ~1e12               | trial division, O(sqrt n)            |
| Numbers up to 1e18                         | Pollard rho (`primality.cpp`)        |

## Handy facts

- **Fermat:** if p is prime and p does not divide a, then `a^(p-1) = 1 (mod p)`, so `a^-1 = a^(p-2)`.
- **Euler:** if `gcd(a, m) = 1` then `a^phi(m) = 1 (mod m)`. This lets you reduce huge exponents: `a^e = a^(e mod phi(m))`.
- **Huge exponents, any a:** for `e >= log2(m)`, `a^e = a^(e mod phi(m) + phi(m)) (mod m)`.
- **phi(n)** = `n * prod(1 - 1/p)` over distinct primes p of n. **sum of phi(d) over d | n = n.**
- **Number of divisors** `d(n) = prod(e_i + 1)`. At most 1344 for n <= 1e9, 103680 for n <= 1e18.
- **Number of primes** below 1e6 is 78,498; below 1e7 is 664,579; below 1e9 is 50,847,534.
- **Useful primes:** `1e9+7`, `998244353`, `1e9+9`.
- **Wilson:** `(p-1)! = -1 (mod p)` for prime p.

## Pitfalls that apply to everything here

- **Negative remainders:** in C++ `-7 % 5 = -2`. Always normalise with `((x % m) + m) % m`.
- **Overflow:** `a * b % m` needs `a * b` to fit in 64 bits. For `m` up to ~3e9 plain `long long` is fine, for larger `m` use `mulmod` (128-bit).
- **Division mod m** means multiplying by the inverse. It only exists when `gcd(a, m) = 1`, and Fermat's inverse additionally needs `m` prime.
- **Modulus choice:** NTT needs `998244353`; factorial tables need a prime modulus larger than `N`.
- **Reducing exponents:** you can reduce an exponent modulo `p - 1` only for a **prime** `p` not dividing the base; the general rule uses `phi`.
