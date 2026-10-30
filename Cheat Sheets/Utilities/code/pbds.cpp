// GNU policy-based data structures (g++ only; not on MSVC):
//  - ordered_set: a set with order_of_key (rank) and find_by_order (k-th smallest), O(log n)
//  - gp_hash_table: a faster hash table than unordered_map
// Also shows the multiset trick (store (value, unique id) pairs).
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// Set of distinct values supporting rank queries:
//   s.insert(x), s.erase(x), s.find_by_order(k) -> iterator to the k-th smallest (0-based),
//   s.order_of_key(x) -> number of elements strictly smaller than x.
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Map version: ordered_map<K, V> also supports find_by_order / order_of_key on keys.
template<class K, class V>
using ordered_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

// Multiset version: store (value, id) pairs with a fresh id per insertion.
// Count of elements < x:  ms.order_of_key({x, -1}).   Erase one copy: ms.erase(ms.lower_bound({x, -1})).
using ll = long long;
using ordered_multiset = ordered_set<pair<ll, int>>;

// Hash table with the same interface as unordered_map but usually 2-5x faster.
// Pair it with a good hash for anti-hash safety (see custom_hash in random_utils.cpp).
template<class K, class V, class H = hash<K>>
using fast_map = gp_hash_table<K, V, H>;

#ifdef LOCAL
int main() {
    ordered_set<int> s;
    for (int x : {5, 1, 9, 3}) s.insert(x);
    cout << *s.find_by_order(2) << " " << s.order_of_key(5) << "\n";   // 5 2
    ordered_multiset ms; int id = 0;
    for (int x : {4, 4, 7}) ms.insert({x, id++});
    cout << ms.order_of_key({4, -1}) << ms.order_of_key({5, -1}) << "\n";  // 02
    ms.erase(ms.lower_bound({4, -1}));
    cout << ms.size() << "\n";                                        // 2
    fast_map<int, int> mp;
    mp[3] = 9; cout << mp[3] << "\n";                                 // 9
}
#endif
