#include <iostream>
#include <queue>
#include <string.h>
#include <stdio.h>

using namespace std;

struct Node{
	int x, y;
	int level;
};

char map[101][101];
bool marked[101][101][11];
int dir[4][2] = {0,1,1,0,0,-1,-1,0};

int BFS(Node &s, Node &e, int n, int m, int time)
{
	queue<Node> qnode;
	qnode.push(s);

	marked[s.x][s.y][0] = true;
	Node curr, temp;

	while(!qnode.empty())
	{
		curr = qnode.front();
		qnode.pop();
		
		if(curr.x == e.x && curr.y == e.y)
			return curr.level;
		
		for(int i = 0; i < 4; i++)
		{
			temp.x = curr.x + dir[i][0];
			temp.y = curr.y + dir[i][1];
			temp.level = curr.level + 1;

			//skip marked
			if(marked[temp.x][temp.y][temp.level%time])
				continue;

			//skip wall
			if(map[temp.x][temp.y] == '#' && temp.level % time != 0)
				continue;
			
			//out of bound
			if(temp.x < 1 || temp.x > n || temp.y < 1 || temp.y > m)
				continue;

			marked[temp.x][temp.y][temp.level%time] = true;
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
					cin >> map[i][j];
					if(map[i][j] == 'Y')
					{
						s.x = i;
						s.y = j;
					}
					else if(map[i][j] == 'G')
					{
						e.x = i;
						e.y = j;
					}
				}

		s.level = 0;		
		
		int cost = BFS(s, e, n, m, time);
		if(cost == -1)
			cout << "Please give me another chance!" << endl;
		else
			cout << cost << endl;
	}

	return 0;
}
