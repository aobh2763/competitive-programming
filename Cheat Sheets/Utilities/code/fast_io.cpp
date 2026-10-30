// Fast input/output with fread/fwrite. Use it only when cin/cout is too slow:
// roughly 1e6 numbers or more. Usually `ios::sync_with_stdio(false); cin.tie(nullptr);`
// is enough, and plain cin is far less error-prone.
// Do NOT mix this reader with cin/scanf in the same program.
#include <bits/stdc++.h>
using namespace std;

struct FastIn {
    static const size_t BUFSZ = 1 << 16;
    char buf[BUFSZ];
    size_t len = 0, pos = 0;

    // Next byte or -1 at end of input. Refills the buffer with one fread.
    int get() {
        if (pos == len) {
            len = fread(buf, 1, BUFSZ, stdin);
            pos = 0;
            if (len == 0) return -1;
        }
        return (unsigned char)buf[pos++];
    }

    // Read an integer (any integral type, may be negative). Returns false at EOF.
    template<class T> bool read(T& x) {
        int c = get();
        while (c != -1 && c != '-' && (c < '0' || c > '9')) c = get();
        if (c == -1) return false;
        bool neg = false;
        if (c == '-') { neg = true; c = get(); }
        x = 0;
        for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + (c - '0');
        if (neg) x = -x;
        return true;
    }

    // Read one whitespace-separated word. Returns false at EOF.
    bool read(string& s) {
        s.clear();
        int c = get();
        while (c != -1 && isspace(c)) c = get();
        if (c == -1) return false;
        for (; c != -1 && !isspace(c); c = get()) s.push_back((char)c);
        return true;
    }

    // Read a whole line (without the newline). Returns false at EOF.
    bool read_line(string& s) {
        s.clear();
        int c = get();
        if (c == -1) return false;
        for (; c != -1 && c != '\n'; c = get()) if (c != '\r') s.push_back((char)c);
        return true;
    }
};

struct FastOut {
    static const size_t BUFSZ = 1 << 16;
    char buf[BUFSZ];
    size_t pos = 0;

    // Write the buffer to stdout and empty it.
    void flush() { fwrite(buf, 1, pos, stdout); pos = 0; }

    // Append one character.
    void put(char c) { if (pos == BUFSZ) flush(); buf[pos++] = c; }

    // Append an integer (any integral type).
    template<class T> void write(T x) {
        if (x < 0) { put('-'); x = -x; }
        char tmp[24]; int n = 0;
        do { tmp[n++] = '0' + x % 10; x /= 10; } while (x);
        while (n) put(tmp[--n]);
    }

    // Append a string.
    void write(const string& s) { for (char c : s) put(c); }

    // Flushes on destruction so you cannot forget it.
    ~FastOut() { flush(); }
};

#ifdef LOCAL
int main() {
    FastIn in; FastOut out;
    int n = 0; in.read(n);
    long long s = 0;
    for (int i = 0; i < n; i++) { long long x = 0; in.read(x); s += x; }
    out.write(s); out.put('\n');            // for input "3\n1 -2 10" prints 9
}
#endif
