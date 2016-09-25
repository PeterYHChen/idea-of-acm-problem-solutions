#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <map>
#include <queue>

using namespace std;
multimap<string, string> paths;
map<string, string> result;
map<string, bool> check;

void bfs(string from, string to)
{
	queue<string> que;

	que.push(from);
	string curr, temp;
	bool flag = false;
	check[from] = true;
	while(!que.empty())
	{
		curr = que.front();
		que.pop();

		if(curr == to)
		{
			flag = true;
			break;
		}
		multimap<string, string>::iterator it;
		for (it=paths.equal_range(curr).first; it!=paths.equal_range(curr).second; ++it)
		{
			string tempto = (*it).second;
			if(check[tempto])
				continue;

			check[tempto] = true;

			que.push(tempto);
			result[tempto] = curr;
		}
	}

	if (flag)
	{
		vector<string> re;
		re.push_back(to);
		while(!result[to].empty())
		{
			re.push_back(result[to]);
			to = result[to];
		}

		for(int i = re.size() - 1; i >= 0; i--)
		{
			if(i == re.size() - 1)
				cout << re[i];
			else
				cout << " " << re[i];
		}
		cout << endl;
	}
	else
		cout << "no route found" << endl;
}

int main()
{
	int n;
	while(cin >> n && n > 0)
	{
		paths.clear();
		result.clear();
		check.clear();

		string temp;
		string from, to;
		getline(cin, temp);

		for(int i = 0; i < n; i++)
		{
			getline(cin, temp);
			istringstream iss(temp);
			
			iss >> from;
			check[from] = false;
			while(iss >> to)
			{
				paths.insert(pair<string, string>(from, to));
				paths.insert(pair<string, string>(to, from));
			}
		}

		cin >> from >> to;
		bfs(from, to);
	}
	return 0;
}

