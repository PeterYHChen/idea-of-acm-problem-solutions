#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> players[505];
int cnt[505];

int n, m;

void init()
{
	for(int i = 0; i <= n; i++)
	{
		players[i].clear();
		cnt[i] = 0;
	}
}

void arrange()
{
	priority_queue<int, vector<int>, greater<int> > qnode;
	
	for(int i = 1; i <= n; i++)
	{
		if(!cnt[i])
			qnode.push(i);
	}

	bool flag = true;
	int curr, temp;
	while(!qnode.empty())
	{
		curr = qnode.top();
		qnode.pop();
		
		if(flag)
			flag = false;
		else
			cout << " ";
		
		cout << curr;
		
		for(int i = 0; i < players[curr].size(); i++)
		{
			if(--cnt[players[curr][i]] == 0)
				qnode.push(players[curr][i]);
		}
	}
}
int main()
{
	while(cin >> n >> m)
	{
		init();		

		int a, b;
		for(int i = 1; i <= m; i++ )
		{
			cin >> a >> b;
			players[a].push_back(b);
			cnt[b]++;
		}

		arrange();

		cout << endl;
	}

	return 0;
}
