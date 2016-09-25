#include <iostream>
#include <string.h>

using namespace std;
#define DEBUG 0 
#define db(x) {if(DEBUG) x}

int map[10][10];
bool row[10][10];
bool column[10][10];
bool matrix[10][10];

bool DFS()
{
	int x = 0;
	int y = 0;
	//find first empty value
	for(int i = 1; i <= 9; i++)
	{
		bool flag = false;
		for(int j = 1; j <= 9; j++)
		{
			if(map[i][j] == 0)
			{
				x = i;
				y = j;
				flag = true;
				break;
			}
		}
		if(flag)
			break;
	}

	if(x == 0 && y == 0)
		return true;

	for(int i = 1; i <= 9; i++)
	{
		if(row[x][i] || column[y][i] || matrix[(x-1) / 3 * 3 + (y-1) / 3 + 1][i])
			continue;

		map[x][y] = i;
		
		row[x][i] = true;
		column[y][i] = true;
		matrix[(x-1) / 3 * 3 + (y-1) / 3 + 1][i] = true;

		if(DFS())
			return true;

		row[x][i] = false;
		column[y][i] = false;
		matrix[(x-1) / 3 * 3 + (y-1) / 3 + 1][i] = false;
		map[x][y] = 0;
	}

	return false;
}

int main()
{
	char temp;
	int count = 0;
	while(cin >> temp)
	{

		memset(row, 0, sizeof(row));
		memset(column, 0, sizeof(column));
		memset(matrix, 0, sizeof(matrix));
		
		for(int i = 1; i <= 9; i++)
			for(int j = 1; j <= 9; j++)
			{
				char ch;
				if(i == 1 && j == 1)
					ch = temp;
				else
					cin >> ch;

				if(ch == '?')
					map[i][j] == 0;
				else
					map[i][j] = ch -'0';

				row[i][map[i][j]] = true;
				column[j][map[i][j]] = true;
				matrix[(i-1) / 3 * 3 + (j-1) / 3 + 1][map[i][j]] = true;
			}

		if(DFS())
		{
			if(count++)
				cout << endl;
			
			for(int i = 1; i <= 9; i++)
			{
				cout << map[i][1];
				for(int j = 2; j <= 9; j++)
				{
					cout << " " << map[i][j];
				}
				cout << endl;
			}
		}
	}
	return 0;
}
