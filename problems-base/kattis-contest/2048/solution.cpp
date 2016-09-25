#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

int n;

int data[5][5];

void output()
{
	for(int i = 1; i <= 4; i++)
		for(int j = 1; j <= 4; j++)
		{
			cout << data[i][j];
			if(j < 4)
				cout << " ";
			else
				cout << endl;
		}
}
int main()
{
	while(cin >> data[1][1] >> data[1][2] >> data[1][3] >> data[1][4])
	{
		for(int i = 2; i <= 4; i++)
			for(int j = 1; j <= 4; j++)
			{
				cin >> data[i][j];
			}

		int move;
		cin >> move;

		//left
		if (move == 0)
		{
			for(int i = 1; i <= 4; i++)
			{
				int temp = 0;
				for(int j = 1; j <= 4; j++)
				{
					if (data[i][j] != 0)
					{
						if (temp != 0 && data[i][temp] == data[i][j])
						{
							data[i][temp] += data[i][j];	
							data[i][j] = 0;
							temp = 0;
						}
						else
							temp = j;
					}
				}

				for(int j = 1; j <= 4; j++)
				{
					if(data[i][j] != 0)
						continue;

					for(int k = j; k <= 4; k++)
						if(data[i][k] != 0)
						{
							data[i][j] = data[i][k];
							data[i][k] = 0;
							break;
						}
				}
			
			}
			
		}
		//up
		else if (move == 1)
		{
			for(int j = 1; j <= 4; j++)
			{
				int temp = 0;
				for(int i = 1; i <= 4; i++)
				{
					if (data[i][j] == 0)
						continue;
					else
					{
						if (temp != 0 && data[temp][j] == data[i][j])
						{
							data[temp][j] += data[i][j];	
							data[i][j] = 0;
							temp = 0;
						}
						else
							temp = i;
					}
				}

				for(int i = 1; i <= 4; i++)
				{
					if(data[i][j] != 0)
						continue;

					for(int k = i; k <= 4; k++)
						if(data[k][j] != 0)
						{
							data[i][j] = data[k][j];
							data[k][j] = 0;
							break;
						}
				}
			}
		}
		//right
		else if (move == 2)
		{
			for(int i = 4; i >= 1; i--)
			{
				int temp = 0;
				for(int j = 4; j >= 1; j--)
				{
					if (data[i][j] != 0)
					{
						if (temp != 0 && data[i][temp] == data[i][j])
						{
							data[i][temp] += data[i][j];	
							data[i][j] = 0;
							temp = 0;
						}
						else
							temp = j;
					}
				}

				for(int j = 4; j >= 1; j--)
				{
					if(data[i][j] != 0)
						continue;

					for(int k = j; k >= 1; k--)
						if(data[i][k] != 0)
						{
							data[i][j] = data[i][k];
							data[i][k] = 0;
							break;
						}
				}
			}
		}
		else if (move == 3)
		{
			for(int j = 4; j >= 1; j--)
			{
				int temp = 0;
				for(int i = 4; i >= 1; i--)
				{
					if (data[i][j] == 0)
						continue;
					else
					{
						if (temp != 0 && data[temp][j] == data[i][j])
						{
							data[temp][j] += data[i][j];	
							data[i][j] = 0;
							temp = 0;
						}
						else
							temp = i;
					}
				}

				temp = 0;
				for(int i = 4; i >= 1; i--)
				{
					if(data[i][j] != 0)
						continue;

					for(int k = i; k >= 1; k--)
						if(data[k][j] != 0)
						{
							data[i][j] = data[k][j];
							data[k][j] = 0;
							break;
						}
				}
			}
		}

		output();
	}
	return 0;
}

