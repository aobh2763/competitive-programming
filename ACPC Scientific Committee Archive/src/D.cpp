#include <bits/stdc++.h>

using namespace std;

long sumMatrix(vector<vector<int>> &prefix, int fromX, int fromY, int toX, int toY)
{
	return prefix[toX + 1][toY + 1] - prefix[fromX][toY + 1] - prefix[toX + 1][fromY] + prefix[fromX][fromY];
}

bool possible(vector<vector<int>> &prefix, int startX, int startY, int size)
{
	if (size == 0)
	{
		return true;
	}

	long sum = sumMatrix(prefix, startX, startY, startX + size - 1, startY + size - 1);

	if (size % 2 == 0)
	{
		return (sum >= ((size * size) / 2));
	}
	else
	{
		return (sum >= (((size * size) / 2) + 1));
	}
}

bool possibleSize(vector<vector<int>> &prefix, int n, int m, int size)
{
	int itersX = n - size + 1;
	int itersY = m - size + 1;

	for (int i = 0; i < itersX; i++)
	{
		for (int j = 0; j < itersY; j++)
		{
			if (possible(prefix, i, j, size))
			{
				return true;
			}
		}
	}

	return false;
}

int main()
{
	int n, m;
	long k;

	cin >> n >> m >> k;

	vector<vector<int>> v = vector<vector<int>>(n, vector<int>(m));

	long tmp;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> tmp;

			if (tmp <= k)
			{
				v[i][j] = 1;
			}
			else
			{
				v[i][j] = 0;
			}
		}
	}

	vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			prefix[i][j] = v[i - 1][j - 1] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
		}
	}

	int minSize = 0;
	int maxSize = min(n, m);

	while (minSize <= maxSize)
	{
		int middleSize = (minSize + maxSize) / 2;

		if (possibleSize(prefix, n, m, middleSize))
		{
			minSize = middleSize + 1;
		}
		else
		{
			maxSize = middleSize - 1;
		}
	}

	cout << maxSize * maxSize << endl;

	return 0;
}