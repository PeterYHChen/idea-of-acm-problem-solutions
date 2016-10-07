
#include<iostream>
#include <string>
#include <queue>
#include <vector>
#include"string.h"
using namespace std;

char map[210][210];
int value[210][210];
bool mark[210][210];

#define BLOCK 45000;
#define INF 50000;

struct Node
{
	int x, y;
};

class comp
{
public:
	bool operator()(const Node a, Node b)
	{
		return value[a.x][a.y] > value[b.x][b.y];
	}
};

priority_queue<Node, vector<Node>, comp> qnode;

int dir[][2] = {{0, 1},{0, -1},{1, 0},{-1, 0}};

int main()
{
	int n, m;
	while(cin >> n >> m)
	{
		string s;
		memset(mark, 0, sizeof(mark));

		for(int i = 1; i <= n; i++)
		{
			cin >> s;
			for(int j = 1; j <= m; j++)
			{
				map[i][j] = s[j-1];
			}
		}	


		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				if(map[i][j] == 'r')
				{
					Node start;
					start.x = i;
					start.y = j;
					value[i][j] = 0;
					qnode.push(start);
				}
				else 
					value[i][j] = INF;
			}
		}
	
		Node curr;
		while(qnode.size() > 0)
		{
			curr = qnode.top();
			qnode.pop();
			mark[curr.x][curr.y] = true;
		
			if(map[curr.x][curr.y] == 'a')
				break;

			Node temp;
			for(int i = 1; i <= 4; i++)
			{
				temp.x = curr.x + dir[i-1][0];
				temp.y = curr.y + dir[i-1][1];
				//out of bound
				if(temp.x < 1 || temp.y < 1 || temp.x > n || temp.y > m)
					continue;
			
				//encounter block
				if(map[temp.x][temp.y] == '#')
					continue;
			
				//marked before, got the shortest path already
				if(mark[temp.x][temp.y])
					continue;
			
				int weigh = 1;
				if(map[temp.x][temp.y] == 'x')
					weigh = 2;
			
				if(value[curr.x][curr.y] + weigh < value[temp.x][temp.y])
				{
					value[temp.x][temp.y] = value[curr.x][curr.y] + weigh;
					qnode.push(temp);
				}
			}
		}
		if(map[curr.x][curr.y] != 'a')
			cout << "Poor ANGEL has to stay in the prision all his life." << endl;
		else
			cout << value[curr.x][curr.y] << endl;
	}
	return 0;
}
