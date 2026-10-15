#include <bits/stdc++.h>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;

	cin >> T;

	while (T-- > 0)
	{
		int n;

		cin >> n;

		unordered_set<long long> s = unordered_set<long long>();
		s.reserve(n * 2);

		for (int i = 0; i < n; i++)
		{
			long long a;

			cin >> a;

			while (s.count(a))
			{
				a++;
			}

			s.insert(a);

			cout << a << " ";
		}

		cout << "\n";
	}

	return 0;
}