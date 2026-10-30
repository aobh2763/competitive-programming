// Digit DP: count numbers x in [0, N] (or [L, R]) whose DIGITS satisfy some property.
// Build the number digit by digit from the most significant one, remembering only a small
// "state" (digit sum, last digit, remainder mod K, ...). O(digits * states * 10).
// You supply:   init state, step(state, digit, started) -> new state (or -1 to reject),
//               accept(state) -> does a finished number count?
// `started` is false while only leading zeros have been placed, so that "007" is just "7".
// Consequence: the number 0 has NO digits at all (it is all leading zeros), so step() is never
// called with started = true for it and accept(init) decides whether 0 counts.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DigitDP {
    int S;                                   // number of states (0 .. S-1)
    int init;                                // starting state
    function<int(int, int, bool)> step;      // (state, digit, started_after) -> state or -1
    function<bool(int)> accept;              // final state accepted?

    // Count x in [0, N] accepted by the automaton (N >= 0, base 10).
    // Memoised on (position, state, started) for the "not tight" branches; a number is
    // "tight" while its digits so far equal the prefix of N (so the next digit is capped).
    ll count_upto(ll N) const {
        if (N < 0) return 0;
        string s = to_string(N);
        int L = s.size();
        vector<vector<array<ll, 2>>> memo(L + 1, vector<array<ll, 2>>(S, {-1, -1}));
        function<ll(int, int, bool, bool)> go = [&](int pos, int st, bool tight, bool started) -> ll {
            if (pos == L) return accept(st) ? 1 : 0;
            if (!tight && memo[pos][st][started] != -1) return memo[pos][st][started];
            int lim = tight ? s[pos] - '0' : 9;
            ll res = 0;
            for (int d = 0; d <= lim; d++) {
                bool ns_started = started || d != 0;
                int ns = step(st, d, ns_started);
                if (ns < 0) continue;
                res += go(pos + 1, ns, tight && d == lim, ns_started);
            }
            if (!tight) memo[pos][st][started] = res;
            return res;
        };
        return go(0, init, true, false);
    }

    // Count x in [L, R]. Handles L = 0.
    ll count_range(ll L, ll R) const { return count_upto(R) - count_upto(L - 1); }
};

// Example 1: numbers in [0, N] whose digit sum is divisible by K. State = digit sum mod K.
ll count_digit_sum_divisible(ll N, int K) {
    DigitDP dp{K, 0,
               [K](int st, int d, bool) { return (st + d) % K; },
               [](int st) { return st == 0; }};
    return dp.count_upto(N);
}

// Example 2: numbers in [0, N] with NO two equal adjacent digits (0 counts).
// State = last digit + 1, or 0 when nothing has been placed yet (leading zeros).
ll count_no_adjacent_equal(ll N) {
    DigitDP dp{11, 0,
               [](int st, int d, bool started) {
                   if (!started) return 0;                   // still in leading zeros
                   if (st == d + 1) return -1;               // same as the previous digit
                   return d + 1;
               },
               [](int) { return true; }};
    return dp.count_upto(N);
}

#ifdef LOCAL
int main() {
    cout << count_digit_sum_divisible(100, 5) << "\n";             // 20 (0, 5, 14, 19, 23, ..., 96)
    cout << count_no_adjacent_equal(100) << "\n";                  // 91 (101 numbers minus 11,22,...,99 and 100)
    DigitDP even_digit_count{2, 0,
        [](int st, int d, bool started) { return started ? st ^ (d % 2 == 0) : st; },   // parity of # even digits
        [](int st) { return st == 1; }};
    cout << even_digit_count.count_range(10, 99) << "\n";          // 2-digit numbers with an odd number of even digits: 45
}
#endif
