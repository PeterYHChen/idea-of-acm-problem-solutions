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

