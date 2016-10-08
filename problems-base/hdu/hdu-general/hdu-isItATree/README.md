## solution.cpp
```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX 2010

bool flag;
int f[MAX];
int markin[MAX];
bool mark[MAX];

int find(int x)
{
	if(f[x] != x)
		f[x] = find(f[x]);
	return f[x];
}

void myunion(int a, int b)
{
	int roota = find(a), rootb = find(b);

	if(roota == rootb)
	{
		flag = true;
		return;
	}

	f[roota] = rootb;
}

int main()
{
	int count = 1, s, e, max;
	flag = false;
	while(scanf("%d%d", &s, &e) && s >= 0 && e >=0)
	{
		if(s == 0 || e == 0)
		{
			printf("Case %d is ", count++);
			printf("not a tree.\n");
			continue;
		}
		
		flag = false;
		for(int i = 1; i <= MAX; i++)
		{
			f[i] = i;
			markin[i] = 0;
			mark[i] = false;
		}
		
		markin[e]++;
		mark[s] = mark[e] = true;
		myunion(e, s);
		max = s > e? s:e;

		while(scanf("%d%d", &s, &e) && s && e)
		{
			if(max < s || max < e)
				max = s > e? s : e;

			mark[s] = mark[e] = true;

			if(flag)
				continue;

			if(++markin[e] > 1)
			{
				flag = true;
				continue;
			}

			myunion(e, s);
		}

		if(!flag)
		{
			int root;
			for(int i = 1; i <= max; i++)
				if(mark[i] == true)
				{
					root = find(i);
					break;
				}
			for(int i = 1; i <= max; i++)
				if(mark[i] == true && root != find(i))
				{
					flag = true;
					break;
				}
			if(!flag)
				if(markin[root] != 0)
					flag = true;
		}

		printf("Case %d is ", count++);

		if(!flag)
			printf("a tree.\n");
		else
			printf("not a tree.\n");
	}

	return 0;
}
```
## test.in
```cpp
6 8 5 3 5 2 6 4
5 6 0 0
8 1 7 3 6 2 8 9 7 5
7 4 7 8 7 6 0 0
3 8 6 8 6 4
5 3 5 6 5 2 0 0
-1 -1
```
