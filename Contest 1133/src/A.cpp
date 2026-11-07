#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;

	cin >> t;

	while (t-- > 0)
	{
		int n, k;

		cin >> n >> k;

		// if k is odd, makeOdd operation
		// if k is even, makeEven operation

		int nbOddA = 0, nbOddB = 0, nbEvenA = 0, nbEvenB = 0;

		int tmp;

		for (int i = 0; i < n; i++)
		{
			cin >> tmp;

			if (tmp % 2 == 0)
			{
				nbEvenA++;
			}
			else
			{
				nbOddA++;
			}
		}

		for (int i = 0; i < n; i++)
		{
			cin >> tmp;

			if (tmp % 2 == 0)
			{
				nbEvenB++;
			}
			else
			{
				nbOddB++;
			}
		}

		if (nbOddA == nbOddB && nbEvenA == nbEvenB)
		{
			cout << "YES" << endl;

			continue;
		}

		if (k % 2 == 0)
		{
			if (nbOddA < nbOddB)
			{
				cout << "NO" << endl;
			}
			else
			{
				cout << "YES" << endl;
			}
		}
		else
		{
			if (nbEvenA < nbEvenB)
			{
				cout << "NO" << endl;
			}
			else
			{
				cout << "YES" << endl;
			}
		}
	}

	return 0;
}