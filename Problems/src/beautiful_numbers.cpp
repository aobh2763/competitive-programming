#include <bits/stdc++.h>

using namespace std;

map<char, int> calculateDigits(long long x)
{
    map<char, int> digits = {
        {'+', 0}, // The untouchable first number (for the sum)
        {'1', 0},
        {'2', 0},
        {'3', 0},
        {'4', 0},
        {'5', 0},
        {'6', 0},
        {'7', 0},
        {'8', 0},
        {'9', 0},
        {'0', 0}};

    int digit;

    while (x / 10ll != 0)
    {
        digit = x % 10ll;

        digits[(char)('0' + digit)]++;

        x = x / 10ll;
    }

    digits['+'] = x;

    return digits;
}

int main()
{
    int t;

    cin >> t;

    while (t-- > 0)
    {
        long long x;

        cin >> x;

        map<char, int> digits = calculateDigits(x);

        int sum = digits['+'] + 0 * digits['0'] + 1 * digits['1'] + 2 * digits['2'] + 3 * digits['3'] + 4 * digits['4'] + 5 * digits['5'] + 6 * digits['6'] + 7 * digits['7'] + 8 * digits['8'] + 9 * digits['9'];

        digits[(char)('0' + (digits['+'] - 1))]++;

        int moves = 0;
        int current = 9;

        while (sum > 9)
        {
            while (digits[(char)('0' + current)] == 0)
            {
                current--;
            }

            digits[(char)('0' + current)]--;

            sum -= current;

            moves++;
        }

        cout << moves << endl;
    }

    return 0;
}