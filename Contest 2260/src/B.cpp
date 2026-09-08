#include <bits/stdc++.h>

using namespace std;

int main()
{
    long t;

    cin >> t;

    for (long i = 0; i < t; i++)
    {
        long long x, y, k;

        cin >> x >> y >> k;

        long long res = 0;
        long long d = y - x;
        long long j = 0;

        while (k > 0 && (x + j) <= d)
        {
            res += d % (x + j);

            j++;
            k--;
        }

        res += d * k;

        cout << res << endl;
    }
}