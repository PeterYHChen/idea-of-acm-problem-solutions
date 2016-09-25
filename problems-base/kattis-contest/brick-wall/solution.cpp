/*************************************************************************
    > File Name: solution.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Fri 21 Nov 2014 10:43:34 AM AST
 ************************************************************************/

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int numbrick[4];
bool bad[310];

struct State
{
	int size;
	int c[3];
	bool equal(State a)
	{
		if(size == a.size && c[0] == a.c[0] && c[1] == a.c[1] && c[2] == a.c[2])
			return true;
		return false;
	}
};

class comp
{
public:
	bool operator() (const State& a, const State& b)
	{
		if(a.size > b.size)
			return true;
		else if (a.size == b.size)
		{
			if(a.c[0] > b.c[0])
				return true;
			else if(a.c[0] == b.c[0])
			{
				if(a.c[1] > b.c[1])
					return true;
				else if(a.c[1] == b.c[1])
					return a.c[2] > b.c[2];
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
};

priority_queue<State, vector<State>, comp> qstate;

int main()
{
	int k;
	cin >> k;
	while(k--)
	{
		int n;
		cin >> n;
		for(int i = 1; i <= 3; i++)
		{
			cin >> numbrick[i];
		}

		int sum = 0;
		for(int i = 1; i <= n; i++)
		{
			int temp;
			cin >> temp;
			sum += temp;
			bad[sum] = true;
		}
		//last size is good
		bad[sum] = false;

		//clear priority queue	
		while(qstate.size() > 0)
			qstate.pop();

		State temp, curr, pre;
		temp.size = 0;
		temp.c[0] = temp.c[1] = temp.c[2] = 0;
		
		pre.size = -1;

		qstate.push(temp);
		while(qstate.size() > 0)
		{
			curr = qstate.top();
			qstate.pop();
			
			for(int i = 1; i <= 3; i++)
			{
				if(bad[curr.size + i])
					continue;
				
				if(curr.c[i-1] + 1 > numbrick[i])
					continue;

				if(curr.equal(pre))
					continue;

				if(curr.size + i > sum)
					continue;
				
				temp = curr;
				temp.size += i;
				temp.c[i-1]++;
				
				if(temp.size == sum)
					break;
				
				qstate.push(temp);
			}
			
			if(temp.size == sum)
		 		break;

			pre = curr;
		}

		if(temp.size == sum)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	
	return 0;
}
