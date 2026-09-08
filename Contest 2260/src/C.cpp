#include <bits/stdc++.h>

using namespace std;

long getLargestPowerOfTwo(long number)
{
    if (number == 0)
        return 0;

    long power = 1;

    while (power * 2 <= number)
        power *= 2;

    return power;
}

int main()
{
    int t;

    cin >> t;

    for (int i = 0; i < t; i++)
    {
        long x, y;

        cin >> x >> y;

        long max = x + y;

        long ops = 0;

        long p = getLargestPowerOfTwo(max);

        if (p >= y)
        {
            ops = p - y;
        }

        cout << max << " " << ops << endl;
    }

    return 0;
}
