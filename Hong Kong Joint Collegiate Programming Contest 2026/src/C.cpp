#include <bits/stdc++.h>

using namespace std;

int &getElement(tuple<int, int, int> &t, int index)
{
	return index == 0	? get<0>(t)
		   : index == 1 ? get<1>(t)
						: get<2>(t);
}

int main()
{
	int T;

	cin >> T;

	while (T-- > 0)
	{
		int a, b, c;

		cin >> a >> b >> c;

		int firstMax, secondMax, thirdMax;
		int firstMaxIndex, secondMaxIndex, thirdMaxIndex;

		if (a >= b && a >= c)
		{
			firstMax = a;
			firstMaxIndex = 0;
			if (b >= c)
			{
				secondMax = b;
				thirdMax = c;

				secondMaxIndex = 1;
				thirdMaxIndex = 2;
			}
			else
			{
				secondMax = c;
				thirdMax = b;

				secondMaxIndex = 2;
				thirdMaxIndex = 1;
			}
		}
		else if (b >= c && b >= a)
		{
			firstMax = b;
			firstMaxIndex = 1;
			if (a >= c)
			{
				secondMax = a;
				thirdMax = c;

				secondMaxIndex = 0;
				thirdMaxIndex = 2;
			}
			else
			{
				secondMax = c;
				thirdMax = a;

				secondMaxIndex = 2;
				thirdMaxIndex = 0;
			}
		}
		else
		{
			firstMax = c;
			firstMaxIndex = 2;
			if (a >= b)
			{
				secondMax = a;
				thirdMax = b;

				secondMaxIndex = 0;
				thirdMaxIndex = 1;
			}
			else
			{
				secondMax = b;
				thirdMax = a;

				secondMaxIndex = 1;
				thirdMaxIndex = 0;
			}
		}

		int total = firstMax * secondMax;

		vector<vector<tuple<int, int, int>>> S(
			firstMax,
			vector<tuple<int, int, int>>(secondMax, tuple<int, int, int>()));

		for (int i = 0; i < firstMax; i++)
		{
			for (int j = 0; j < secondMax; j++)
			{
				getElement(S[i][j], secondMaxIndex) = j + 1;
				getElement(S[i][j], firstMaxIndex) = i + 1;
			}
		}

		for (int j = 0; j < secondMax; j++)
		{
			int start = j + 1;
			for (int i = 0; i < firstMax; i++)
			{
				if (start <= thirdMax)
				{
					getElement(S[i][j], thirdMaxIndex) = start;
				}
				else
				{
					getElement(S[i][j], thirdMaxIndex) = 1;
				}
				start++;

				if (start > secondMax)
				{
					start = 1;
				}
			}
		}

		cout << total << endl;

		for (int i = 0; i < firstMax; i++)
		{
			for (int j = 0; j < secondMax; j++)
			{
				cout << get<0>(S[i][j]) << " " << get<1>(S[i][j]) << " " << get<2>(S[i][j]) << "\n";
			}
		}
	}

	return 0;
}

/*
2 3 4

(1, 1, 1), (2, 1, 2), (3, 1, x), (4, 1, x),
(1, 2, x), (2, 2, x), (3, 2, x), (4, 2, x),
(1, 3, x), (2, 3, x), (3, 3, x), (4, 3, x),

3 2 3

(1, 1, 1), (1, 2, 2), (1, x, 3),
(2, 2, 1), (2, x, 2), (2, 1, 3),
(3, x, 1), (3, 1, 2), (3, 2, 3)

4 3 4

(1, 1, 1), (1, 2, 2), (1, 3, 3), (1, x, 4),
(2, 2, 1), (2, 3, 2), (2, x, 3), (2, 1, 4),
(3, 3, 1), (3, x, 2), (3, 1, 3), (3, 2, 4),
(4, x, 1), (4, 1, 2), (4, 2, 3), (4, 3, 4)

4 4 4

(1, 1, 1), (1, 2, 2), (1, 3, 3), (1, 4, 4),
(2, 1, 2), (2, 2, 3), (2, 3, 4), (2, 4, 1),
(3, 1, 3), (3, 2, 4), (3, 3, 2), (3, 4, 3),
(4, 1, 4), (4, 2, 1), (4, 3, 1), (4, 4, 2)

2 2 6
(1, 1, x), (1, 2, x),
(2, 1, x), (2, 2, x),
(3, 1, x), (3, 2, x),
(4, 1, x), (4, 2, x),
(5, 1, x), (5, 2, x),
(6, 1, x), (6, 2, x)
*/