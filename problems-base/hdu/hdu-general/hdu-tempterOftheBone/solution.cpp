#include <iostream>
#include <string.h>
#include <cmath>

using namespace std;

#define DEBUG 1
#define db(x) {if(DEBUG) x;}

char map[8][8];
bool marked[8][8];
int dir[4][2] = {0,1,1,0,0,-1,-1,0};

struct Node{
	int x, y, step;
};

int n, m, t;
Node s, e;

bool okay(Node &s)
{
	if(s.x < 1 || s.x > n || s.y < 1 || s.y > m)
		return false;

	if(map[s.x][s.y] == 'X')
		return false;

	if(marked[s.x][s.y])
		return false;

	return true;
}

bool DFS(Node &s)
{
	Node temp;

	if(s.x == e.x && s.y == e.y && s.step == t)
		return true;

	if(s.step > t)
		return false;

	temp.step = s.step + 1;

	for(int i = 0; i < 4; i++)
	{
		temp.x = s.x + dir[i][0];
		temp.y = s.y + dir[i][1];
		
		if(okay(temp))
		{
			marked[temp.x][temp.y] = true;
			if(DFS(temp))
				return true;

			marked[temp.x][temp.y] = false;
		}
	}

	return false;
}

int main()
{
	while(cin >> n >> m >> t && n && m && t)
	{
		memset(marked, 0, sizeof(marked));

		for(int i = 1; i <= n; i++)		
			for(int j = 1; j <= m; j++)		
			{
				cin >> map[i][j];
				
				if(map[i][j] == 'S')
				{
					s.x = i;
					s.y = j;
				}
				else if(map[i][j] == 'D')
				{
					e.x = i;
					e.y = j;
				}
			}
			
		s.step = 0;
		
		marked[s.x][s.y] = true;

		int dist = t - abs(e.x - s.x) + abs(e.y - s.y);
		if(dist % 2 != 0)
		{
			cout << "NO" << endl;
			continue;
		}

		if(DFS(s))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}
