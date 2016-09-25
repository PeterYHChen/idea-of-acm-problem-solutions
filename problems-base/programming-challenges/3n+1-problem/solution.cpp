#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int cycleLen[1000001];

int getCycleLength(int a)
{
	if (a == 1)
		return 1;

	if (a <= 1000000)
	{
		if (cycleLen[a] != 0)
			return cycleLen[a];
	}

	int val = a;
	// if odd
	if (val % 2)
	{
		val = 3 * val + 1;
	}
	// if even
	else
	{
		val /= 2;
	}
		
	if (a <= 1000000)
	{
		cycleLen[a] = 1 + getCycleLength(val);
		return cycleLen[a]; 
	}
	else
	{
		return 1 + getCycleLength(val);
	}
}

int maxCycleLength(int a, int b)
{
	int max = 0;
	if (a > b)
	{
		int j = a;
		a = b;
		b = j;
	}

	for (int i = a; i <= b; i++)
	{
		int len = getCycleLength(i);
		if (max < len)				
			max = len;
	}
			
	return max;
}

int main()
{
	int i, j;
	memset(cycleLen, 0, sizeof(cycleLen));

	while(cin >> i >> j && i > 0 && j > 0)
	{
		cout << i << " " << j << " " << maxCycleLength(i, j) << endl;
	}

	return 0;
}
