#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;

	cin >> t;

	while (t-- > 0)
	{
		int n;

		cin >> n;

		int zeroCount = 0;
		int oneCount = 0;

		int tmp;

		for (int i = 0; i < n; i++)
		{
			cin >> tmp;

			if (tmp == 0)
			{
				zeroCount++;
			}
			else
			{
				oneCount++;
			}
		}

		if (oneCount >= zeroCount)
		{
			cout << "Bessie" << endl;
		}
		else
		{
			cout << "Elsie" << endl;
		}
	}

	return 0;
}