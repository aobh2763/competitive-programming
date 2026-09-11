#include <bits/stdc++.h>

using namespace std;

bool verifyTriplet(int target, int bigger, int smaller)
{
    return (bigger - smaller) % 2 == 0;
}

int main()
{
    int t;

    cin >> t;

    while (t-- > 0)
    {
        int a, b, c;

        cin >> a >> b >> c;

        bool firstNumber = verifyTriplet(a, max(b, c), min(b, c));
        bool secondNumber = verifyTriplet(b, max(a, c), min(a, c));
        bool thirdNumber = verifyTriplet(c, max(a, b), min(a, b));

        cout << (int)firstNumber << " " << (int)secondNumber << " " << (int)thirdNumber << endl;
    }

    return 0;
}