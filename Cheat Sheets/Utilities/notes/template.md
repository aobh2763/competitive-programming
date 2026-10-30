# Contest Template

**File:** `template.cpp`

## What it does
A ready-to-copy starting point: common typedefs (`ll`, `vi`, `pii`...), short macros (`all`, `sz`, `rep`), constants, `chmin`/`chmax`, and a **debug printer** that exists only when compiled with `-DLOCAL`.

## Why each part is there
| Part                                 | Reason                                                         |
|--------------------------------------|----------------------------------------------------------------|
| `sync_with_stdio(false)`, `cin.tie`  | Makes `cin`/`cout` about as fast as `scanf`/`printf`           |
| `solve()` + `while (T--)`            | Multi-test problems become one-line changes; `return` works as "next test" |
| `dbg(x, v)`                          | Prints names and values to **stderr**, so stdout stays clean   |
| `#ifdef LOCAL`                       | Debug code vanishes on the judge, no need to delete it         |
| `chmin` / `chmax`                    | Turns `if (b < a) a = b;` into one call (DP transitions)       |
| Timer at the end                     | Shows how close you are to the time limit locally              |

## Using the debug printer
```
dbg(n, a);          // [n, a]: 3 {1, -2, 10}
dbg(v, mp);         // works for vector, set, map, pair, nested containers
```
Compile locally with `-DLOCAL`. In CPH, add `-DLOCAL` to the compile arguments (see `workflow.md`).

## Pitfalls
- After `sync_with_stdio(false)` **do not mix** `cin/cout` with `scanf/printf`.
- `rep(i, a, b)` is half-open `[a, b)`. `per(i, a, b)` counts down from `b - 1` to `a`.
- `#define` macros with arguments are textual. Don't pass expressions with side effects (`sz(v++)`).
- `dbg` needs C++17 (it uses `enable_if` and `declval`) and does nothing without `LOCAL`.
- Printing very large containers with `dbg` inside loops makes the local run slow.
- Don't use `endl` in big outputs, it flushes every time. Use `'\n'`.
- Defining `#define int long long` hides overflow bugs but breaks `vector<int>` sizes and can slow things down. This template avoids it on purpose.
