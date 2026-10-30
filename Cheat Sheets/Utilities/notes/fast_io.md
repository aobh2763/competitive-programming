# Fast I/O

**File:** `fast_io.cpp`

## What it does
`FastIn` reads integers, words and lines through a 64 KB `fread` buffer. `FastOut` collects output in a buffer and writes it with `fwrite`.

## Use it when
- The input has more than about **1e6 numbers** and `cin` with `sync_with_stdio(false)` is still too slow.
- You hit a TLE with the I/O as the bottleneck (profile first).

For almost every problem, `ios::sync_with_stdio(false); cin.tie(nullptr);` is enough. Prefer that.

## Usage
```
FastIn in; FastOut out;
int n; in.read(n);
for (int i = 0; i < n; i++) { long long x; in.read(x); out.write(x); out.put('\n'); }
```
`FastOut` flushes by itself when it goes out of scope, so output is never lost at the end of `main`.

## Pitfalls
- **Don't mix** `FastIn` with `cin`, `scanf` or `getline` in the same program: each keeps its own buffer.
- `read(x)` and `read(string&)` consume the **one character after** the token (the delimiter). So after reading a number, `read_line` returns the **next** line, not the rest of the current one.
- `read_line` strips a trailing `\r` (Windows line endings) but nothing else.
- Doubles are not supported. Read them as a string and convert, or use `cin`.
- Returns `false` at end of input, so `while (in.read(x))` works for unknown-length input.
- Interactive problems need flushing after each answer, so `FastOut` is **not** suitable there.
