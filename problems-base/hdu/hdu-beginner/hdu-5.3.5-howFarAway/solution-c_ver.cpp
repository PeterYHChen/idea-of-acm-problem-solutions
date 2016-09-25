#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define N 40002
#define M 202

struct Edge{
	int to, len;
	int next;
};

Edge edge[2*N];

int n, m, edgeCnt, edgeOf[N];
int x[N], y[N], z[N];
int parentOf[N], dist[N]; 
bool mark[N];

void init(int n)
{
	edgeCnt = 0;
	memset(edgeOf, -1, sizeof(edgeOf));
	memset(mark, 0, sizeof(mark));
}

void insert(int a, int b, int len)
{
	edge[edgeCnt].to = b;// the current edge points to b
	edge[edgeCnt].len = len; // set its length
	edge[edgeCnt].next = edgeOf[a]; // next = previous edge of its head a
	edgeOf[a] = edgeCnt++; // edge head a stores the index of its edge

	edge[edgeCnt].to = a;
	edge[edgeCnt].len = len;
	edge[edgeCnt].next = edgeOf[b];
	edgeOf[b] = edgeCnt++;
}

int find(int a)
{
	if(a != parentOf[a])
		parentOf[a] = find(parentOf[a]);

	return parentOf[a];
}

void tarjan(int curr)
{
	mark[curr] = true;
	// when tarjan dfs its children, curr would be recognized as the least common ancestor
	parentOf[curr] = curr; 

	// loop through all queries. 
	// If any of the nodes is current node, and another node has been visited before, they must share the same ancestor
	for(int i = 1; i <= m; i++)
	{
		if(x[i] == curr && mark[y[i]])
			z[i] = find(y[i]);
		else if(y[i] == curr && mark[x[i]])
			z[i] = find(x[i]);
	}

	for(int i = edgeOf[curr]; i != -1; i = edge[i].next)
	{
		// avoid searching up to the root
		if(!mark[edge[i].to])
		{
			dist[edge[i].to] = dist[curr] + edge[i].len;
			
			tarjan(edge[i].to);
			
			// make curr is the LCA between its children and its friends
			parentOf[edge[i].to] = curr;
		}
	}
}

int main()
{
	int t;
	cin >> t;

	while(t--)
	{
		cin >> n >> m;

		init(n);
		
		int a, b, k;
		for(int i = 1; i <= n-1; i++)
		{
			scanf("%d%d%d", &a, &b, &k);

			insert(a, b, k);
		}
		
		for(int i = 1; i <= m; i++)
			scanf("%d%d", &x[i], &y[i]);

		dist[1] = 0;

		tarjan(1);

		for(int i = 1; i <= m; i++)
			printf("%d\n", dist[x[i]] + dist[y[i]] - 2 * dist[z[i]]);
	}

	return 0;
}
