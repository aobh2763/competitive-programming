#include <bits/stdc++.h>

using namespace std;

int doubleCount(string s, int len)
{
    int index = 1;

    int count = 0;

    while (index < (len - 1))
    {
        while (index < (len - 1) && s.at(index) == 's')
        {
            index++;
        }

        if (index >= (len - 1))
        {
            break;
        }

        if (s.at(index) == 'u' && s.at(index + 1) == 'u')
        {
            count++;
            index += 2;
        }
        else
        {
            index++;
        }
    }

    return count;
}

int main()
{
    int t;

    cin >> t;

    while (t-- > 0)
    {
        string s;

        cin >> s;

        int len = s.length();

        int count = 0;

        if (s.at(0) == 'u')
        {
            s.at(0) = 's';
            count++;
        }

        if (s.at(len - 1) == 'u')
        {
            s.at(len - 1) = 's';
            count++;
        }

        count += doubleCount(s, len);

        cout << count << endl;
    }

    return 0;
}