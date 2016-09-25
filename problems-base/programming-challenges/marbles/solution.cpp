#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;


int main()
{
	int val;
	int c1,c2,n1,n2;

	while(cin >> val && val > 0)
	{
		cin >> c1 >> n1;
		cin >> c2 >> n2;

		int temp = 0;
		if((double)n1/c1 < (double)n2/c2)
		{
			temp = n1;
			n1 = n2;
			n2 = temp;
			temp = c1;
			c1 = c2;
			c2 = temp;
			temp = 1;
		}

		if (val % n1 == 0)
		{
			cout << val/n1*c1 << " " << 0 << endl;
			continue;
		}

		if (n1 & 1 == 1 && n2 & 1 == 1 && val & 1 == 0)
		{
			cout << "failed" << endl;
			continue;
		}

		int k1 = 0, k2;
		k1 = val/n1;
		while(k1 >= 0)
		{
			k2 = 0;
			int total = k1*n1 + k2*n2;
			while(total < val)
			{	
				int cnt = 1;
				while(total + (cnt << 1) * n2 < val)
				{
					cnt <<= 1;
				}
				k2 += cnt;
				total = k1*n1 + k2*n2;
			}

			if (k1*n1 + k2*n2 == val)
			{
				break;
			}
			k1--;
		}

		if (k1*n1 + k2*n2 != val)
		{
			cout << "failed" << endl;
		}
		else
		{
			if (temp == 0)
				cout << k1 << " " << k2 << endl;
			else
				cout << k2 << " " << k1 << endl;
		}
	}

	return 0;
}
