# Array Utilities

**File:** `array_utils.cpp`

## What it does
| Function / struct                          | Purpose                                              | Time        |
|--------------------------------------------|------------------------------------------------------|-------------|
| `compress`                                 | Replace values with their rank (0..k-1)              | O(n log n)  |
| `prefix_sums`                              | Range sums of a 1D array                             | O(n), query O(1) |
| `Prefix2D`                                 | Rectangle sums of a grid                             | O(RC), query O(1) |
| `Diff2D`                                   | Add to a whole rectangle in O(1), build at the end   | O(RC)       |
| `next_greater` / `next_smaller`            | Nearest larger/smaller element to the right          | O(n)        |
| `prev_greater` / `prev_smaller`            | Nearest larger/smaller element to the left           | O(n)        |
| `sliding_window_max`                       | Max of each window of size k                         | O(n)        |
| `lis_length`                               | Longest increasing subsequence                       | O(n log n)  |
| `count_inversions`                         | Pairs `i < j` with `a[i] > a[j]`                     | O(n log n)  |
| `kadane`                                   | Maximum subarray sum                                 | O(n)        |

## Use it when
- Values are huge but only their **order** matters (feed them to a Fenwick tree): compress.
- Many range-sum queries on a static array or grid: prefix sums.
- Many range **updates** then one read of the final array: difference array.
- "For each element, find the next/previous bigger one", histograms, stock-span style problems: monotonic stack.
- "Max of every window", DP optimization with a deque: sliding window.
- Counting inversions is also the number of adjacent swaps bubble sort needs.

## Tricks
- **Difference array (1D):** to add `v` on `[l, r]`: `d[l] += v; d[r+1] -= v`; at the end take the prefix sum.
- **Sum of subarray minimums:** for each element, use `prev_smaller` and `next_smaller` to count the subarrays where it is the minimum: `(i - prev) * (next - i) * a[i]`. (Break ties consistently, e.g. strict on one side, non-strict on the other.)
- **Largest rectangle in a histogram:** the width for bar `i` is `next_smaller[i] - prev_smaller[i] - 1`.
- **LIS reconstruction** needs extra arrays (predecessor indices), not just the length.
- **Sliding window min:** negate the values, call `sliding_window_max`, negate the result.

## Pitfalls
- `prefix_sums` has size `n + 1`: sum of `a[l..r]` is `P[r+1] - P[l]`.
- `Prefix2D::query` bounds are **inclusive** and 0-indexed.
- `next_greater` etc. use **strict** comparisons: equal elements are skipped. Adjust for "greater or equal" problems.
- `lis_length(a, strict)`: pass `false` for non-decreasing.
- `count_inversions` takes the array **by value** and sorts the copy.
- `kadane` assumes a non-empty array and returns the best non-empty subarray (negative if all are negative).
- `compress` modifies the vector in place and returns the sorted distinct values.
