#include <bits/stdc++.h>

using namespace std;

int main()
{
    unordered_map<string, long long> teasToPrice;
    unordered_map<string, long long> categoriesToPrice;
    unordered_map<string, string> namesToCategories;

    long long T;

    cin >> T;

    string stmp;
    long long lltmp;

    for (int i = 0; i < T; i++)
    {
        cin >> stmp >> lltmp;

        teasToPrice[stmp] = lltmp;
    }

    cin >> lltmp;
    categoriesToPrice["SMALL"] = lltmp;
    cin >> lltmp;
    categoriesToPrice["MEDIUM"] = lltmp;
    cin >> lltmp;
    categoriesToPrice["LARGE"] = lltmp;
    cin >> lltmp;
    categoriesToPrice["SPECIAL"] = lltmp;
    cin >> lltmp;
    categoriesToPrice["DELUXE"] = lltmp;

    long long D;

    cin >> D;

    string stmp2;
    for (int i = 0; i < D; i++)
    {
        cin >> stmp >> stmp2;

        namesToCategories[stmp] = stmp2;
    }

    long long m;

    cin >> m;

    while (m-- > 0)
    {
        double total = 0.0;

        long long n, k, w;
        string t;

        cin >> n >> t >> k >> w;

        total += n * teasToPrice[t];

        for (int i = 0; i < k; i++)
        {
            cin >> stmp >> lltmp;

            total += categoriesToPrice[namesToCategories[stmp]] * lltmp;
        }

        if (w == 0)
        {
            total = total * 1.1;
        }

        cout << (long long)round(total) << "\n";
    }

    return 0;
}