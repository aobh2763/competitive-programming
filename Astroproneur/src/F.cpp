#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <numeric>
#include <unordered_set>
#include <cmath>
#include <iterator>

using namespace std;

// --- Speed Optimization ---
#define FAST_IO                       \
	ios_base::sync_with_stdio(false); \
	cin.tie(NULL);

// --- Type Aliases ---
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;

// --- Macros ---
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define sz(x) ((int)(x).size())

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
	os << "[";
	for (size_t i = 0; i < v.size(); ++i)
	{
		os << v[i];
		if (i != v.size() - 1)
			os << ", ";
	}
	return os << "]";
}

// ==========================================
//             SOLVE FUNCTION
// ==========================================
void solve()
{
	int n;

	cin >> n;

	map<int, int> M = map<int, int>();

	int tmp;
	for (int i = 0; i < n; i++)
	{
		cin >> tmp;

		M[tmp]++;
	}

	int ptr = 0;

	while (M[ptr] >= 2)
	{
		ptr++;
	}

	int firstMex = ptr;

	while (M[ptr] >= 1)
	{
		ptr++;
	}

	int secondMex = ptr;

	cout << firstMex + secondMex << "\n";
}

int main()
{
	FAST_IO

	int t = 1;
	cin >> t; // Comment this out if the problem has only 1 test case
	while (t--)
	{
		solve();
	}

	return 0;
}