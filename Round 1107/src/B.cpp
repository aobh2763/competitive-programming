#include <bits/stdc++.h>

using namespace std;

int numberOfDigits(long long k)
{
    int i = 0;
    while (k > 0)
    {
        k /= 10;
        i++;
    }
    return i;
}

int main()
{
    long long t;

    cin >> t;

    for (long long i = 0; i < t; i++)
    {
        long long x, y;

        cin >> x;

        y = pow(10, numberOfDigits(x)) + 1;

        cout << y << endl;
    }

    return 0;
}