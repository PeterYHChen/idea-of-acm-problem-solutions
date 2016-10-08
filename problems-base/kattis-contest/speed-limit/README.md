## solution.cpp
```cpp
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
```
## test.in
```cpp
3
20 2
30 6
10 7
2
60 1
30 5
4
15 1
25 2
30 3
10 5
-1
```
