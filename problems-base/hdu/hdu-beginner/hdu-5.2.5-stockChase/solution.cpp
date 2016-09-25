#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

#define MAX 240

bool mark[MAX][MAX];

void addEdge(int a, int b, int n)
{
	mark[a][b] = true;
	
	for(int i = 1; i <= n; i++)		
		if(mark[i][a] && !mark[i][b])
			mark[i][b] = true;

	for(int i = 1; i <= n; i++)		
		if(mark[i][b])
			for(int j = 1; j <= n; j++)
				if(mark[b][j] && !mark[i][j])
					mark[i][j] = true;
}

int main()
{
	int n, t;
	int testCase = 0;

	while(cin >> n >> t && n && t)
	{
		memset(mark, 0, sizeof(mark));

		int a, b;
		int cnt = 0;

		for(int i = 1; i <= t; i++)
		{
			scanf("%d %d", &a, &b);
			
			if(mark[b][a] || a == b)
				cnt++;
			else if(!mark[a][b])
				addEdge(a, b, n);
		}

		cout << ++testCase << ". " << cnt << endl;
	}

	return 0;
}
