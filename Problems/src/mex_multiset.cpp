#include <bits/stdc++.h>

using namespace std;

/*
0: (count, indexes)
1: (count, [0, 2, ...])
*/

int main()
{
    int t;

    cin >> t;

    while (t-- > 0)
    {
        long n;

        cin >> n;

        map<long, pair<long, vector<long>>> numberCountIndexes;

        for (int i = 0; i < n; i++)
        {
            long tmp;

            cin >> tmp;

            if (numberCountIndexes.count(tmp) == 0)
            {
                numberCountIndexes[tmp] = pair<long, vector<long>>(1, vector<long>(1, i));
            }
            else
            {
                numberCountIndexes[tmp].first++;
                numberCountIndexes[tmp].second.push_back(i);
            }
        }

        if (numberCountIndexes[0].first == 0)
        {
            cout << "YES" << endl;

            vector<char> res(n, 'C');
            for (char c : res)
            {
                cout << c;
            }

            cout << endl;

            continue;
        }

        long maxDualMex = 0;

        while (numberCountIndexes[maxDualMex].first >= 2)
        {
            maxDualMex++;
        }

        if (maxDualMex == 0)
        {
            if (numberCountIndexes[0].first > 0)
            {
                cout << "NO" << endl;
                continue;
            }
        }

        // shove all the 0s
        // shove everything else in C

        vector<char> res(n, 'C');

        long lastIndex;

        for (long index : numberCountIndexes[0].second)
        {
            res[index] = 'A';
            lastIndex = index;
        }

        res[lastIndex] = 'B';

        cout << "YES" << endl;
        for (char c : res)
        {
            cout << c;
        }
        cout << endl;
    }

    return 0;
}