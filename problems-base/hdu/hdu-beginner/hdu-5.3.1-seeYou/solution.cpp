
#include <iostream>
#include <stdio.h>

using namespace std;

#define lowbit(x) (x & (-x))
#define MAXN 1002

int shelf[MAXN][MAXN];
int origin[MAXN][MAXN];

int init()
{
	for(int i = 1; i < MAXN; i++)
		for(int j = 1; j < MAXN; j++)
		{
			origin[i][j] = 1;
			shelf[i][j] = lowbit(i) * lowbit(j);
		}
}

void update(int x, int y, int n)
{
	for(int i = x; i < MAXN; i += lowbit(i))
		for(int j = y; j < MAXN; j += lowbit(j))
		{
			shelf[i][j] += n; 
			
			//cout << "update: " << shelf[i][j] << endl;
		}
}

int sum(int x, int y)
{
	int result = 0;
	for(int i = x; i > 0; i -= lowbit(i))
		for(int j = y; j > 0; j -= lowbit(j))
			result += shelf[i][j];

	return result;
}

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
	int t, testcase = 0;
	cin >> t;

	int q;

	while(t--)
	{
		init();

		cin >> q;

		char task;
		int x1, y1, x2, y2, n;

		printf("Case %d:\n", ++testcase);

		while(q--)
		{
			cin >> task;
			switch(task)
			{
			case 'S':
				scanf("%d%d%d%d*c", &x1, &y1, &x2, &y2);
				x1++; y1++; x2++; y2++;
				if(x1 > x2)
					swap(x1, x2);
				if(y1 > y2)
					swap(y1, y2);

				printf("%d\n", sum(x1-1, y1-1) + sum(x2, y2) - sum(x1-1, y2) - sum(x2, y1-1));

				break;

			case 'A':
				scanf("%d%d%d*c", &x1, &y1, &n);
				x1++; y1++;
				update(x1, y1, n);

				origin[x1][y1] += n;

				break;

			case 'D':
				scanf("%d%d%d*c", &x1, &y1, &n);
				x1++; y1++;

				if(n > origin[x1][y1])
					n = origin[x1][y1];

				origin[x1][y1] -= n;

				update(x1, y1, -n);

				break;

			case 'M':
				scanf("%d%d%d%d%d*c", &x1, &y1, &x2, &y2, &n);
				x1++; y1++; x2++; y2++;

				if(n > origin[x1][y1])
					n = origin[x1][y1];

				origin[x1][y1] -= n;
				update(x1, y1, -n);

				origin[x2][y2] += n;
				update(x2, y2, n);

				break;
			}

		}

	}
	return 0;
}
