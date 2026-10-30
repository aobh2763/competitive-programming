# Workflow: Compiling, Debugging, Local Setup

Your setup (VS Code, g++ via MSYS2, CPH, C++17/20) works well. This is how to get the most out of it.

## Compile commands

| Purpose            | Command                                                                       |
|--------------------|-------------------------------------------------------------------------------|
| Like the judge     | `g++ -std=c++17 -O2 sol.cpp -o sol`                                           |
| Debug build        | `g++ -std=c++17 -g -Wall -Wextra -Wshadow -DLOCAL -D_GLIBCXX_DEBUG sol.cpp -o sol` |
| With sanitizers    | add `-fsanitize=address,undefined` (Linux/WSL)                                |
| Bigger stack       | add `-Wl,--stack=268435456` (Windows/MinGW; Codeforces gives a large stack)   |

What the flags do:
- `-Wall -Wextra -Wshadow`: warnings that catch real bugs (unused or uninitialized variables, shadowed names, sign comparisons).
- `-D_GLIBCXX_DEBUG`: makes `vector`, `string`, etc. check bounds and iterator validity, and crash with a message instead of silent corruption.
- `-fsanitize=address,undefined`: catches out-of-bounds, use-after-free and signed overflow with a stack trace. **AddressSanitizer is generally not available for MinGW GCC on Windows**, so use it under Linux or WSL, and on Windows rely on `-D_GLIBCXX_DEBUG` (if the compiler rejects the sanitizer flags, just drop them).
- `-DLOCAL`: enables the `dbg(...)` printer from `template.cpp`.

## Running with files
```
sol.exe < in.txt > out.txt          (Windows)
./sol < in.txt > out.txt            (Linux / MSYS2 bash)
```
To time it in PowerShell: `Measure-Command { .\sol.exe < in.txt > out.txt }`.

## CPH (Competitive Programming Helper) tips
- In its settings, add `-DLOCAL` (and `-D_GLIBCXX_DEBUG` if you like) to the **C++ compilation arguments** so your debug printer and bounds checks run locally. The judge never sees those flags.
- Add your own failing cases with "Add testcase". It keeps them next to the problem.

## VS Code snippet for the template
`File > Preferences > Configure Snippets > cpp`. Create an entry whose `body` is the lines of `template.cpp`:
```
{
  "Contest template": {
    "prefix": "tmpl",
    "body": [ "#include <bits/stdc++.h>", "using namespace std;", "...rest of template.cpp, one string per line..." ]
  }
}
```
Typing `tmpl` then inserts the whole template.

## When your solution is wrong: a routine
1. Re-read the statement, check the constraints and edge cases (n = 1, empty, all equal, max values).
2. Compile with the debug flags and run the samples. Warnings and `_GLIBCXX_DEBUG` often point straight at the bug.
3. Add `dbg(...)` prints on small inputs and compare to what you computed by hand.
4. If it is TLE, estimate the operation count, and check for `endl`, `vector` copies passed by value, and `O(n)` work inside loops.

## Pitfalls
- A program that "works on my machine" but fails on the judge usually has **undefined behavior** (uninitialized variables, out-of-bounds, signed overflow). Debug flags and sanitizers exist to expose it.
- Don't leave `-D_GLIBCXX_DEBUG` on when measuring speed. It makes containers much slower.
- Windows and Linux differ: `long double`, `%lld` formats, stack size and `rand()` behave differently. Prefer `cin/cout` and `mt19937`.
