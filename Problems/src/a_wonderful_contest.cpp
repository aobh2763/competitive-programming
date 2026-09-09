#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;

    cin >> t;

    for (int i = 0; i < t; i++)
    {
        int n;

        cin >> n;

        bool possible = false;

        for (int j = 0; j < n; j++)
        {
            int a;

            cin >> a;

            if (a == 100)
            {
                possible = true;
            }
        }

        if (possible)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }

    return 0;
}