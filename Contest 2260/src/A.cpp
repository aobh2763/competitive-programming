#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;

	cin >> t;

	for (int i = 0; i < t; i++)
	{
		int n;

		cin >> n;

		int firstProblem, lastProblem;
		int easyCount = 0;
		int tmp;

		for (int j = 0; j < n; j++)
		{
			cin >> tmp;

			if (tmp == 0)
			{
				easyCount++;
			}

			if (j == 0)
			{
				firstProblem = tmp;
			}
			if (j == n - 1)
			{
				lastProblem = tmp;
			}
		}

		if (easyCount < 2)
		{
			cout << -1 << endl;
		}
		else
		{
			cout << firstProblem + lastProblem << endl;
		}
	}

	return 0;
}