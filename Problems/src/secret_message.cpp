
#include <bits/stdc++.h>

using namespace std;

vector<map<char, int>> getLetterMap(vector<string> v, int vectorLength, int stringLength)
{
    vector<map<char, int>> M(stringLength);

    for (int j = 0; j < stringLength; j++)
    {
        for (int i = 0; i < vectorLength; i++)
        {
            M[j][v[i][j]]++;
        }
    }

    return M;
}

int main()
{
    int t;
    cin >> t;

    while (t-- > 0)
    {
        int n, k;
        cin >> n >> k;

        vector<string> v(k);

        for (int i = 0; i < k; i++)
        {
            cin >> v[i];
        }

        vector<map<char, int>> letterMap = getLetterMap(v, k, n);

        for (int d = 1; d <= n; d++)
        {
            if (n % d != 0)
            {
                continue;
            }

            string str = "";
            bool solFound = true;

            for (int j = 0; j < d; j++)
            {
                bool foundMatch = false;

                for (char c = 'a'; c <= 'z'; c++)
                {
                    bool valid = true;

                    for (int pos = j; pos < n; pos += d)
                    {
                        if (letterMap[pos][c] == 0)
                        {
                            valid = false;
                            break;
                        }
                    }

                    if (valid)
                    {
                        str += c;
                        foundMatch = true;
                        break;
                    }
                }

                if (!foundMatch)
                {
                    solFound = false;
                    break;
                }
            }

            if (solFound)
            {
                for (int i = 0; i < n / d; i++)
                {
                    cout << str;
                }

                cout << '\n';
                break;
            }
        }
    }

    return 0;
}
