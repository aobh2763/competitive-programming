#include <bits/stdc++.h>

using namespace std;

int getSign(long a)
{
    return a / abs(a);
}

int main()
{
    int t;

    cin >> t;

    while (t-- > 0)
    {
        long n;

        cin >> n;

        int currentSign = 0;
        long switchCount = 0;
        long a;

        vector<long> operations(0);

        cin >> a;

        currentSign = getSign(a);

        for (long i = 1; i < n; i++)
        {
            cin >> a;

            if (getSign(a) != currentSign)
            {
                currentSign = getSign(a);

                switchCount++;

                operations.push_back(i);
            }
        }

        if (currentSign > 0)
        {
            switchCount++;

            operations.push_back(n);
        }

        if (switchCount == 0)
        {
            cout << switchCount;
        }
        else
        {
            cout << switchCount << endl
                 << operations[switchCount - 1];
        }

        for (int i = 1; i < switchCount; i++)
        {
            cout << " " << operations[switchCount - i - 1];
        }

        cout << endl;
    }

    return 0;
}