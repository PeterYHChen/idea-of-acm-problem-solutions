#include <iostream>
#include <string.h>
#include <cmath>

using namespace std;

#define DEBUG 1
#define db(x) {if(DEBUG) x;}

int t;
int value[11];
int map[11][11];

int dist(int a, int b)
{
	return abs(value[a] - value[b]);
}

int cal()
{
	for(int j = 1; j <= 9; j++)
		for(int i = 1; i <= 9; i++)
			if(i+j <= 10)
			{
				int min = 100;
				for(int k = i + 1; k <= i + j - 1; k++)
				{
					if(min > map[i][k] + map[k][i+j])
						min = map[i][k] + map[k][i+j];
				}

				if(min > dist(i, i+j) + map[i+1][i+j])
					min = dist(i, i+j) + map[i+1][i+j];
				
				map[i][i+j] = min;
			}

	return map[1][10];
}

int main()
{
	cin >> t;

	while(t--)
	{
		memset(map, 0, sizeof(map));

		for(int i = 1; i <= 10; i++)
		{
			int temp;
			cin >> temp;
			value[temp] = i;
		}

		for(int i = 1; i <= 9; i++)
			map[i][i+1] = dist(i, i+1);
	
		cout << cal() << endl;
	}

	return 0;
}

