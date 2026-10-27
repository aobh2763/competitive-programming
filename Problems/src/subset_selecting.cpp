#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t = 0;

    cin >> t;

    while (t-- > 0)
    {
        int n, k;

        cin >> n >> k;

        bool isZeroPresent = false;

        int tmp;
        map<int, int> M = map<int, int>();
        for (int i = 0; i < n; i++)
        {
            cin >> tmp;

            M[tmp]++;
        }

        int ptr = 0;

        while (M[ptr] > 0)
        {
            int t = 0;

            int toFill = k - 1;
            M[ptr]--;

            while (t <= ptr && toFill > 0)
            {
                int willTake = min(toFill, M[t]);

                M[t] -= willTake;
                toFill -= willTake;

                t++;
            }

            if (toFill > 0)
                break;

            ptr++;
        }

        if (ptr > (n / k))
        {
            ptr = n / k;
        }

        cout << ptr << endl;
    }

    return 0;
}