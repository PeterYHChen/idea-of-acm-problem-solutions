#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX 2010

bool flag;
int f[MAX], rank[MAX];

int find(int x)
{
	if(f[x] == x)
		return f[x];	

	int temp;
	
	temp = f[x];
	f[x] = find(f[x]);
	rank[x] = (rank[x] + rank[temp]) & 1;
	return f[x];
}

void myunion(int a, int b)
{
	int roota = find(a), rootb = find(b);

	if(roota == rootb)
	{
		if(rank[a] == rank[b])
			flag = true;

		return;
	}

	f[roota] = rootb;
	rank[roota] = (rank[a] + rank[b] + 1) & 1;
}

int main()
{
	int t;
	cin >> t;

	int count = 1;
	while(t--)
	{
		int n, inter;
		scanf("%d%d", &n, &inter);

		flag = false;
		for(int i = 1; i <= n; i++)
		{
			f[i] = i;
			rank[i] = 0;
		}
		
		int a, b;
		for(int i = 0; i < inter; i++)
		{
			scanf("%d%d", &a, &b);
			if(flag)
				continue;
			myunion(a, b);
		}

		printf("Scenario #%d:\n", count++);

		if(flag)
			printf("Suspicious bugs found!\n");
		else
			printf("No suspicious bugs found!\n");

			cout << endl;

	}
	return 0;
}
