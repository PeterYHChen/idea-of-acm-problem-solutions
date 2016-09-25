#include <iostream>
#include <queue>
#include <string.h>
#include <stdio.h>

using namespace std;

struct Node{
	int x, y;
};

char map[21][21];
bool marked[21][21];
int dir[4][2] = {0,1,1,0,0,-1,-1,0};

int BFS(Node &s, int n, int m)
{
	queue<Node> qnode;
	qnode.push(s);

	marked[s.x][s.y] = true;
	Node curr, temp;
	
	int count = 0;
	while(!qnode.empty())
	{
		curr = qnode.front();
		qnode.pop();
		
		count++;

		for(int i = 0; i < 4; i++)
		{
			temp.x = curr.x + dir[i][0];
			temp.y = curr.y + dir[i][1];

			//skip marked
			if(marked[temp.x][temp.y])
				continue;

			//skip red tile
			if(map[temp.x][temp.y] == '#')
				continue;
			
			//out of bound
			if(temp.x < 1 || temp.x > n || temp.y < 1 || temp.y > m)
				continue;

			marked[temp.x][temp.y] = true;
			qnode.push(temp);
		}
	}

	return count;
}

int main()
{
	int w, h;
	while(cin >> w >> h && w && h)
	{
		Node s;
		memset(marked, 0, sizeof(marked));

		for(int i = 1; i <= h; i++)
			for(int j = 1; j <= w; j++)
			{
				cin >> map[i][j];
				if(map[i][j] == '@')
				{
					s.x = i;
					s.y = j;
				}
			}

		cout << BFS(s, h, w) << endl;
	}

	return 0;
}
