#include <bits/stdc++.h>

using namespace std;

int mtiMFirstCorrespondence = 0;
int mtiTFirstCorrespondence = 0;
int mtiIFirstCorrespondence = 0;

int mitMFirstCorrespondence = 0;
int mitIFirstCorrespondence = 0;
int mitTFirstCorrespondence = 0;

void updateMitCorrespondence(char c, int i)
{
	switch (c)
	{
	case 'm':
		if (i % 3 == 0)
		{
			mtiMFirstCorrespondence++;
			mitMFirstCorrespondence++;
		}
		else if (i % 3 == 1)
		{
			mtiIFirstCorrespondence++;
			mitTFirstCorrespondence++;
		}
		else if (i % 3 == 2)
		{
			mtiTFirstCorrespondence++;
			mitIFirstCorrespondence++;
		}
		break;
	case 't':
		if (i % 3 == 0)
		{
			mtiTFirstCorrespondence++;
			mitTFirstCorrespondence++;
		}
		else if (i % 3 == 1)
		{
			mtiMFirstCorrespondence++;
			mitIFirstCorrespondence++;
		}
		else if (i % 3 == 2)
		{
			mitMFirstCorrespondence++;
			mtiIFirstCorrespondence++;
		}
		break;
	case 'i':
		if (i % 3 == 0)
		{
			mtiIFirstCorrespondence++;
			mitIFirstCorrespondence++;
		}
		else if (i % 3 == 1)
		{
			mtiTFirstCorrespondence++;
			mitMFirstCorrespondence++;
		}
		else if (i % 3 == 2)
		{
			mtiMFirstCorrespondence++;
			mitTFirstCorrespondence++;
		}
		break;
	}
}

int main()
{
	int N;
	string s;

	cin >> N;
	cin >> s;

	int i = 0;

	for (char c : s)
	{
		updateMitCorrespondence(c, i);
		i++;
	}

	int maxMIT = max(mitMFirstCorrespondence, max(mitIFirstCorrespondence, mitTFirstCorrespondence));
	int maxMTI = max(mtiMFirstCorrespondence, max(mtiIFirstCorrespondence, mtiTFirstCorrespondence));

	if (maxMIT == maxMTI)
	{
		cout << "FAKE" << endl;
	}
	else if (maxMIT > maxMTI)
	{
		cout << "mit " << (N - maxMIT) << endl;
	}
	else if (maxMIT < maxMTI)
	{
		cout << "mti " << (N - maxMTI) << endl;
	}

	return 0;
}