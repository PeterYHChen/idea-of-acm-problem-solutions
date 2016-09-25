#include <iostream>
#include <queue>
#include <string.h>
#include <stdio.h>

using namespace std;

struct Node{
	int x, y;
	int level;
	int floor;
};

char map[2][11][11];
bool marked[2][11][11];
int dir[4][2] = {0,1,1,0,0,-1,-1,0};

int BFS(Node &s, Node &e, int n, int m)
{
	queue<Node> qnode;
	qnode.push(s);

	marked[s.floor][s.x][s.y] = true;
	Node curr, temp;

	while(!qnode.empty())
	{
		curr = qnode.front();
		qnode.pop();
		
		if(curr.x == e.x && curr.y == e.y && curr.floor == e.floor)
			return curr.level;
		
		for(int i = 0; i < 4; i++)
		{
			temp.x = curr.x + dir[i][0];
			temp.y = curr.y + dir[i][1];
			temp.floor = curr.floor;
			temp.level = curr.level + 1;

			//skip marked
			if(marked[temp.floor][temp.x][temp.y])
				continue;

			//skip wall
			if(map[temp.floor][temp.x][temp.y] == '*')
				continue;
			
			//out of bound
			if(temp.x < 1 || temp.x > n || temp.y < 1 || temp.y > m)
				continue;

			//teleport 
			if(map[temp.floor][temp.x][temp.y] == '#')
			{
				marked[temp.floor][temp.x][temp.y] = true;

				if(map[1 - temp.floor][temp.x][temp.y] == '*')
					continue;
				
				if(map[1 - temp.floor][temp.x][temp.y] == '#')
				{
					marked[1 - temp.floor][temp.x][temp.y] = true;
					continue;
				}

				if(marked[1 - temp.floor][temp.x][temp.y])
					continue;

				temp.floor = 1 - curr.floor;
			}
			
			marked[temp.floor][temp.x][temp.y] = true;
			qnode.push(temp);
		}
	}

	return -1;
}

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n, m, time;
		cin >> n >> m >> time;
		
		Node s, e;
		memset(marked, 0, sizeof(marked));

		for(int k = 0; k <= 1; k++)
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= m; j++)
				{
					cin >> map[k][i][j];
					if(map[k][i][j] == 'P')
					{
						e.x = i;
						e.y = j;
						e.floor = k;
					}
				}

		s.x = 1;
		s.y = 1;
		s.floor = 0;
		s.level = 0;		
		
		int cost = BFS(s, e, n, m);
		if(cost != -1 && cost <= time)
			cout << "YES" << cost << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}
