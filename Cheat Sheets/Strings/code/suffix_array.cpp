// Suffix array + LCP array.
//  suffix_array: indices of all suffixes in sorted order. O(n log n) (prefix doubling with
//                counting sort).
//  lcp_array:    Kasai's algorithm, LCP of neighbouring suffixes in sorted order. O(n)
// Uses: count distinct substrings, find all occurrences of a pattern, longest repeated
// substring, longest common substring of two strings (concatenate with a separator).
// The string must not contain the character '\0'.
#include <bits/stdc++.h>
using namespace std;

// Sorts the CYCLIC shifts of s (s must end with a unique smallest character), by doubling:
// after round h the classes order shifts by their first 2^h characters.
vector<int> sort_cyclic_shifts(const string& s) {
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++) cnt[(unsigned char)s[i]]++;
    for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[(unsigned char)s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]]) classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; h++) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
            if (cur != prev) classes++;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

// Suffix array of s: sa[k] = start of the k-th smallest suffix. Appends a sentinel '\0'
// (smaller than every character) so cyclic shifts order like suffixes, then drops it. O(n log n)
vector<int> suffix_array(string s) {
    s.push_back('\0');
    auto p = sort_cyclic_shifts(s);
    p.erase(p.begin());
    return p;
}

// Kasai: lcp[k] = longest common prefix of suffixes sa[k] and sa[k+1] (size n - 1).
// Key fact: moving from suffix i to i+1 the LCP drops by at most 1, so k only needs
// decrementing once per step. O(n)
vector<int> lcp_array(const string& s, const vector<int>& sa) {
    int n = s.size();
    vector<int> rank(n), lcp(max(n - 1, 0));
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    for (int i = 0, k = 0; i < n; i++) {
        if (rank[i] == n - 1) { k = 0; continue; }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rank[i]] = k;
        if (k) k--;
    }
    return lcp;
}

// Number of distinct non-empty substrings: all n(n+1)/2 substrings minus the duplicates,
// which are exactly the sum of the LCP array. O(n log n)
long long count_distinct_substrings(const string& s) {
    long long n = s.size();
    auto lcp = lcp_array(s, suffix_array(s));
    long long total = n * (n + 1) / 2;
    for (int x : lcp) total -= x;
    return total;
}

// Range [lo, hi) of positions in `sa` whose suffixes start with pattern p, by binary search.
// Occurrences are sa[lo], ..., sa[hi-1]. O(|p| log n)
pair<int, int> find_occurrences(const string& s, const vector<int>& sa, const string& p) {
    int n = s.size(), m = p.size();
    auto less_than = [&](int pos) { return s.compare(pos, m, p) < 0; };       // suffix < pattern
    auto greater_than = [&](int pos) { return s.compare(pos, m, p) > 0; };    // suffix (first m chars) > pattern
    int lo = partition_point(sa.begin(), sa.begin() + n, less_than) - sa.begin();
    int hi = partition_point(sa.begin() + lo, sa.begin() + n, [&](int pos) { return !greater_than(pos); }) - sa.begin();
    return {lo, hi};
}

// Longest substring that occurs at least twice (possibly overlapping): max of the LCP array.
string longest_repeated_substring(const string& s) {
    auto sa = suffix_array(s);
    auto lcp = lcp_array(s, sa);
    int best = 0, at = 0;
    for (int i = 0; i < (int)lcp.size(); i++) if (lcp[i] > best) { best = lcp[i]; at = sa[i]; }
    return s.substr(at, best);
}

#ifdef LOCAL
int main() {
    string s = "banana";
    auto sa = suffix_array(s);
    for (int x : sa) cout << x << " ";                                   // 5 3 1 0 4 2
    cout << "\n";
    for (int x : lcp_array(s, sa)) cout << x << " ";                     // 1 3 0 0 2
    cout << "\n" << count_distinct_substrings(s) << "\n";                 // 15
    auto [lo, hi] = find_occurrences(s, sa, "ana");
    cout << hi - lo << ":"; for (int k = lo; k < hi; k++) cout << " " << sa[k]; cout << "\n";   // 2: 3 1
    cout << longest_repeated_substring(s) << "\n";                       // ana
}
#endif
