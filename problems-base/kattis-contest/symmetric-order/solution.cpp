#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
string names[16];

void output(int index, int n)
{
	if (index >= n)
		return;
	
	cout << names[index] << endl;
	output(index + 2, n);
	if (index + 1 < n)
		cout << names[index + 1] << endl;
}

int main()
{
	int n;
	int count = 0;
	while(cin >> n && n > 0)
	{
		for (int i = 0; i < n; i++)	
			cin >> names[i]; 
		
		count++;
		cout << "SET " << count << endl;
		output(0, n);
	}
	return 0;
}

