## solution.cpp
```cpp
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
int width;
int x[16];
int y[16];


int main()
{
	while(cin >> width && width > 0)
	{
		int count = 0;
		
		int w = 0, h = 0;
		int mh = 0, mw = 0;
		while(cin >> x[count] >> y[count] && x[count] >= 0 && y[count] >= 0)
		{
			if (w + x[count] > width)
			{
				if (mw < w)
					mw = w;

				w = 0;
				h += mh;
				mh = y[count];
			}

			w += x[count];
			if (mh < y[count])
				mh = y[count];
			
			count++;
		}
		if (mw < w)
			mw = w;
		h += mh;

		cout << mw << " x " << h << endl;
	}
	return 0;
}
```
## test.in
```cpp
35
10 5
20 12
8 13
-1 -1
25
10 5
20 13
3 12
-1 -1
15
5 17
5 17
5 17
7 9
7 20
2 10
-1 -1
0
```
