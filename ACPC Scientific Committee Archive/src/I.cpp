#include <bits/stdc++.h>

using namespace std;

int maxMex = 0;
int maxLength = 1;

int calculateMex(vector<int> &v, int start, int end)
{
    int mex = 0;

    while (find(v.begin() + start, v.begin() + end + 1, mex) != (v.begin() + end + 1))
    {
        mex++;
    }

    return mex;
}

void check(vector<int> &v, int N, bool cameFromStart, int start, int end, set<int> uniques, int prevMex)
{
    if (uniques.find(v[start]) != uniques.end() && cameFromStart)
    {
        return;
    }

    if (uniques.find(v[end]) != uniques.end() && !cameFromStart)
    {
        return;
    }

    int currMex;

    if (prevMex == v[start] || prevMex == v[end])
    {
        currMex = calculateMex(v, start, end);

        if (currMex >= maxMex)
        {
            maxMex = currMex;
            maxLength = max(maxLength, end - start + 1);
        }
    }
    else
    {
        currMex = prevMex;

        if (currMex >= maxMex)
        {
            maxMex = currMex;
            maxLength = max(maxLength, end - start + 1);
        }
    }

    uniques.insert(v[start]);
    uniques.insert(v[end]);

    if (start > 0)
    {
        check(v, N, true, start - 1, end, uniques, currMex);
    }

    if (end < N - 1)
    {
        check(v, N, false, start, end + 1, uniques, currMex);
    }
}

int main()
{
    int N;

    cin >> N;

    vector<int> v(N);

    for (int i = 0; i < N; i++)
    {
        cin >> v[i];
    }

    bool hasZero = false;

    for (int i = 0; i < N; i++)
    {
        if (v[i] == 0)
        {
            hasZero = true;
            check(v, N, true, i, i, set<int>(), 0);
        }
    }

    if (hasZero)
    {
        cout << maxLength << endl;
    }
    else
    {
        cout << N << endl;
    }

    return 0;
}