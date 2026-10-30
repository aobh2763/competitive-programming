// Small string helpers: split / join / trim, case conversion, run-length encoding,
// base conversion, subsequence and palindrome checks.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Split s on a single delimiter character. Keeps empty pieces ("a,,b" -> {"a","","b"}).
vector<string> split(const string& s, char delim) {
    vector<string> res;
    string cur;
    for (char c : s) {
        if (c == delim) { res.push_back(cur); cur.clear(); }
        else cur.push_back(c);
    }
    res.push_back(cur);
    return res;
}

// Split on any whitespace, skipping empty pieces ("  a  b " -> {"a","b"}).
vector<string> split_ws(const string& s) {
    vector<string> res;
    istringstream in(s);
    for (string w; in >> w;) res.push_back(w);
    return res;
}

// Join pieces with a separator.
string join(const vector<string>& parts, const string& sep) {
    string r;
    for (size_t i = 0; i < parts.size(); i++) { if (i) r += sep; r += parts[i]; }
    return r;
}

// Remove leading and trailing whitespace.
string trim(const string& s) {
    size_t l = 0, r = s.size();
    while (l < r && isspace((unsigned char)s[l])) l++;
    while (r > l && isspace((unsigned char)s[r - 1])) r--;
    return s.substr(l, r - l);
}

// Lower-case / upper-case copy (ASCII).
string to_lower(string s) { for (auto& c : s) c = tolower((unsigned char)c); return s; }
string to_upper(string s) { for (auto& c : s) c = toupper((unsigned char)c); return s; }

// Run-length encode: "aaabcc" -> {('a',3), ('b',1), ('c',2)}. O(n)
vector<pair<char, int>> rle(const string& s) {
    vector<pair<char, int>> res;
    for (char c : s) {
        if (!res.empty() && res.back().first == c) res.back().second++;
        else res.push_back({c, 1});
    }
    return res;
}

// Write n >= 0 in base b (2..36) using digits 0-9 and a-z. to_base(0, b) = "0".
string to_base(ll n, int b) {
    if (n == 0) return "0";
    string r;
    for (; n > 0; n /= b) r.push_back("0123456789abcdefghijklmnopqrstuvwxyz"[n % b]);
    reverse(r.begin(), r.end());
    return r;
}

// Parse a base-b (2..36) string (digits 0-9, a-z or A-Z) into an integer.
ll from_base(const string& s, int b) {
    ll r = 0;
    for (char c : s) r = r * b + (isdigit((unsigned char)c) ? c - '0' : tolower(c) - 'a' + 10);
    return r;
}

// True if t is a subsequence of s (characters in order, not necessarily adjacent). O(|s|)
bool is_subsequence(const string& t, const string& s) {
    size_t j = 0;
    for (size_t i = 0; i < s.size() && j < t.size(); i++) if (s[i] == t[j]) j++;
    return j == t.size();
}

// True if s reads the same forwards and backwards.
bool is_palindrome(const string& s) { return equal(s.begin(), s.begin() + s.size() / 2, s.rbegin()); }

#ifdef LOCAL
int main() {
    cout << join(split("a,,b", ','), "|") << "\n";             // a||b
    cout << split_ws("  x   y ").size() << "[" << trim("  hi \n") << "]\n";  // 2[hi]
    cout << to_upper("abC") << to_lower("ABc") << "\n";        // ABCabc
    for (auto [c, k] : rle("aaabcc")) cout << c << k;          // a3b1c2
    cout << "\n" << to_base(255, 16) << " " << from_base("ff", 16) << "\n";   // ff 255
    cout << is_subsequence("ace", "abcde") << is_palindrome("level") << "\n"; // 11
}
#endif
