#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

#define MAXN 50001
#define lowbit(x) (x & (-x))

int camp[MAXN];
int origin[MAXN]; 

void init(int n)
{
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &origin[i]);	
		camp[i] = 0;
		for(int j = i - lowbit(i) + 1; j <= i; j++)
			camp[i] += origin[j];
	}

}

int sum(int a)
{
	int result = 0;

	for(int i = a; i > 0; i -= lowbit(i))
		result += camp[i];
	
	return result;
}

void update(int a, int val, int n)
{
	for(int i = a; i <= n; i += lowbit(i))
		camp[i] += val;
}

int main()
{
	int t, testcase = 0;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;

		init(n);

		printf("Case %d:\n", ++testcase);

		string s;
		int a, b;
		while(cin >> s && s != "End")
		{
			scanf("%d%d", &a, &b);
			if(s == "Query")
			{
				printf("%d\n", sum(b) - sum(a-1));
			}
			else if(s == "Add")
			{
				update(a, b, n);
				origin[a] += b;
			}
			else if(s == "Sub")
			{
				if(b > origin[a])
					b = origin[a];

				update(a, -b, n);
				origin[a] -= b;
			}
		}
	}

	return 0;
}
