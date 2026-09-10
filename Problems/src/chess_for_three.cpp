#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;

    cin >> t;

    while (t-- > 0)
    {
        int p1, p2, p3;

        cin >> p1 >> p2 >> p3;

        int sum = p1 + p2 + p3;

        if (sum % 2 != 0)
        {
            cout << -1 << endl;
            continue;
        }

        if (p3 >= p1 + p2)
        {
            cout << p1 + p2 << endl;
        }
        else
        {
            int draws = 0;

            while (p1 + p2 > p3)
            {
                draws++;
                p1--;
                p2--;
            }

            draws += p3;

            cout << draws << endl;
        }
    }

    return 0;
}