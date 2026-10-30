// Lyndon words and cyclic rotations.
// A Lyndon word is strictly smaller than all of its proper suffixes (equivalently, smaller
// than all its rotations). Every string splits uniquely into a NON-INCREASING sequence of
// Lyndon words (Duval's algorithm, O(n)). The same idea finds the lexicographically smallest
// rotation of a string, which is the canonical form for "are these two necklaces equal?".
#include <bits/stdc++.h>
using namespace std;

// Duval's algorithm: the Lyndon factorization of s as a list of words w1 >= w2 >= ... >= wk
// with s = w1 w2 ... wk. O(n) time, O(1) extra memory besides the output.
vector<string> duval(const string& s) {
    int n = s.size();
    vector<string> res;
    for (int i = 0; i < n;) {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) k = i; else k++;
            j++;
        }
        while (i <= k) {
            res.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return res;
}

// Start index of the lexicographically smallest rotation of s (the smallest such index if
// there are ties). Duval on s + s. O(n)
int min_rotation_index(const string& s) {
    int n = s.size();
    if (n == 0) return 0;
    string d = s + s;
    int i = 0, ans = 0;
    while (i < n) {
        ans = i;
        int j = i + 1, k = i;
        while (j < 2 * n && d[k] <= d[j]) {
            if (d[k] < d[j]) k = i; else k++;
            j++;
        }
        while (i <= k) i += j - k;
    }
    return ans;
}

// The smallest rotation itself.
string min_rotation(const string& s) {
    int i = min_rotation_index(s);
    return s.substr(i) + s.substr(0, i);
}

// Are a and b rotations of each other (the same necklace)? Compare canonical forms. O(n)
bool same_necklace(const string& a, const string& b) {
    return a.size() == b.size() && min_rotation(a) == min_rotation(b);
}

#ifdef LOCAL
int main() {
    for (auto& w : duval("banana")) cout << w << " ";                    // b an an a
    cout << "\n" << min_rotation("cabab") << " " << min_rotation_index("cabab") << "\n";   // ababc 1
    cout << same_necklace("abcde", "cdeab") << same_necklace("abc", "acb") << "\n";   // 10
}
#endif
