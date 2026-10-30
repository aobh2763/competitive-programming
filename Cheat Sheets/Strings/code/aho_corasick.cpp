// Aho-Corasick automaton: search for MANY patterns in a text at once.
// Build a trie of the patterns, add "suffix links" (failure links) with BFS, and turn it into
// a full automaton so the text is processed one character at a time in O(1) each.
// Build O(total pattern length * 26), scan O(|text|), plus O(nodes) to push counts down links.
// Lowercase letters a-z only (change ALPHA otherwise).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct AhoCorasick {
    static const int ALPHA = 26;
    struct Node {
        int go[ALPHA];      // transition (after build(): full automaton, never -1)
        int link = 0;       // longest proper suffix that is also a trie prefix
        Node() { fill(go, go + ALPHA, -1); }
    };
    vector<Node> t;
    vector<int> end_node;   // end_node[id] = trie node where pattern `id` ends
    vector<int> bfs_order;

    // Automaton with only the root.
    AhoCorasick() : t(1) {}

    // Add a pattern; returns its id (0, 1, 2, ... in insertion order). O(|p|)
    int add(const string& p) {
        int v = 0;
        for (char ch : p) {
            int c = ch - 'a';
            if (t[v].go[c] == -1) { t[v].go[c] = t.size(); t.emplace_back(); }
            v = t[v].go[c];
        }
        end_node.push_back(v);
        return end_node.size() - 1;
    }

    // Compute failure links and complete the transitions with BFS. Call after all add()s.
    // link(child) = go[link(parent)][c]; missing transitions copy the link's transition.
    void build() {
        bfs_order.clear();
        queue<int> q;
        for (int c = 0; c < ALPHA; c++) {
            if (t[0].go[c] == -1) t[0].go[c] = 0;
            else { t[t[0].go[c]].link = 0; q.push(t[0].go[c]); }
        }
        while (!q.empty()) {
            int v = q.front(); q.pop();
            bfs_order.push_back(v);
            for (int c = 0; c < ALPHA; c++) {
                int u = t[v].go[c];
                if (u == -1) t[v].go[c] = t[t[v].link].go[c];
                else { t[u].link = t[t[v].link].go[c]; q.push(u); }
            }
        }
    }

    // occ[id] = number of occurrences of pattern id in text (overlaps counted).
    // Run the automaton, count visits per node, then add each node's count to its suffix link
    // in reverse BFS order (a visit to a node is also a visit to all its suffix-link ancestors).
    vector<ll> count_occurrences(const string& text) const {
        vector<ll> visits(t.size(), 0);
        int v = 0;
        for (char ch : text) { v = t[v].go[ch - 'a']; visits[v]++; }
        for (int i = (int)bfs_order.size() - 1; i >= 0; i--) {
            int u = bfs_order[i];
            visits[t[u].link] += visits[u];
        }
        vector<ll> occ(end_node.size());
        for (size_t id = 0; id < end_node.size(); id++) occ[id] = visits[end_node[id]];
        return occ;
    }

    // Does the text contain at least one pattern? O(|text|) given the built automaton.
    bool contains_any(const string& text) const {
        vector<char> terminal(t.size(), 0);
        for (int e : end_node) terminal[e] = 1;
        vector<char> bad(t.size(), 0);                    // node whose suffix-link chain hits a terminal
        for (int u : bfs_order) bad[u] = terminal[u] || bad[t[u].link];
        int v = 0;
        for (char ch : text) { v = t[v].go[ch - 'a']; if (bad[v] || terminal[v]) return true; }
        return false;
    }
};

#ifdef LOCAL
int main() {
    AhoCorasick ac;
    for (string p : {"he", "she", "his", "hers"}) ac.add(p);
    ac.build();
    auto occ = ac.count_occurrences("ushers");
    for (ll x : occ) cout << x << " ";                                   // 1 1 0 1
    cout << "\n" << ac.contains_any("xyz") << ac.contains_any("ahistory") << "\n";   // 01
}
#endif
