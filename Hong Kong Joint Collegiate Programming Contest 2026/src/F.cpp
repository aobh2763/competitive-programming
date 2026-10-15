#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, q;

	cin >> n >> q;

	vector<int> v(n);

	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}

	while (q-- > 0)
	{
		int l, r;

		cin >> l >> r;
		l--;
		r--;

		if (abs(l - r) == 1)
		{
			cout << "2" << "\n";
			continue;
		}

		int firstMinIndex, secondMinIndex;
		if (v[l] < v[l + 1])
		{
			firstMinIndex = l;
			secondMinIndex = l + 1;
		}
		else
		{
			firstMinIndex = l + 1;
			secondMinIndex = l;
		}

		for (int i = l + 1; i <= r; i++)
		{
			if (v[i] < v[firstMinIndex])
			{
				secondMinIndex = firstMinIndex;
				firstMinIndex = i;
			}
			else if (v[i] < v[secondMinIndex])
			{
				secondMinIndex = i;
			}
		}
		cout << abs(firstMinIndex - secondMinIndex) + 1 << "\n";
	}

	return 0;
}