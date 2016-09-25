#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;
#define DEBUG 0 
#define db(x) {if(DEBUG) x}

int sticks[65];
bool mark[65];

int n, length;

bool DFS(int len, int step)
{
	if(step == n && len == 0)
		return true;

	if(len == 0)
		len = length;
	
	for(int i = 1; i <= n; i++)
	{
		if(sticks[i] > len || mark[i])
			continue;
		else 
		{
			mark[i] = true;
			
			if(DFS(len - sticks[i], step + 1))
				return true;

			mark[i] = false;

			if(len == length)
				return false;

			if(i + 1 <= n && sticks[i+1] == sticks[i])
				i++;
		}
	}

	return false;
}

bool cmp(int a, int b)
{
	return a > b;
}

int main()
{
	while(cin >> n && n)
	{
		memset(mark, 0, sizeof(mark));

		int sum = 0;
		int max = 0;
		for(int i = 1; i <= n; i++)		
		{
			cin >> sticks[i];
			sum += sticks[i];

			if(max < sticks[i])
				max = sticks[i];

		}
		
		sort(sticks + 1, sticks + n + 1, cmp);
		for(length = max; length <= sum; length++)
			if(sum % length == 0 && DFS(length, 0))
			{
				cout << length << endl;
				break;
			}
	}

	return 0;
}
