#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;

    cin >> t;

    while (t-- > 0)
    {
        long n, k, m;

        cin >> n >> k >> m;

        if (k > m)
        {
            cout << "NO" << endl;
        }
        else
        {
            cout << "YES" << endl;

            long rest = m - k + 1;

            cout << rest;

            for (long i = 0; i < n - 1; i++)
            {
                cout << " 1";
            }

            cout << endl;
        }
    }

    return 0;
}