#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <string>

using namespace std;

int n;
char arr[28];

void output(int n, int index)
{
	index = (index + n) % 28;
	
	cout << arr[index];
}
int main()
{
	string s;
	for(int i = 0; i < 26; i++)
	{
		arr[i] = 'A' + i;
	}
	arr[26] = '_';
	arr[27] = '.';

	while(cin >> n && n > 0)
	{
		cin >> s;
		int index;	
		for(int i = s.size() - 1; i >= 0; i--)
		{
			if(s[i] >= 'A' && s[i] <= 'Z')
				index = s[i] - 'A';	
			else if (s[i] == '_')
				index = 26;
			else
				index = 27;

			output(n, index);
		}
		cout << endl;
	}
	return 0;
}

