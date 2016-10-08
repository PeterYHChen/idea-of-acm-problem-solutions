## solution.cpp
```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

int n;

int data[100011];
bool check[100011];
int main()
{
	while(cin >> n)
	{
		int max = 0;
		for(int i = 1; i <= n; i++)
		{
			cin >> data[i];
			if (max <= data[i])
			{
				check[i] = true;
				max = data[i];	
			}
			else
			{
				check[i] = false;
			}
		}
		
		int min = data[n];
		for(int i = n-1; i >= 1; i--)
		{
			if (min <= data[i])
			{
				check[i] = false;
			}
			else
			{
				min = data[i];	
			}
		}

		int count = 0;
		while(n--)
			if(check[n+1])
				count++;

		cout << count << endl;
	}
	return 0;
}
```
## test.in
```cpp
8
2 1 3 4 7 5 6 8
7
1 2 3 4 5 7 6
```
