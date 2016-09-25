#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
int speed[11];
int elapse[11];
int main()
{
	int n;
	while(cin >> n && n >= 0)
	{
		int miles = 0;
		for (int i = 0; i < n; i++)	
		{
			cin >> speed[i] >> elapse[i];
			if (i == 0)
				miles = elapse[i]*speed[i];
			else
				miles += (elapse[i] - elapse[i-1]) * speed[i];
		}
		
		cout << miles << " miles" << endl;
	}
	return 0;
}
