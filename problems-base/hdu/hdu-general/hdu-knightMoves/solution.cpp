#include <iostream>
#include <queue>
#include "string.h"
#include "stdio.h"
using namespace std;

struct Node
{
	int x;
	int y;
	int level;
};

bool marked[9][9];
int dir[][2] = {
	{1,2},{2,1},{-1,2},{-2,1},{-1,-2},{-2,-1},{1,-2},{2,-1}
};

int BFS(Node &s, Node &e)
{
	memset(marked, 0, sizeof(marked));
	queue<Node> qnode;

	qnode.push(s);

	Node curr, temp;
	while(!qnode.empty())
	{
		curr = qnode.front();
		qnode.pop();

		if(curr.x == e.x && curr.y == e.y)
			return curr.level;
		
		for(int i = 0; i < 8; i++)	
		{
			temp.x = curr.x + dir[i][0];
			temp.y = curr.y + dir[i][1];
			temp.level = curr.level + 1;

			//in boundary
			if(temp.x >= 1 && temp.x <= 8 && temp.y >= 1 && temp.y <= 8)
				if(!marked[temp.x][temp.y])
				{
					marked[temp.x][temp.y] = true;
					qnode.push(temp);
				}
		}
	}

	return -1;
}

int main()
{
	char start[2], end[2];
	Node s, e;
	while(cin >> start >> end)
	{
		s.x = start[0] - 'a' + 1;
		s.y = start[1] - '0';
		s.level = 0;

		e.x = end[0] - 'a' + 1;
		e.y = end[1] - '0';

		printf("To get from %s to %s takes %d knight moves.\n", start, end, BFS(s,e));
		//cout << "To get from " << start << " to " << end 
		//	<< " takes " << BFS(s,e) << " knight moves." << endl;
	}
	
	return 0;
}

