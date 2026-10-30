# Digit DP

**File:** `digit_dp.cpp`

## What it does
Counts how many numbers in `[0, N]` (or `[L, R]`) have digits satisfying a property. `DigitDP` is a small framework: you describe a **state machine** over digits, and it counts accepted numbers. Two examples are included: digit sum divisible by `K`, and no two equal adjacent digits.

## Use it when
- "How many numbers in `[L, R]` have digit sum `S`, digit sum divisible by `K`, no digit 4, ...?"
- `N` is huge (up to 1e18) so you cannot loop.
- The property can be tracked with a **small state** while reading digits left to right.

## The idea
1. Write `N` as a string of digits.
2. Build numbers digit by digit from the left. Remember a **tight** flag (the prefix so far equals `N`'s prefix, so the next digit is limited) and a **started** flag (leading zeros do not count).
3. When not tight, the remaining digits are free, so the count depends only on `(position, state, started)`. Memoize it.

## What you provide
| Piece                       | Meaning                                                  |
|-----------------------------|----------------------------------------------------------|
| `S`                         | number of states                                         |
| `init`                      | state before any digit                                   |
| `step(state, digit, started)` | new state, or `-1` to reject the number                |
| `accept(state)`             | does a finished number with this state count?            |

Examples of states: digit sum mod `K`, last digit (11 values incl. "none"), parity of a count, "have I seen digit 3 yet".

## Complexity
O(digits * S * 10). For 18 digits and a few hundred states it is instant.

## Range counting
`count_range(L, R) = count_upto(R) - count_upto(L - 1)`.

## Pitfalls
- The number **0 has no digits** in this model (it is all leading zeros), so `accept(init)` decides whether 0 counts. Check that against the problem.
- If leading zeros must not affect the state (e.g. "no two equal adjacent digits"), return the same state while `started` is false, as in the examples.
- A digit sum up to `9 * 18 = 162` needs 163 states if you track the exact sum.
- For other bases, change `to_string` and the digit limit `9`.
- `count_upto` builds a fresh memo each call. That is fine for a few queries; for thousands, reuse a memo for the free (non-tight) part.
