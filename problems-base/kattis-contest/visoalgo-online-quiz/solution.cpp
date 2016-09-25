#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <queue>
#include <vector>

using namespace std;

int n, m;
int minw, count;

struct Node
{
	int tag;
	int w;
	bool ck;
};

class comp{
	public:
	bool operator() (const Node& a, const Node& b) const
	{
		return a.w > b.w;
	}
};

vector<Node> vnodes[10001];

int bfs(int s, int t)
{
	int minw = 0;
	priority_queue<Node, vector<Node>, comp> qnodes;
	
	Node curr;
	curr.tag = s;
	curr.w = 0;
	qnodes.push(curr);

	while(!qnodes.empty())
	{
		curr = qnodes.top();
		qnodes.pop();
		
		if(curr.tag == t)
		{
			return curr.w;
		}
		
		Node temp;
		for(int i = 0; i < vnodes[curr.tag].size(); i++)
		{
			temp.tag = vnodes[curr.tag][i].tag;
			temp.w = curr.w + vnodes[curr.tag][i].w;
			
			qnodes.push(temp);
		}
	}

	return -1;
}

void dfs(int s, int weight, int t)
{
	if(s == t)	
	{
		if (minw == -1)
		{
			minw = weight;
			count = 1;
		}
		else
		{
			if (minw == weight)
				count++;
			else if (minw > weight)
			{
				minw = weight;
				count = 1;
			}
		}

		return;
	}

	for(int i = 0; i < vnodes[s].size(); i++)
	{
		if (vnodes[s][i].ck)
			continue;

		if (minw != -1 && minw < vnodes[s][i].w + weight)
			continue;

		vnodes[s][i].ck = true;
		dfs(vnodes[s][i].tag, vnodes[s][i].w + weight, t);
		vnodes[s][i].ck = false;
	}
}

int main()
{
	while(cin >> n >> m)
	{
		minw = -1;
		count = 0;
		for(int i = 0; i < n; i++)
		{
			vnodes[i].clear();	
		}

		int u, v, w;
		for(int i = 0; i < m; i++)
		{
			cin >> u >> v >> w;
			Node temp;
			temp.tag = v;
			temp.w = w;
			temp.ck = false;
			vnodes[u].push_back(temp);
		}

		int s, t;
		cin >> s >> t;
		minw = bfs(s, t);
		if (minw == -1)
			cout << "0" << endl;
		else
		{
			dfs(s, 0, t);
			cout << count << endl;
		}
	}
	return 0;
}

