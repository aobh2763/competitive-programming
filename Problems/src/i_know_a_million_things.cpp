#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;

    cin >> t;

    while (t--)
    {
        int n;

        cin >> n;

        int odds = 0;
        int evens = 0;

        int tmp;

        for (int i = 0; i < n; i++)
        {
            cin >> tmp;

            if (tmp % 2 == 0)
            {
                evens++;
            }
            else
            {
                odds++;
            }
        }

        if (odds == 1 && evens == 0)
        {
            cout << "Moggity" << endl;

            continue;
        }

        if (odds == 1 && evens == 1)
        {
            cout << "Larpity" << endl;

            continue;
        }

        if (evens == 0)
        {
            if (odds == 3)
            {
                cout << "Larpity" << endl;

                continue;
            }
            else
            {
                cout << "Moggity" << endl;

                continue;
            }
        }

        if (odds % 2 == 0)
        {
            cout << "Moggity" << endl;

            continue;
        }
        else
        {
            if (evens > 0)
            {
                cout << "Moggity" << endl;

                continue;
            }
            else
            {
                cout << "Moggity" << endl;

                continue;
            }
        }
    }

    return 0;
}