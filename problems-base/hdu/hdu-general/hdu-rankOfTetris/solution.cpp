#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>

using namespace std;

#define MAX 10002
int n, m, sum;

int parentOf[MAX];
vector<int> sonsOf[MAX];
int indegreeOf[MAX];
int a[MAX], b[MAX];
char c[MAX];

void init()
{
	for(int i = 0; i < n; i++)
	{
		parentOf[i] = i;
		sonsOf[i].clear();
		indegreeOf[i] = 0;
	}
}

int find(int a)
{
	if(parentOf[a] != a)
		parentOf[a] = find(parentOf[a]);

	return parentOf[a];
}

void topsort()
{
	bool uncertain = false;
	queue<int> qnode;	

	for(int i = 0; i < n; i++)
		if(indegreeOf[i] == 0 && find(i) == i)
			qnode.push(i);
	
	while(!qnode.empty())
	{
		int curr = qnode.front();

		if(qnode.size() > 1)
			uncertain = true;

		qnode.pop();
		sum--;

		for(int i = 0; i < sonsOf[curr].size(); i++)
			if(--indegreeOf[sonsOf[curr][i]] == 0)
				qnode.push(sonsOf[curr][i]);
	}

	if(sum > 0)
		printf("CONFLICT\n");
	else if(uncertain)
		printf("UNCERTAIN\n");
	else
		printf("OK\n");
}

int main()
{
	while(scanf("%d %d", &n, &m) != EOF)
	{
		sum = n;
		init();

		for(int i = 0; i < m; i++)
		{
			scanf("%d %c %d", &a[i], &c[i], &b[i]);
			
			int roota = find(a[i]), rootb = find(b[i]);

			if(c[i] == '=')
			{
				if(roota != rootb)
					sum--;

				parentOf[roota] = rootb;
			}
		}

		for(int i = 0; i < m; i++)
		{
			int roota = find(a[i]), rootb = find(b[i]);

			if(c[i] == '=')
				continue;
			else if (c[i] == '>')
			{
				sonsOf[roota].push_back(rootb);
				indegreeOf[rootb]++;
			}
			else if (c[i] == '<')
			{
				sonsOf[rootb].push_back(roota);
				indegreeOf[roota]++;
			}
		}

		topsort();
	}

	return 0;
}
