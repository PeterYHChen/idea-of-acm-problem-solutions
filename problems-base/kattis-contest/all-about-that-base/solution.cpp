#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>

using namespace std;

int s2i(string& s, int base) 
{
	int max = 0;
	bool flag = true;
	for(int i = 0; i < s.size(); i++)
	{
		max = (max > s[i] ? max : s[i]);
		if (s[i] != '1' && flag)
			flag = false;
	}

	if (max >= 'a')
		max = max - 'a' + 10;
	else
		max = max - '0';

	int temp = 0;
	int curr;
	if(max < base)
	{
		for(int i = s.size() - 1; i >= 0; i--)
		{
			if(s[i] >= 'a')
				curr = (s[i] - 'a' + 10) * pow(base, s.size()-1-i);
			else
				curr = (s[i] - '0') * pow(base, s.size()-1-i);

			// out of range
			curr += temp;
			if (curr < temp)
				return -1;

			temp = curr;
		}

		return temp;

		// all 1's
	} else if (flag)
	{
		return s.size();
	}

	return -1;
}

bool isequal(int op1, int op2, int op3, char op)
{
	switch(op)
	{
		case '+':
			return (op1 + op2) == op3;
		case '-':
			return (op1 - op2) == op3;
		case '*':
			if (op3 / op1 < op2)
				return false;
			return (op1 * op2) == op3;
		case '/':
			if (op2 == 0)
				return false;
			return ((double)op1 / op2) == op3;
	}
}
int main()
{
	int n;
	while(cin >> n && n > 0)
	{
		string s[5];
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < 5; j++)
				cin >> s[j];

			string temp = "";
			for(int i = 1; i <= 36; i++)
			{
				int op1 = s2i(s[0], i);
				int op2 = s2i(s[2], i);
				int op3 = s2i(s[4], i);
				
				if (op1 < 0 || op2 < 0 || op3 < 0)
					continue;

				if (isequal(op1, op2, op3, s[1][0]))
				{
					if(i <= 9)
						temp += '0' + i;
					else if (i < 36)
						temp += 'a' + i - 10;
					else
						temp += '0';
				}
			}
			if (!temp.empty())
				cout << temp << endl;
			else
				cout << "invalid" << endl;
		}
	}
	return 0;
}

