#include <bits/stdc++.h>

using namespace std;

int main()
{
	int T;

	cin >> T;

	while (T-- > 0)
	{
		int a, b, c;

		cin >> a >> b >> c;

		int firstMax, secondMax;

		if (a >= b && a >= c)
		{
			firstMax = a;
			if (b >= c)
			{
				secondMax = b;
			}
			else
			{
				secondMax = c;
			}
		}
		else if (b >= c && b >= a)
		{
			firstMax = b;
			if (a >= c)
			{
				secondMax = a;
			}
			else
			{
				secondMax = c;
			}
		}
		else
		{
			firstMax = c;
			if (a >= b)
			{
				secondMax = a;
			}
			else
			{
				secondMax = b;
			}
		}

		cout << firstMax * secondMax << "\n";
	}

	return 0;
}