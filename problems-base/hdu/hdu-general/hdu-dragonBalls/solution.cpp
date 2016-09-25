#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX 10001

int parentOf[MAX];
int ballcount[MAX];
int balltimes[MAX];

int n;

void init()
{
	for(int i = 0; i <= n; i++)
	{
		parentOf[i] = i;
		ballcount[i] = 1;
		balltimes[i] = 0;
	}
}

int find(int a)
{
	if(parentOf[a] == a)
		return parentOf[a];

	//when its parent is the root, balltimes[root] == 0, no worry
	int temp = parentOf[a];
	parentOf[a] = find(parentOf[a]);
	balltimes[a] += balltimes[temp];
	return parentOf[a];
}

void merge(int a, int b)
{
	int roota = find(a), rootb = find(b);

	if(roota == rootb)
		return;

	parentOf[roota] = rootb;
	
	balltimes[roota]++;

	ballcount[rootb] += ballcount[roota];
	ballcount[roota] = 0;
}
int main()
{
	int t, count = 0;
	cin >> t;
	while(t--)
	{
		int q;
		cin >> n >> q;
		
		init();

		int a, b;
		char task;
		bool flag = true;
		count++;

		for(int i = 0; i < q; i++)
		{
			scanf(" %c", &task);

			if(task == 'T')
			{
				scanf("%d %d", &a, &b);
				merge(a, b);
			}
			else if(task == 'Q')
			{
				scanf("%d", &a);

				int roota = find(a);
				
				if(flag)
					printf("Case %d:\n", count);
				printf("%d %d %d\n", roota, ballcount[roota], balltimes[a]);
				flag = false;
			}
		}
	}

	return 0;
}
