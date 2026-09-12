#include <bits/stdc++.h>

using namespace std;

void fillMatrix(vector<vector<int>> &matrix, int n, int diags)
{
	int p = 1;

	for (int i = 0; i < diags; i++)
	{
		matrix[i][i] = p;
		p++;
	}

	int i = 0, j = 0;

	while (p <= n * n)
	{
		if (matrix[i][j] == 0)
		{
			matrix[i][j] = p;
			p++;
		}

		j++;

		if (j == n)
		{
			j = 0;
			i++;
		}
	}
}

void printMatrix(vector<vector<int>> matrix, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << matrix[i][j] << " ";
		}

		cout << endl;
	}
}

int main()
{
	int t;

	cin >> t;

	while (t-- > 0)
	{
		int n, k;

		cin >> n >> k;

		if (k < n)
		{
			cout << -1 << endl;
			continue;
		}

		if (k - n >= n)
		{
			cout << -1 << endl;
			continue;
		}

		int diags = k - n;

		vector<vector<int>> matrix = vector<vector<int>>(n, vector<int>(n, 0));

		fillMatrix(matrix, n, n - diags);

		printMatrix(matrix, n);
	}

	return 0;
}

/*
3 5
k - n = 2
n - k + n = 1
1 2 3
4 5 6
7 8 9

3 3
k - n = 0
n - k + n = 3
1 4 5
6 2 7
8 9 3

3 4
k - n = 1
n - k + n =
1 2 4
5 6 7
8 9 3
*/