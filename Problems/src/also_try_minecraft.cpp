#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<long long> world(n);
    vector<long long> right(n, 0);
    vector<long long> left(n, 0);

    for (auto &x : world)
        cin >> x;

    for (int i = 1; i < n; i++)
    {
        right[i] = right[i - 1] + max(0LL, world[i - 1] - world[i]);
        left[i] = left[i - 1] + max(0LL, world[i] - world[i - 1]);
    }

    while (m--)
    {
        int from, to;
        cin >> from >> to;

        from--;
        to--;

        if (from < to)
            cout << right[to] - right[from] << '\n';
        else
            cout << left[from] - left[to] << '\n';
    }

    return 0;
}