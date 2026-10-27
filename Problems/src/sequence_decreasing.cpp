#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;

    cin >> t;

    while (t-- > 0)
    {
        int n;

        cin >> n;

        int min = INT_MAX;

        int tmp;
        for (int i = 0; i < n; i++)
        {
            cin >> tmp;

            if (tmp < min)
                min = tmp;
        }

        if (min - (n - 1) > 0)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << n << endl;
        }
    }

    return 0;
}