// Sequence DP on one or two strings/arrays:
//  LCS (with the actual subsequence), edit distance, longest palindromic subsequence,
//  longest common substring, LIS with reconstruction.
// The first four are O(n * m) (or O(n^2)); LIS is O(n log n).
#include <bits/stdc++.h>
using namespace std;

// Longest common SUBSEQUENCE of a and b (characters in order, gaps allowed), returned as
// a string. dp[i][j] = LCS length of a[0..i) and b[0..j). O(n * m) time and memory.
string lcs(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = a[i - 1] == b[j - 1] ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);
    string res;
    for (int i = n, j = m; i > 0 && j > 0;) {           // walk back through the table
        if (a[i - 1] == b[j - 1]) { res.push_back(a[i - 1]); i--; j--; }
        else if (dp[i - 1][j] >= dp[i][j - 1]) i--;
        else j--;
    }
    reverse(res.begin(), res.end());
    return res;
}

// Edit (Levenshtein) distance: fewest insert / delete / replace operations turning a into b.
// dp[i][j] = distance between a[0..i) and b[0..j). Uses two rows. O(n * m) time, O(m) memory.
int edit_distance(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<int> prev(m + 1), cur(m + 1);
    iota(prev.begin(), prev.end(), 0);                  // turning "" into b[0..j) costs j
    for (int i = 1; i <= n; i++) {
        cur[0] = i;
        for (int j = 1; j <= m; j++)
            cur[j] = min({prev[j] + 1,                  // delete a[i-1]
                          cur[j - 1] + 1,               // insert b[j-1]
                          prev[j - 1] + (a[i - 1] != b[j - 1])});  // replace / match
        swap(prev, cur);
    }
    return prev[m];
}

// Length of the longest palindromic SUBSEQUENCE of s.
// dp[i][j] for the window s[i..j]: equal ends add 2, else drop one end. O(n^2)
int longest_palindromic_subsequence(const string& s) {
    int n = s.size();
    if (n == 0) return 0;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = 1;
        for (int j = i + 1; j < n; j++)
            dp[i][j] = s[i] == s[j] ? dp[i + 1][j - 1] + 2 : max(dp[i + 1][j], dp[i][j - 1]);
    }
    return dp[0][n - 1];
}

// Length of the longest common SUBSTRING (contiguous) of a and b.
// dp[i][j] = length of the common suffix ending at a[i-1], b[j-1]. O(n * m), O(m) memory.
int longest_common_substring(const string& a, const string& b) {
    int n = a.size(), m = b.size(), best = 0;
    vector<int> prev(m + 1, 0), cur(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cur[j] = a[i - 1] == b[j - 1] ? prev[j - 1] + 1 : 0;
            best = max(best, cur[j]);
        }
        swap(prev, cur);
    }
    return best;
}

// One longest strictly increasing subsequence, returned as INDICES in increasing order.
// Patience sorting keeps the index of the smallest possible tail for each length, plus a
// predecessor pointer for every element. O(n log n)
template<class T>
vector<int> lis_indices(const vector<T>& a) {
    int n = a.size();
    vector<int> tails, prev(n, -1);                     // tails[k] = index of best tail of length k+1
    for (int i = 0; i < n; i++) {
        int lo = 0, hi = tails.size();
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (a[tails[mid]] < a[i]) lo = mid + 1; else hi = mid;
        }
        if (lo > 0) prev[i] = tails[lo - 1];
        if (lo == (int)tails.size()) tails.push_back(i); else tails[lo] = i;
    }
    vector<int> res;
    for (int i = tails.empty() ? -1 : tails.back(); i != -1; i = prev[i]) res.push_back(i);
    reverse(res.begin(), res.end());
    return res;
}

#ifdef LOCAL
int main() {
    cout << lcs("AGGTAB", "GXTXAYB") << "\n";                      // GTAB
    cout << edit_distance("kitten", "sitting") << "\n";            // 3
    cout << longest_palindromic_subsequence("bbbab") << "\n";      // 4
    cout << longest_common_substring("abcdef", "zcdemf") << "\n";  // 3 ("cde")
    vector<int> a = {10, 9, 2, 5, 3, 7, 101, 18};
    for (int i : lis_indices(a)) cout << a[i] << " ";              // 2 3 7 18
    cout << "\n";
}
#endif
