#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long t;

    cin >> t;

    for (long long i = 0; i < t; i++)
    {
        long long x, y;

        cin >> x >> y;

        if (y > x)
        {
            cout << "NO" << endl;
            continue;
        }

        if (x % y == 0)
        {
            cout << "YES" << endl;
            continue;
        }

        cout << "NO" << endl;
    }

    return 0;
}