/*************************************************************************
    > File Name: hdu-Cable-Master.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Tue 04 Nov 2014 11:49:06 AM AST
 ************************************************************************/

#include <iostream>
#include "stdio.h"
#include <string.h>

using namespace std;

double cable[10005];

int main()
{
	int n, k;
	while(cin >> n >> k && n && k)
	{
		memset(cable, 0, sizeof(cable));
		double max = 0;

		for(int i = 1; i <= n; i++)
		{
			cin >> cable[i];
			if(max < cable[i])
				max = cable[i];
		}
		double min = 1;

		double ans = 0;

		while(max > min)
		{
			int count = 0;
			double mid = (min + max)/2;
			
			for(int i = 1; i <= n; i++)
			{
				count += (int)(cable[i] / mid);
			}
			
			if(count >= k)
			{
				ans = ans < mid? mid:ans;
				min = mid + 0.001;
			}
			else if(count < k)
				max = mid - 0.001;
		}

		printf("%.2f\n", ans);

	}
	return 0;
}
