#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long t;

    cin >> t;

    for (long long i = 0; i < t; i++)
    {
        long long n;

        cin >> n;

        vector<long long> a = vector<long long>(n);
        vector<long long> b = vector<long long>(n);

        for (long long j = 0; j < n; j++)
        {
            cin >> a[j];
        }

        for (long long j = 0; j < n; j++)
        {
            cin >> b[j];
        }

        for (long long k = n - 1; k > 0; k--)
        {
            if (a[k] < b[k])
            {
                a[k] = b[k];
            }
            else if (a[k] > b[k])
            {
                a[k - 1] = a[k - 1] + (a[k] - b[k]);
                a[k] = b[k];
            }
        }

        if (a[0] > b[0])
        {
            cout << "NO" << endl;
        }
        else
        {
            cout << "YES" << endl;
        }
    }

    return 0;
}