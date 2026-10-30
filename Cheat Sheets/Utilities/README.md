# Common Utilities Cheat Sheet

Each `.cpp` file has a matching `.md` with the "when and why". Start with `template` and `workflow`.

## What is where?

| I need to...                                                         | Use                         | File |
|----------------------------------------------------------------------|-----------------------------|------|
| Start every problem from a clean base (typedefs, debug printer)      | Contest template            | `template` |
| Read/write millions of numbers quickly                               | fread/fwrite I/O            | `fast_io` |
| Generate random tests, random trees/graphs, safe `unordered_map`     | RNG + generators + hash     | `random_utils` |
| Find a boundary ("smallest x such that..."), minimize a unimodal fn  | Binary / ternary search     | `binary_search` |
| Compress values, prefix sums, nearest greater, window max, LIS       | Array utilities             | `array_utils` |
| Bitmasks, submasks, SOS DP, XOR basis                                | Bit tricks                  | `bit_tricks` |
| Split, trim, RLE, base conversion                                    | String helpers              | `string_utils` |
| k-th smallest in a dynamic set, rank of a value                      | pb_ds ordered set           | `pbds` |
| Compile flags, sanitizers, CPH, VS Code setup                        | Workflow                    | `workflow.md` |

## Contest-day checklist

1. **Read the constraints first** and pick the complexity (see the table in `trees/README.md`).
2. **Use `long long`** whenever a sum or product can exceed ~2e9.
3. **Reset everything between test cases** (arrays, vectors, adjacency lists, global counters).
4. **Check indexing:** 0-based vs 1-based, inclusive vs half-open ranges.
5. **Test the samples**, then the smallest and largest cases (n = 1, all equal, already sorted, maximum values).
6. **Print with `'\n'`, not `endl`**, in large outputs.

## Bugs that cost the most time

| Symptom                              | Usual cause                                                     |
|--------------------------------------|-----------------------------------------------------------------|
| Wrong on big input only              | Integer overflow (`int` instead of `long long`, `1 << 40`)      |
| Wrong on the 2nd test case           | Missing reset between tests                                     |
| Random crash / garbage               | Out-of-bounds index, uninitialized variable                     |
| TLE with a correct idea              | `endl`, `cin` without `sync_with_stdio(false)`, O(n) inside a loop |
| Different answers locally vs judge   | Undefined behavior (uninitialized values, signed overflow)      |
| `a % m` is negative                  | C++ keeps the sign: use `((a % m) + m) % m`                     |
| Precision errors                     | Comparing doubles with `==`; use an epsilon or integers         |
