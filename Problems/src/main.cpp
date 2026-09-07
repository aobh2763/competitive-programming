#include <iostream>
#include <bits/stdc++.h>

using namespace std;

bool isAlternating(string s)
{
	long long l = s.length();

	for (long long i = 0; i < l - 1; i++)
	{
		if (s.at(i) == s.at(i + 1))
		{
			return false;
		}
	}

	return true;
}

string fix(string s, long long start, int del)
{
	long long l = s.length();
}

int main()
{
	long long t;

	cin >> t;

	for (long long i = 0; i < t; i++)
	{
		long long n;

		cin >> n;

		string s;

		cin >> s;

		if (isAlternating(s))
		{
			cout << 0 << endl;
			continue;
		}

		long long zeroCount = 0, oneCount = 0;

		for (long long j = 0; j < n; j++)
		{
			if (s.at(j) == '0')
			{
				zeroCount++;
			}
			else
			{
				oneCount++;
			}
		}
		cout << zeroCount << " " << oneCount << endl;

		if (abs(zeroCount - oneCount) > 2)
		{
			cout << -1 << endl;
			continue;
		}
	}

	return 0;
}