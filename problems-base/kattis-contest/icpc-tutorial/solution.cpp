#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

int m, n, t;

int fact[14];
int expo[31];
bool factor(int n, int m)
{
	if (n >= 13)
		return false;

	if(fact[n] > m)
		return false;
	
	return true;
}

int main()
{
	memset(fact, 0, sizeof(fact));
	fact[1] = 1;
	for (int i = 2; i <= 12; i++)
	{
		fact[i] = i * fact[i-1];
	}
	
	expo[1] = 2;
	for (int i = 2; i <= 29; i++)
	{
		expo[i] = (expo[i-1] << 1);
	}

	while(cin >> m >> n >> t)
	{
		int ac = 0;
		int temp = 0;
		switch(t)
		{
			case 1:
				ac = factor(n, m);	
				break;
			case 2:
				if(n >= 30)
					ac = false;
				else
					ac = (expo[n] <= m);
				break;
			case 3:
				while(m / n > 0)
				{
					m /= n;
					temp++;
					if (temp >= 4)
						break;
				}
				if (temp >= 4)
					ac = true;
				else 
					ac = false;
				break;
			case 4:
				if (n > 1000)
					ac = false;
				else
					ac = (n*n*n <= m);
				break;
			case 5:
				while(m / n > 0)
				{
					m /= n;
					temp++;
					if (temp >= 2)
						break;
				}
				if (temp >= 2)
					ac = true;
				else 
					ac = false;
				break;
			case 6:
				if (n > m)
					ac = false;
				else
				{
					double d = n;
					ac = (d * log2(d) <= m);
				}
				break;
			case 7:
				ac = (n <= m);
				break;
		}

		if (ac)
			cout << "AC" << endl;
		else
			cout << "TLE" << endl;
	}
	return 0;
}

