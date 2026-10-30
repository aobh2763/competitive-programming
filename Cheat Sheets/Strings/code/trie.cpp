// Tries (prefix trees):
//  - Trie: lowercase words with insert / erase / exact count / prefix count / longest prefix
//  - XorTrie: binary trie of integers for "max XOR with any stored number"
// Every operation is O(length of the word) (O(bits) for the XOR trie).
#include <bits/stdc++.h>
using namespace std;

struct Trie {
    struct Node {
        int next[26];
        int pass = 0, end = 0;      // words passing through this node / words ending here
        Node() { memset(next, -1, sizeof(next)); }
    };
    vector<Node> t;

    // Empty trie (just the root).
    Trie() : t(1) {}

    // Insert word w (lowercase a-z). Duplicates are counted. O(|w|)
    void insert(const string& w) {
        int v = 0;
        t[0].pass++;                                  // the root counts every word (empty prefix)
        for (char ch : w) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) { t[v].next[c] = t.size(); t.emplace_back(); }
            v = t[v].next[c];
            t[v].pass++;
        }
        t[v].end++;
    }

    // Walk the path of w; returns the node reached, or -1 if it leaves the trie. O(|w|)
    int find_node(const string& w) const {
        int v = 0;
        for (char ch : w) {
            v = t[v].next[ch - 'a'];
            if (v == -1) return -1;
        }
        return v;
    }

    // How many times the exact word w was inserted. O(|w|)
    int count(const string& w) const {
        int v = find_node(w);
        return v == -1 ? 0 : t[v].end;
    }

    // How many inserted words start with prefix p. O(|p|)
    int count_prefix(const string& p) const {
        int v = find_node(p);
        return v == -1 ? 0 : t[v].pass;
    }

    // Remove ONE copy of w if present. Returns true if something was removed. O(|w|)
    // (Nodes are not freed, only their counters change.)
    bool erase(const string& w) {
        if (count(w) == 0) return false;
        int v = 0;
        t[0].pass--;
        for (char ch : w) { v = t[v].next[ch - 'a']; t[v].pass--; }
        t[v].end--;
        return true;
    }

    // Length of the longest prefix of w that is a prefix of some stored word. O(|w|)
    int longest_common_prefix(const string& w) const {
        int v = 0, len = 0;
        for (char ch : w) {
            int nx = t[v].next[ch - 'a'];
            if (nx == -1 || t[nx].pass == 0) break;
            v = nx; len++;
        }
        return len;
    }
};

// Binary trie over B-bit non-negative integers (default 30 bits: values < 2^30).
struct XorTrie {
    int B;
    vector<array<int, 2>> ch;       // children
    vector<int> cnt;                // how many stored numbers pass through each node

    // Empty trie for numbers below 2^bits.
    XorTrie(int bits = 30) : B(bits), ch(1, {-1, -1}), cnt(1, 0) {}

    // Insert x (can be inserted several times). O(B)
    void insert(long long x) {
        int v = 0;
        for (int b = B - 1; b >= 0; b--) {
            int bit = x >> b & 1;
            if (ch[v][bit] == -1) { ch[v][bit] = ch.size(); ch.push_back({-1, -1}); cnt.push_back(0); }
            v = ch[v][bit];
            cnt[v]++;
        }
    }

    // Remove one copy of x, which must have been inserted. O(B)
    void erase(long long x) {
        int v = 0;
        for (int b = B - 1; b >= 0; b--) { v = ch[v][x >> b & 1]; cnt[v]--; }
    }

    // max over stored y of (x XOR y); the trie must not be empty. Greedy: at every bit prefer
    // the child that differs from x's bit. O(B)
    long long max_xor(long long x) const {
        int v = 0;
        long long res = 0;
        for (int b = B - 1; b >= 0; b--) {
            int bit = x >> b & 1, want = bit ^ 1;
            int nx = ch[v][want];
            if (nx != -1 && cnt[nx] > 0) { res |= 1LL << b; v = nx; }
            else v = ch[v][bit];
        }
        return res;
    }
};

#ifdef LOCAL
int main() {
    Trie t;
    for (string w : {"apple", "app", "apple", "bat"}) t.insert(w);
    cout << t.count("apple") << t.count("app") << t.count("ap") << "\n";   // 210
    cout << t.count_prefix("ap") << t.count_prefix("b") << t.count_prefix("") << "\n";   // 314
    t.erase("apple");
    cout << t.count("apple") << " " << t.longest_common_prefix("applesauce") << "\n";   // 1 5
    XorTrie x;
    for (int v : {3, 10, 5, 25, 2, 8}) x.insert(v);
    cout << x.max_xor(5) << "\n";                                           // 28 (5 ^ 25)
}
#endif
