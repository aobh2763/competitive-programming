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

		int reply, oneCount;

		cout << "? " << 1 << " " << n << endl;
		fflush(stdout);

		cin >> reply;
		oneCount = reply;

		if (reply == 0)
		{
			cout << "! NO" << endl;
			fflush(stdout);

			continue;
		}
		else if (reply == n)
		{
			cout << "! NO" << endl;
			fflush(stdout);

			continue;
		}

		cout << "? " << 1 << " " << 1 << endl;
		fflush(stdout);

		cin >> reply;

		if (reply == 0)
		{
			cout << "! YES" << endl;
			fflush(stdout);

			continue;
		}

		cout << "? " << n << " " << n << endl;
		fflush(stdout);

		cin >> reply;

		if (reply == 1)
		{
			cout << "! YES" << endl;
			fflush(stdout);

			continue;
		}

		cout << "? " << oneCount + 1 << " " << n << endl;
		fflush(stdout);

		cin >> reply;

		if (reply == 0)
		{
			cout << "! NO" << endl;
			fflush(stdout);
		}
		else
		{
			cout << "! YES" << endl;
			fflush(stdout);
		}
	}

	return 0;
}

// bad: 111100000
// we need 01

// all of them, first and last

// all of them 1 -> no
// all of them 0 -> no
// discrepency -> continue, there are k ones

// first is 0 -> yes
// first is 1 -> continue

// last is 1 -> yes
// last is 0 -> continue

// from k + 1 to end
// all 0s -> no
// there is a one -> yes