#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

#define N 40002
#define M 202

struct Edge{
	int to, len;
};

vector<Edge> vedge[N];// adjacency list

int n, m; 
int x[N], y[N], z[N];
int parentOf[N], dist[N]; 
bool mark[N];

void init(int n)
{
	memset(mark, 0, sizeof(mark));

	for(int i = 1; i <= n; i++)
		vedge[i].clear();
}

void insert(int a, int b, int len)
{
	Edge temp;
	temp.len = len;

	// start node a connects to b, with length = len
	temp.to = b;
	vedge[a].push_back(temp);

	// start node b connects to a, with length = len
	temp.to = a;
	vedge[b].push_back(temp);
}

int find(int a)
{
	if(a != parentOf[a])
		parentOf[a] = find(parentOf[a]);

	return parentOf[a];
}

// all non-visited children will be merged to the visited group as a tree after being visited
void tarjan(int curr)
{
	// loop through all queries. 
	// If node a is current node, and another node b has been visited before, find(b) returns their least common ancestor
	for(int i = 1; i <= m; i++)
	{
		if(x[i] == curr && mark[y[i]])
			z[i] = find(y[i]);
		else if(y[i] == curr && mark[x[i]])
			z[i] = find(x[i]);
	}

	mark[curr] = true;

	// when tarjan dfs its children, curr would be recognized as the least common ancestor
	parentOf[curr] = curr; 

	int child;

	// loop through all children that connect to curr
	for(int i = 0; i < vedge[curr].size(); i++)
	{
		child = vedge[curr][i].to;

		// avoid searching up to the curr 
		if(!mark[child])
		{
			// accumulate distance from the root
			dist[child] = dist[curr] + vedge[curr][i].len;
			
			// DFS a child of curr, establish a tree with child as the root 
			tarjan(child);
			
			// merge the child tree back to curr, and make curr is the LCA between its children
			parentOf[child] = curr;
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

			// add houses to the adjacency list
			insert(a, b, k);
		}
		
		// store the queries
		for(int i = 1; i <= m; i++)
			scanf("%d%d", &x[i], &y[i]);

		// any value could be chosen to be the root of the tree, picking value 1 does not have special meanings.
		// set the distance of root to be 0
		dist[1] = 0;
		tarjan(1);

		for(int i = 1; i <= m; i++)
			printf("%d\n", dist[x[i]] + dist[y[i]] - 2 * dist[z[i]]);
	}

	return 0;
}
