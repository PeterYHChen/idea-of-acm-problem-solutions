#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define maxn 65 

int n;
int a[maxn], b[maxn];

int result[maxn][maxn];

int calmin()
{
	for(int i = 1; i <= n; i++)
		result[i][i] = 0;

	for(int j = 1; j <= n-1; j++)
	{
		printf("computing diagonal #%d\n", j);
		for(int i = 1; i+j <= n; i++)
		{
			printf("setting [%d][%d]\n", i, i+j);
			int temp;
			for(int k = i; k <= i+j-1; k++)
			{
				temp = result[i][k] + result[k+1][i+j] + a[i]*b[k]*b[i+j];
				if(result[i][i+j] == 0)
					result[i][i+j] = temp;
				else if(result[i][i+j] > temp)
					result[i][i+j] = temp;
			}
		}
		cout << endl;
	}

	return result[1][n];

}



int main()
{
	while(cin >> n && n > 0)
	{
		memset(result, 0, (n+1)*(n+1));

		for(int i = 1; i <= n; i++)
		{
			cin >> a[i] >> b[i];
		}

		int res = calmin();
		
		for(int i = 1; i <= n; i++)
		{

			for(int j = 1; j <= n; j++)
			{
				printf("%5d ", result[i][j]);
			}
			cout << endl;
		}
			
		cout << res << endl;
	}
	return 0;
}
