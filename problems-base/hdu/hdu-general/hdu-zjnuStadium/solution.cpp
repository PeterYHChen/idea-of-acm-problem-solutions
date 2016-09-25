#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

#define MAX 50001

int parentOf[MAX];
int offset[MAX];

int n, m;

void init()
{
	for(int i = 0; i <= n; i++)	
	{
		parentOf[i] = i;
		offset[i] = 0;
	}
}

int find(int a)
{
	if(parentOf[a] == a)
		return a;
	
	int temp = parentOf[a];
	parentOf[a] = find(parentOf[a]);
	
	offset[a] += offset[temp];

	return parentOf[a];
}

bool merge(int &a, int &b, int &x)
{
	int roota = find(a), rootb = find(b);

	if(roota == rootb)
	{
		int diff = offset[a] - offset[b];
		if(diff < 0)	
			return (diff + 300) == x;
		else
			return diff == x;
	}

	parentOf[roota] = rootb;

	offset[roota] = offset[b] + x - offset[a];

	return true;	
}

int main()
{
	while(cin >> n >> m)
	{
		init();

		int a, b, x, count = 0;

		while(m--)
		{
			scanf("%d %d %d", &a, &b, &x);

			if(!merge(a, b, x))
				count++;
		}
		cout << count << endl;
	}

	return 0;
}
