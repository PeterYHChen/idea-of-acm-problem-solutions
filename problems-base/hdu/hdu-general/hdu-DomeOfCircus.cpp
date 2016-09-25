/*************************************************************************
    > File Name: hdu-DomeOfCircus.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Tue 04 Nov 2014 10:43:19 PM AST
 ************************************************************************/

#include<iostream>
#include <cmath>
#include "stdio.h"
#include "string.h"
using namespace std;

struct node{
	double m;
	double z;
};

node point[10010];
double r[10010];
double h[10010];

void getMinVolume(int i)
{
	double max, min;
	max = 1000;
	min = point[i].m + 0.0001;

	double midl, midr, hl, hr;

	while(max - min > 1e-6)
	{
		midl = (2*max + min)/3;
		midr = (max + 2*min)/3;
		hl = (point[i].z * midl)/(midl - point[i].m);
		hr = (point[i].z * midr)/(midr - point[i].m);

		if(midl*midl*hl < midr*midr*hr)
			min = midr + 1e-5;
		else
			max = midl - 1e-5;
	}
	
	r[i] = midl;
	h[i] = hl;
}

bool pointInCurrVolume(double m, double z, int curr)
{
	if(z < h[curr] / r[curr] * (r[curr] - m))
		return true;
	
	return false;
}

void connectPointIndex(int curr, int i)
{
	r[curr] = (point[curr].z * point[i].m - point[i].z * point[curr].m) / (point[curr].z - point[i].z);
	h[curr] = point[curr].z * r[curr] / (r[curr] - point[curr].m);
}

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		
		memset(r, 0, sizeof(r));
		memset(h, 0, sizeof(h));
		memset(point, 0, sizeof(point));

		for(int i = 1; i <= n; i++)
		{
			double x, y;
			cin >> x >> y;
			cin >> point[i].z;
			
			point[i].m = sqrt(x*x + y*y);
		}
		
		getMinVolume(1);
		int curr = 1;

		for(int i = 2; i <= n; i++)
		{
			if(pointInCurrVolume(point[i].m, point[i].z, curr))
			{
				r[i] = r[curr];
				h[i] = h[curr];

				continue;
			}
			
			getMinVolume(i);
			
			if(!pointInCurrVolume(point[curr].m, point[curr].z, i))
				connectPointIndex(i, curr);
			
			curr = i;
		}

		printf("%.3f %.3f\n", h[n], r[n]);
	}
	
	return 0;
}
