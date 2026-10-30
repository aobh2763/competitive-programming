// Z-function: z[i] = length of the longest common prefix of s and the suffix s[i..].
// (z[0] is set to n by convention.) O(n), deterministic, and often easier to reason about
// than the prefix function. Equivalent power: pattern matching, periods, borders.
#include <bits/stdc++.h>
using namespace std;

// Z-array of s. Keep the rightmost matched window [l, r) and reuse it to skip comparisons,
// so every character is compared at most once more: O(n).
vector<int> z_function(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    if (n == 0) return z;
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    return z;
}

// All start positions where p occurs in t. Z-function of p + sep + t; a value >= |p| is a
// match. O(n + m). The separator must not appear in either string.
vector<int> z_search(const string& t, const string& p) {
    vector<int> res;
    if (p.empty()) return res;
    string s = p + '\x01' + t;
    auto z = z_function(s);
    int m = p.size();
    for (int i = m + 1; i < (int)s.size(); i++)
        if (z[i] >= m) res.push_back(i - m - 1);
    return res;
}

// Smallest period of s: the smallest p >= 1 with p + z[p] == n (or n if there is none).
// Note: this is the "borderline" period, not necessarily dividing n. O(n)
int smallest_period_z(const string& s) {
    int n = s.size();
    auto z = z_function(s);
    for (int p = 1; p < n; p++) if (p + z[p] == n) return p;
    return n;
}

// Sum over all suffixes of their LCP with s (a standard "how similar are the suffixes to s"
// quantity). O(n).
long long sum_of_z(const string& s) {
    long long total = 0;
    for (int v : z_function(s)) total += v;
    return total;
}

#ifdef LOCAL
int main() {
    for (int x : z_function("aabxaab")) cout << x << " ";         // 7 1 0 0 3 1 0
    cout << "\n";
    for (int i : z_search("abababa", "aba")) cout << i << " ";    // 0 2 4
    cout << "\n" << smallest_period_z("abcabcab") << " " << sum_of_z("aaa") << "\n";   // 3 6
}
#endif
