#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAXN 32002
#define lowbit(x) (x & (-x))

int a[MAXN];
int cnt[MAXN];

void init()
{
	memset(a, 0, sizeof(a));
	memset(cnt, 0, sizeof(cnt));
}

void add(int x, int val)
{
	for(int i = x; i <= MAXN; i += lowbit(i))	
		a[i] += val;
}

int sum(int x)
{
	int result = 0;
	for(int i = x; i > 0; i -= lowbit(i))
		result += a[i];

	return result;
}

int main()
{
	int n;

	while(cin >> n)
	{
		init();

		int x, y;
		for(int i = 1; i <= n; i++)
		{
			scanf("%d%d", &x, &y);
			
			cnt[sum(x+1)]++;
			add(x+1, 1);
		}

		for(int i = 0; i < n; i++)
			printf("%d\n", cnt[i]);

	}
	return 0;
}
