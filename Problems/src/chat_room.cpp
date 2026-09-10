#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;

    cin >> s;

    bool firstH = false, firstE = false, firstL = false, secondL = false, firstO = false;

    for (char c : s)
    {
        if (!firstH)
        {
            if (c == 'h')
            {
                firstH = true;
            }
        }
        else
        {
            if (!firstE)
            {
                if (c == 'e')
                {
                    firstE = true;
                }
            }
            else
            {
                if (!firstL)
                {
                    if (c == 'l')
                    {
                        firstL = true;
                    }
                }
                else
                {
                    if (!secondL)
                    {
                        if (c == 'l')
                        {
                            secondL = true;
                        }
                    }
                    else
                    {
                        if (!firstO)
                        {
                            if (c == 'o')
                            {
                                firstO = true;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
        }
    }

    if (firstH && firstE && firstL && secondL && firstO)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    return 0;
}