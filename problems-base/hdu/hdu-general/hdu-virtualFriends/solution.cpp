#include <iostream>
#include <stdio.h>
#include <string>
#include <map>

using namespace std;

#define MAX 200001

map<string, int>record;

int parentOf[MAX];
int count[MAX];

int n;

void init()
{
	record.clear();

	for(int i = 0; i <= 2 * n; i++)
	{
		parentOf[i] = i;
		count[i] = 1;
	}
}

int find(int a)
{
	if(parentOf[a] != a)
		parentOf[a] = find(parentOf[a]);

	return parentOf[a];
}

void merge(int a, int b)
{
	int roota = find(a), rootb = find(b);

	if(roota == rootb)
		return;

	parentOf[roota] = rootb;
	
	count[rootb] += count[roota];
}

int main()
{
	int t;
	while(cin >> t)
	{
		while(t--)
		{
			int cnt = 0;
			string a, b;
			cin >> n;

			init();

			while(n--)
			{
				cin >> a >> b;
				
				if(!record[a])	
					record[a] = ++cnt;

				if(!record[b])	
					record[b] = ++cnt;
				
				int ia = record.find(a)->second, ib = record.find(b)->second;

				merge(ia, ib);

				cout << count[find(ib)] << endl;
			}
		}
	}

	return 0;
}
