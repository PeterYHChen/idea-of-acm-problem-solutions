#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>

using namespace std;
bool al[27];

int index(char c)
{
	if(c >= 'a' && c <= 'z')
	{
		return c - 'a';
	}
	else if(c >= 'A' && c <= 'Z')
	{
		return c - 'A';
	}

	return -1;
}
int main()
{
	int n;
	while(cin >> n && n > 0)
	{
		string s;
		getline(cin, s);
		for(int i = 0; i < n; i++)
		{
			memset(al, 0, sizeof(al));
			getline(cin, s);
			
			for(int i = 0; i < s.size(); i++)
			{
				int pos = index(s[i]);
				if(pos == -1)
					continue;

				al[pos]++;
			}
			
			string temp = "";
			bool flag = true;
			for(int i = 0; i < 26; i++)
			{
				if(al[i] == 0)
				{
					flag = false;
					temp += 'a' + i;
				}
			}

			if(flag)
				cout << "pangram" << endl;
			else
				cout << "missing " << temp << endl;
		}
	}
	return 0;
}

