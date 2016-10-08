## solution.cpp
```cpp
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
```
## test.in
```cpp
10 10
1 2 150
3 4 200
1 5 270
2 6 200
6 5 80
4 7 150
8 9 100
4 8 50
1 7 100
9 2 100
```
