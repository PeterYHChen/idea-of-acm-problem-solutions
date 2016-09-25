# Tarjan's off-line lowest common ancestor algorithm (hdu2586)

Time Limit: 2000/10000 MS (Java/Others) Memory Limit: 32768/32768 K (Java/Others)
Total Submission(s): 142 Accepted Submission(s): 66

### Problem Description
There are n houses in the village and some bidirectional roads connecting them. Every day peole always like to ask like this "How far is it if I want to go from house A to house B"? Usually it hard to answer. But luckily int this village the answer is always unique, since the roads are built in the way that there is a unique simple path("simple" means you can't visit a place twice) between every two houses. Yout task is to answer all these curious people.
 

##### Input
First line is a single integer T(T<=10), indicating the number of test cases.
For each test case,in the first line there are two numbers n(2<=n<=40000) and m (1<=m<=200),the number of houses and the number of queries. The following n-1 lines each consisting three numbers i,j,k, separated bu a single space, meaning that there is a road connecting house i and house j,with length k(0<k<=40000).The houses are labeled from 1 to n.
Next m lines each has distinct integers i and j, you are to answer the distance between house i and house j.
 

##### Output
For each test case,output m lines. Each line represents the answer of the query. Output a bland line after each test case.
 

##### Sample Input
	2
	3 2
	1 2 10
	3 1 15
	1 2
	2 3

	2 2
	1 2 100
	1 2
	2 1
 

##### Sample Output
	10
	25
	100
	100

### Explanation

##### Problem Analysis
To some degree, this problem definition is very confined. We can easily construct a graph with houses as its nodes and roads as its edges. Specially, this graph is a strongly connected graph, which means every node could be reached by the other node in the same graph. Since paths are unique, no cycles are allowed, and thus something like a spanning tree could be constructed.

Because the graph could be pretty big, with 40000 nodes at most and 39999 edges accordingly, an adjacency list is a better choice than an adjacent matrix to store the edges values. The number of queries is small (m <= 200).

##### Possible Solutions
One method is to use BFS. For each query, starting from one node, loop through all its children, accumulate the distance to its children, and push them into a queue. Do it again and again, until the function meets another node. Then the accumulated distance is the final answer. O(m*n) complexity.

Aother method is the Tarjan off-line lowest common ancestor algorithm, which I use in my code. The lowest common ancestor of two nodes a and b in a rooted tree T is the node g that is an ancestor of both a and b and that has the greatest depth in T. Starting from the root of a tree, go through each child with DFS, accumulate the distance from the root, calculate the LCA of node a and b, and get the result = (distance[a] + distance[b] - 2*distance[root]).

##### Details and Code
Tarjan off-line LCA algorithm is based on the *union-find alogrithm*, and all queries should be stored in advance. 
> (Please check my another doc **union_find_set-hdu1829** for more information)

The tarjan() function is the main function in DFS loop. Each tarjan(**curr**) excutes the following steps,
* loop through the queries
* set **curr**'s parent to be itself
(views the node **curr** as the root of a new tree)
* set **curr**ent node to be visited
* accumulate the distance to its children
* traverse each child of it with tarjan(child)
* and set the parent of its children to be itself
(merge the subtrees with its children as roots back to **curr** node)


Based on each new tree with **curr** as the root, there are visited children and non-visited children. When tarjan() visits one of the non-visited children, node a, it is easily to know the lowest common ancestor of node a and another visited node b by doing find(b) operation, which return **curr**. So each tarjan() function would loop through the queries to check if any of them could get the result.

> Noticed that once subtrees are merged back to the **curr** node, find() function would work to find the LCA bewtween an visited node and an unvisited node.



Here is my code:

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
