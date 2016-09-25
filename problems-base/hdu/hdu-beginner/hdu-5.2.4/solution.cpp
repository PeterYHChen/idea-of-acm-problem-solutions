#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

#define MAX 1001

map<string, int> numbers;
vector<int> players[MAX];
int cnt[MAX];

int order;

void init()
{
	order = 0;
	numbers.clear();
	for(int i = 0; i <= MAX; i++)
	{
		players[i].clear();
		cnt[i] = 0;
	}
}

bool arrange()
{
	int temp = 0;
	for(int i = 1; i <= order; i++)	
	{
		if(cnt[i] == 0)
			temp++;
	}

	if(temp > 1)
		return false;

	return true;
}

int main()
{
	int n;
	while(cin >> n && n)
	{
		init();		

		string a, b;
		for(int i = 1; i <= n; i++)
		{
			cin >> a >> b;

			if(numbers.find(a) == numbers.end())
				numbers[a] = ++order;

			if(numbers.find(b) == numbers.end())
				numbers[b] = ++order;

			int numa = numbers[a], numb = numbers[b];

			players[numa].push_back(numb);
			cnt[numb]++;
		}

		if(arrange())
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}

	return 0;
}
