
#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>
#include <assert.h>

using namespace std;

#define MAX 2003

vector<int> nodes[3][MAX];
int indegree[3][MAX];
int ans[3][MAX];

void insert(int dimention, int a1, int a2)
{
	nodes[dimention][a1].push_back(a2);
	indegree[dimention][a2]++;
}

void init(int n)
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 1; j <= 2*n; j++)
		{
			indegree[i][j] = 0;
			nodes[i][j].clear();
		}
	}

	for(int i = 0; i < 3; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			insert(i, j, j+n);	
		}
	}
}

bool topsort(int dimention, int n)
{
	queue<int> qnode;

	for(int i = 1; i <= n; i++)
		if(indegree[dimention][i] == 0)
		{
			qnode.push(i);
			ans[dimention][i] = 0;
		}

	int curr, cnt = 0;

	while(!qnode.empty())
	{
		curr = qnode.front();
		qnode.pop();
		cnt++;

		for(int i = 0; i < nodes[dimention][curr].size(); i++)
		{
			int node = nodes[dimention][curr][i];
			if(--indegree[dimention][node] == 0)
			{
				qnode.push(node);
				ans[dimention][node] = ans[dimention][curr] + 1;
			}
		}
	}

	return cnt == 2*n;
}

int main()
{
	int n, r, testcase = 0;
	while(cin >> n >> r && n)
	{
		init(n);		
		
		char relation;
		int a, b;
		while(r--)
		{
			scanf("\n%c%d%d", &relation, &a, &b);	
			if(relation == 'I')
			{
				for(int i = 0; i < 3; i++)
				{
					insert(i, a, b+n);
					insert(i, b, a+n);
				}
			}
			else
			{
				insert(relation - 'X', a+n, b);
			}
		}

		printf("Case %d: ", ++testcase);
		if(!topsort(0, n) || !topsort(1, n) || !topsort(2, n))
			printf("IMPOSSIBLE\n");
		else
		{
			printf("POSSIBLE\n");
			
			for(int i = 1; i <= n; i++)
				printf("%d %d %d %d %d %d\n", ans[0][i], ans[1][i], ans[2][i], ans[0][i+n], ans[1][i+n], ans[2][i+n]);
		}

		cout << endl;
	}

	return 0;
}
