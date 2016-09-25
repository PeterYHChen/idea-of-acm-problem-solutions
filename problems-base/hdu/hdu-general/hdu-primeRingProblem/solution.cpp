#include <iostream>
#include <string.h>
#include <stack>
#include <cmath>

using namespace std;

#define DEBUG 1
#define db(x) {if(DEBUG) x;}

int n;
bool marked[21];
int value[21];

bool isPrime(int m)
{
	if(m == 1)
		return false;

	if(m == 2)
		return true;
	
	for(int i = 2; i <= sqrt((double)m); i++)
		if(m % i == 0)
			return false;
	
	return true;
}

void print()
{
	cout << value[1];
	for(int i = 2; i <= n; i++)
		cout << " " << value[i];
	cout << endl;
}

void DFS(int step)
{
	if(step == n)
	{
		if(isPrime(value[n] + value[1]))
			print();
		return;
	}

	for(int i = 1; i <= n; i++)
	{
		if(marked[i])
			continue;

		if(isPrime(i + value[step]))
		{
			value[step + 1] = i;

			marked[i] = true;
			DFS(step + 1);
			marked[i] = false;
		}
	}
}

int main()
{
	int count = 0;
	while(cin >> n)
	{
		count++;
		memset(marked, 0, sizeof(marked));
		cout << "Case " << count << ":" << endl;

		marked[1] = true;
		value[1] = 1;
		DFS(1);

		cout << endl;
	}
	return 0;
}

