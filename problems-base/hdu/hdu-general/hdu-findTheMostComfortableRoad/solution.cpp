#include <iostream>
#include <string.h>
#include <queue>
#include <vector>

using namespace std;

int n, m;
int start, end, speed;
bool mark[201][201][201];

struct Node{
	int val, speed;
};

vector<Node> adjacent[201];

struct Transfer{
	int s, m, e;
	int min, max;
};

class comp{
public:
	bool operator()(Transfer &a, Transfer &b)
	{
		return (a.max - a.min) > (b.max - b.min);
	}
};

int BFS()
{
	priority_queue<Transfer, vector<Transfer>, comp> qtrans;
	
	Transfer curr, temp;

	for(int i = 0; i < adjacent[start].size(); i++)		
	{
		curr.s = start;
		curr.m = curr.s;
		curr.e = adjacent[start][i].val;
		curr.min = curr.max = adjacent[start][i].speed;

		qtrans.push(curr);
	}

	while(!qtrans.empty())
	{
		curr = qtrans.top();
		qtrans.pop();

		if(curr.e == end)
			return curr.max - curr.min;
		
		for(int i = 0; i < adjacent[curr.e].size(); i++)		
		{
			temp.s = curr.m;
			temp.m = curr.e;
			temp.e = adjacent[curr.e][i].val;

			if(temp.e == temp.s)
				continue;

			if(mark[temp.s][temp.m][temp.e])
				continue;

			mark[temp.s][temp.m][temp.e] = true;

			temp.max = adjacent[curr.e][i].speed > curr.max? adjacent[curr.e][i].speed : curr.max;
			temp.min = adjacent[curr.e][i].speed < curr.min? adjacent[curr.e][i].speed : curr.min;

			qtrans.push(temp);
		}
	}

	return -1;
}

int main()
{
	while(cin >> n >> m && n && m)
	{
		for(int i = 0; i <= n; i++)
			adjacent[i].clear();

		Node temp;

		for(int i = 1; i <= m; i++)
		{
			cin >> start >> end >> speed;
			temp.speed = speed;

			temp.val = end;
			adjacent[start].push_back(temp);

			temp.val = start;
			adjacent[end].push_back(temp);
		}

		int q;
		cin >> q;

		while(q--)
		{
			memset(mark, 0, sizeof(mark));

			cin >> start >> end;

			cout << BFS() << endl;
		}
	}
		
	return 0;
}
