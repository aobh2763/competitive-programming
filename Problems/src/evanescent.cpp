#include <bits/stdc++.h>

using namespace std;

int compressedLength(string s, int originalLength)
{
    int compressedLength = 0;
    char previousChar = '0';

    for (int i = 0; i < originalLength; i++)
    {
        while (i < originalLength && s.at(i) == previousChar)
        {
            i++;
        }

        if (i < originalLength)
        {
            previousChar = s.at(i);
            compressedLength++;
        }
    }

    return compressedLength;
}

int consecutiveLength(string s, int length, int index)
{
    if (s.at(index - 1) != s.at(index + 1))
    {
        return 1;
    }

    if (s.at(index) == s.at(index - 1) && s.at(index) == s.at(index + 1))
    {
        return -1;
    }

    int pre = index - 1, post = index + 1;
    char target = s.at(index - 1);

    int consecutiveLength = 0;

    while (pre >= 0 && s.at(pre) == target)
    {
        consecutiveLength++;
        pre--;
    }

    while (post < length && s.at(post) == target)
    {
        consecutiveLength++;
        post++;
    }

    return consecutiveLength;
}

int firstUnhelpfulIndex(string s, int length)
{
    int index = 1;

    while (index < length - 1)
    {
        if (s.at(index) != s.at(index - 1) && s.at(index) != s.at(index + 1))
        {
            return index;
        }

        index++;
    }

    return 1;
}

int main()
{
    int t;

    cin >> t;

    while (t-- > 0)
    {
        int n;
        string s;

        cin >> n;
        cin >> s;

        int maxConsecutiveLength = 1;
        int maxConsecutiveIndex = 1;

        for (int i = 1; i < n - 1; i++)
        {
            int currConsectiveLength = consecutiveLength(s, n, i);

            if (currConsectiveLength > maxConsecutiveLength)
            {
                maxConsecutiveIndex = i;
                maxConsecutiveLength = currConsectiveLength;
            }
        }

        if (maxConsecutiveIndex == 1)
        {
            maxConsecutiveIndex = firstUnhelpfulIndex(s, n);
        }

        s.erase(maxConsecutiveIndex, 1);

        cout << compressedLength(s, n - 1) << endl;
    }

    return 0;
}