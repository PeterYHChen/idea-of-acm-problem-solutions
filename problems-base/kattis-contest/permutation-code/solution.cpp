#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>

using namespace std;
int x;
string s;
string p;
string c;

void output(string s, string p, string c)
{
	char msg[10000];
	int n = c.size();
	int d = (int)(pow((double)n, 1.5) + x) % n;
	
	int pindex, sindex;

	for (int j = 0; j < s.size(); j++)
		if (c[d] == s[j])
		{
			sindex = j;
			break;
		}

	msg[d] = p[sindex];
	
	int i = d;
	for (int count = 0; count < c.size()-1; count++)
	{
		i--;
		if (i < 0)
			i = c.size()-1;

		for(int j = 0; j < s.size(); j++)
		{
			int k = i+1;
			if (k >= c.size())
				k = 0;	

			if (msg[k] == s[j])
			{
				sindex = j;
				break;
			}
		}

		for (int j = 0; j < s.size(); j++)
			if (c[i] == s[j])
			{
				for(int k = 0; k < s.size(); k++)
					if ((k ^ sindex) == j)
					{
						pindex = k;
						break;
					}
			}
		
		msg[i] = p[pindex];
	}

	msg[c.size()] = '\0';

	cout << msg << endl;
}

int main()
{
	while(cin >> x && x > 0)
	{
		cin >> s >> p >> c;	

		output(s, p, c);
	}
	return 0;
}

