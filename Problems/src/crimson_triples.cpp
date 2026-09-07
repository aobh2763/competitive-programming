#include <bits/stdc++.h>

using namespace std;

/*
Have n
For n + 1

Add to n:
(n + 1, x, x)
(x, x, n + 1) THE SAME AS ABOVE
(x, n + 1, x)
(n + 1, n + 1, x)
(x, n + 1, n + 1) THE SAME AS ABOVE
(n + 1, x, n + 1)
(n + 1, n + 1, n + 1)
*/

long getGcdOrCalculate(vector<vector<long>> &gctable, long a, long b)
{
    if (gctable[a][b] != -1)
    {
        return gctable[a][b];
    }

    long res = gcd(a, b);

    gctable[a][b] = res;
    gctable[b][a] = res;

    return res;
}

bool test(vector<vector<long>> &gctable, long a, long b, long c)
{
    long ab = getGcdOrCalculate(gctable, a, b);
    long ac = getGcdOrCalculate(gctable, a, c);
    long bc = getGcdOrCalculate(gctable, b, c);

    long left = abs(b) * getGcdOrCalculate(gctable, abs(a) / ab, abs(c) / bc);

    return (left == ac);
}

long calculateCrimson(vector<vector<long>> &gctable, vector<long> &crimsons, long n)
{
    if (n == 1)
        return 1;

    if (crimsons[n] != -1)
        return crimsons[n];

    long res = calculateCrimson(gctable, crimsons, n - 1);

    for (long x = 1; x < n; x++)
    {
        for (long y = 1; y < n; y++)
        {
            if (test(gctable, n, x, y))
                res++;
            if (test(gctable, x, n, y))
                res++;
            if (test(gctable, x, y, n))
                res++;
        }
    }

    for (long x = 1; x < n; x++)
    {
        if (test(gctable, n, n, x))
            res++;
        if (test(gctable, n, x, n))
            res++;
        if (test(gctable, x, n, n))
            res++;
    }

    if (test(gctable, n, n, n))
        res++;

    crimsons[n] = res;
    return res;
}

int main()
{
    int t;

    cin >> t;

    vector<long> cases(t);

    long max = 0;
    for (int i = 0; i < t; i++)
    {
        cin >> cases[i];

        if (max < cases[i])
        {
            max = cases[i];
        }
    }

    vector<vector<long>> gctable(max + 1, vector<long>(max + 1, -1));

    vector<long> crimsons(max + 1, -1);

    for (int i = 1; i <= max; i++)
    {
        crimsons[i] = calculateCrimson(gctable, crimsons, i);
    }

    for (int cas = 0; cas < t; cas++)
    {
        long n = cases[cas];

        cout << crimsons[n] << endl;
    }

    return 0;
}