#include <bits/stdc++.h>

using namespace std;

long calculateMedian(vector<long> v)
{
	if (v.empty())
	{
		return 0l;
	}

	long n = v.size();

	if (n % 2 != 0)
	{
		auto mid = v.begin() + n / 2;
		nth_element(v.begin(), mid, v.end());
		return (long)(*mid);
	}
	else
	{
		auto mid2 = v.begin() + n / 2;
		auto mid1 = mid2 - 1;

		nth_element(v.begin(), mid2, v.end());
		long val2 = *mid2;

		nth_element(v.begin(), mid1, mid2);
		long val1 = *mid1;

		return min(val1, val2);
	}
}

vector<long> flatten(vector<vector<long>> matrix)
{
	vector<long> flattened;

	long total_size = 0;
	for (const auto &row : matrix)
	{
		total_size += row.size();
	}
	flattened.reserve(total_size);

	for (const auto &row : matrix)
	{
		flattened.insert(flattened.end(), row.begin(), row.end());
	}

	return flattened;
}

int main()
{
	int n, m;
	long k;

	cin >> n >> m >> k;

	vector<vector<long>> M = vector<vector<long>>(n, vector<long>(m));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> M[i][j];
		}
	}

	return 0;
}