#include <bits/stdc++.h>

using namespace std;

int countPossiblePairs(vector<int> a, int n, int start, bool increase)
{
	int possible = 0;

	for (int i = start; i < n - 1; i += 2)
	{
		if (increase)
		{
			if (a[i] == -1 && a[i] == a[i + 1])
			{
				possible++;
			}
		}
		else
		{
			if (a[i] == 1 && a[i] == a[i + 1])
			{
				possible++;
			}
		}
	}

	return possible;
}

int main()
{
	int t;

	cin >> t;

	for (int i = 0; i < t; i++)
	{
		int n;
		cin >> n;

		vector<int> a(n);
		int sum = 0;

		for (int j = 0; j < n; j++)
		{
			cin >> a[j];
			sum += a[j];
		}

		if (n % 2 == 1)
		{
			cout << "NO" << endl;
			continue;
		}

		if (sum == 0)
		{
			cout << "YES" << endl;
			continue;
		}

		if (sum % 4 != 0)
		{
			cout << "NO" << endl;
			continue;
		}

		bool increase = false;
		if (sum < 0)
		{
			increase = true;
			sum = -sum;
		}

		int possibleFromZero = countPossiblePairs(a, n, 0, increase);
		if (sum - possibleFromZero * 4 < 0)
		{
			cout << "YES" << endl;
			continue;
		}

		int possibleFromOne = countPossiblePairs(a, n, 1, increase);
		if (sum - possibleFromOne * 4 < 0)
		{
			cout << "YES" << endl;
			continue;
		}

		cout << "NO" << endl;
	}

	return 0;
}