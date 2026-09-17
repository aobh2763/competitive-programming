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

        map<int, int> numbersToPlaces;

        int tmp;
        for (int i = 0; i < n; i++)
        {
            cin >> tmp;

            numbersToPlaces.insert(pair<int, int>(tmp, i + 1));
        }

        double center = -1;
        bool possible = true;

        for (int number = 1; number <= n; number++)
        {
            int index = numbersToPlaces[number];

            if (numbersToPlaces[index] != number)
            {
                cout << "NO" << endl;
                possible = false;

                break;
            }

            if (index == number)
            {
                continue;
            }

            if (center != -1 && center != ((index + number) / 2))
            {
                cout << "NO" << endl;
                possible = false;

                break;
            }
            else
            {
                center = (index + number) / 2;
            }
        }

        if (possible)
        {
            cout << "YES" << endl;
        }
    }

    return 0;
}
