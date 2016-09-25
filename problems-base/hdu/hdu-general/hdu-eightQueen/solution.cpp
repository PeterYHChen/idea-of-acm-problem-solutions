#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;
#define DEBUG 0 
#define db(x) {if(DEBUG) x}

int n;
bool row[21];
bool column[21];
bool ptri[41];
bool ntri[41];
int value[21];

bool okay(int x, int y)
{
	if(row[x] || column[y] || ptri[x + y] || ntri[n - x + y])
		return false;
	return true;
}
int DFS(int step)
{
	if(step == n)
		return 1;

	int count = 0;

	for(int i = 1; i <= n; i++)
	{
		if(okay(i, step + 1))
		{
			row[i] = true;
			column[step + 1] = true;
			ptri[i + step + 1] = true;
			ntri[n - i + step + 1] = true;
			
			count += DFS(step + 1);
					
			row[i] = false;
			column[step + 1] = false;
			ptri[i + step + 1] =false;
			ntri[n - i + step + 1] = false;
		}
	}

	return count;
}

int main()
{
	memset(value, -1, sizeof(value));

	while(cin >> n && n)
	{
		memset(row, 0, sizeof(row));
		memset(column, 0, sizeof(column));
		memset(ptri, 0, sizeof(ptri));
		memset(ntri, 0, sizeof(ntri));

		if(value[n] == -1)
			value[n] = DFS(0);
	
		cout << value[n] << endl;	
	}

	return 0;
}
