# Policy-Based Data Structures (pb_ds)

**File:** `pbds.cpp`

## What it does
- `ordered_set<T>`: a balanced tree set with `find_by_order(k)` (k-th smallest, 0-based) and `order_of_key(x)` (how many elements are smaller than `x`).
- `ordered_multiset`: the multiset version (pairs of value and unique id).
- `ordered_map<K, V>`: the same for maps.
- `fast_map`: `gp_hash_table`, a faster `unordered_map`.

## Use it when
- You need the **k-th smallest** in a set that changes (insert and erase).
- You need the **rank** of a value in a dynamic set (count how many are smaller).
- "Count inversions online", sliding-window median, "k-th element after removals".
- You prefer not to write a Fenwick tree with coordinate compression (it is simpler, but slower).

## Complexity
All O(log n), with a larger constant than `std::set`.

## Usage
```
ordered_set<int> s;
s.insert(5); s.insert(1); s.insert(9);
*s.find_by_order(1);      // 5  (the 2nd smallest)
s.order_of_key(9);        // 2  (1 and 5 are smaller)
```

## The multiset trick
Plain `ordered_set` removes duplicates. Store `(value, id)` with a fresh `id` per insertion:
```
ordered_multiset ms; int id = 0;
ms.insert({x, id++});
ms.order_of_key({x, -1});                  // count of elements < x
ms.erase(ms.lower_bound({x, -1}));         // erase ONE copy of x
```

## Pitfalls
- It is **GCC-only** (`<ext/pb_ds/...>`). It works on Codeforces and with MSYS2 g++, not on MSVC.
- `find_by_order(k)` with `k >= size` returns `end()`. Dereferencing it is undefined.
- `order_of_key` counts **strictly smaller** elements.
- Erasing by value from a multiset version removes nothing (keys are pairs). Use the `lower_bound` pattern above.
- `gp_hash_table` has no `reserve` and is vulnerable to anti-hash tests with its default hash. Use a custom hash on hackable judges.
- Don't use it just to get a sorted set. `std::set` is faster and simpler for that.
