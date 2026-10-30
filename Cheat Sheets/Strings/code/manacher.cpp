// Manacher's algorithm: all palindromic substrings in O(n).
//  d1[i] = number of odd-length palindromes centred at i  (radius, counting the single char)
//  d2[i] = number of even-length palindromes centred between i-1 and i
// From these: longest palindromic substring, count of palindromic substrings, and an O(1)
// test "is s[l..r] a palindrome?".
#include <bits/stdc++.h>
using namespace std;

struct Manacher {
    string s;
    vector<int> d1, d2;

    // Compute d1 and d2 by reusing the mirror of the rightmost palindrome found so far. O(n)
    Manacher(const string& s) : s(s) {
        int n = s.size();
        d1.assign(n, 0); d2.assign(n, 0);
        for (int i = 0, l = 0, r = -1; i < n; i++) {                 // odd
            int k = i > r ? 1 : min(d1[l + r - i], r - i + 1);
            while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
            d1[i] = k;
            if (i + k - 1 > r) { l = i - k + 1; r = i + k - 1; }
        }
        for (int i = 0, l = 0, r = -1; i < n; i++) {                 // even
            int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
            while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
            d2[i] = k;
            if (i + k - 1 > r) { l = i - k; r = i + k - 1; }
        }
    }

    // Is s[l..r] (inclusive) a palindrome? O(1)
    bool is_palindrome(int l, int r) const {
        int len = r - l + 1;
        if (len % 2) return d1[(l + r) / 2] >= (len + 1) / 2;
        return d2[(l + r + 1) / 2] >= len / 2;
    }

    // Number of palindromic substrings (counted by position, so "aaa" has 6). O(n)
    long long count_palindromes() const {
        long long total = 0;
        for (int x : d1) total += x;
        for (int x : d2) total += x;
        return total;
    }

    // The longest palindromic substring (first one found among ties). O(n)
    string longest() const {
        int n = s.size(), best = 0, start = 0;
        for (int i = 0; i < n; i++) {
            if (2 * d1[i] - 1 > best) { best = 2 * d1[i] - 1; start = i - d1[i] + 1; }
            if (2 * d2[i] > best)     { best = 2 * d2[i];     start = i - d2[i]; }
        }
        return s.substr(start, best);
    }
};

#ifdef LOCAL
int main() {
    Manacher m("abacaba");
    cout << m.longest() << " " << m.count_palindromes() << "\n";   // abacaba 12
    cout << m.is_palindrome(0, 6) << m.is_palindrome(1, 3) << m.is_palindrome(0, 1) << "\n";   // 100
    Manacher e("abba");
    cout << e.longest() << " " << e.count_palindromes() << "\n";   // abba 6
}
#endif
