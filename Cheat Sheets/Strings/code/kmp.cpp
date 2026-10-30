// KMP and the prefix function.
// pi[i] = length of the longest proper prefix of s[0..i] that is also a suffix of s[0..i]
// ("border"). Everything below is O(n) or O(n + m), fully deterministic.
#include <bits/stdc++.h>
using namespace std;

// Prefix function of s. Each step extends the previous border or falls back along shorter
// borders; amortized O(n).
vector<int> prefix_function(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int k = pi[i - 1];
        while (k > 0 && s[i] != s[k]) k = pi[k - 1];
        if (s[i] == s[k]) k++;
        pi[i] = k;
    }
    return pi;
}

// All start indices where pattern p occurs in text t (overlaps allowed). O(n + m)
// Run the prefix function on p + '#' + t: a value equal to |p| marks a match ending there.
// ('#' must not appear in either string; use another separator if it can.)
vector<int> kmp_search(const string& t, const string& p) {
    vector<int> res;
    if (p.empty()) return res;
    string s = p + '\x01' + t;
    auto pi = prefix_function(s);
    int m = p.size();
    for (int i = m + 1; i < (int)s.size(); i++)
        if (pi[i] == m) res.push_back(i - 2 * m);
    return res;
}

// Smallest p such that s[i] == s[i + p] for every valid i (so s is a prefix of the infinite
// repetition of its first p characters). = n - pi[n-1]. O(n)
int smallest_period(const string& s) {
    if (s.empty()) return 0;
    return s.size() - prefix_function(s).back();
}

// Length of the shortest string u with s = u repeated k >= 1 times (k = n / |u|).
// If s is not a whole number of repetitions of a shorter block, the answer is n. O(n)
int smallest_repeating_unit(const string& s) {
    int n = s.size();
    if (n == 0) return 0;
    int p = smallest_period(s);
    return n % p == 0 ? p : n;
}

// All border lengths of s (a border is a proper prefix that is also a suffix), descending.
// Follow the chain pi[n-1], pi[pi[n-1]-1], ... O(n)
vector<int> borders(const string& s) {
    vector<int> res;
    if (s.empty()) return res;
    auto pi = prefix_function(s);
    for (int k = pi.back(); k > 0; k = pi[k - 1]) res.push_back(k);
    return res;
}

// occ[len] (len = 1..n) = number of times the prefix of length len occurs in s as a substring.
// Count how often each pi value appears, then push counts down the border chain. O(n)
vector<int> count_prefix_occurrences(const string& s) {
    int n = s.size();
    auto pi = prefix_function(s);
    vector<int> occ(n + 1, 0);
    for (int i = 0; i < n; i++) occ[pi[i]]++;
    for (int i = n - 1; i > 0; i--) occ[pi[i - 1]] += occ[i];
    for (int i = 1; i <= n; i++) occ[i]++;                 // each prefix occurs at its own position
    return occ;
}

#ifdef LOCAL
int main() {
    for (int x : prefix_function("abacabab")) cout << x << " ";   // 0 0 1 0 1 2 3 2
    cout << "\n";
    for (int i : kmp_search("abababa", "aba")) cout << i << " ";  // 0 2 4
    cout << "\n" << smallest_period("abcabcab") << " " << smallest_repeating_unit("abcabc")
         << " " << smallest_repeating_unit("abcab") << "\n";      // 3 3 5
    for (int b : borders("abaaba")) cout << b << " ";             // 3 1
    cout << "\n";
    auto occ = count_prefix_occurrences("aaaa");
    cout << occ[1] << occ[2] << occ[3] << occ[4] << "\n";         // 4321
}
#endif
