#include <iostream>
#include <string.h>
#include <queue>
#include <cmath>

using namespace std;

#define DEBUG 1
#define db(x) {if(DEBUG) x;}

int n, k, m, result;
bool marked[2011];

struct Node{
	int value, step, parent;
	char ch;
};

Node anode[2011];
Node curr, temp;

int BFS(Node &s)
{
	queue<Node> qnode;
	qnode.push(s);

	int count = 0;
	
	while(!qnode.empty())
	{
		curr = qnode.front();
		qnode.pop();

		anode[count] = curr;

		if((curr.value % k + k) % k == result)
			return curr.step;

		temp.step = curr.step + 1;

		//+
		temp.value = curr.value + m;
		if(temp.value <= 1000 && temp.value >= -1000 && !marked[temp.value + 1000])
		{
			temp.parent = count;
			temp.ch = '+';
			qnode.push(temp);
			marked[temp.value + 1000] = true;
		}

		//-
		temp.value = curr.value - m;
		if(temp.value <= 1000 && temp.value >= -1000 && !marked[temp.value + 1000])
		{
			temp.parent = count;
			temp.ch = '-';
			qnode.push(temp);
			marked[temp.value + 1000] = true;
		}

		//*
		temp.value = curr.value * m;
		if(temp.value <= 1000 && temp.value >= -1000 && !marked[temp.value + 1000])
		{
			temp.parent = count;
			temp.ch = '*';
			qnode.push(temp);
			marked[temp.value + 1000] = true;
		}
		
		//%
		temp.value = curr.value % m;
		if(temp.value <= 1000 && temp.value >= -1000 && !marked[temp.value + 1000])
		{
			temp.parent = count;
			temp.ch = '%';
			qnode.push(temp);
			marked[temp.value + 1000] = true;
		}

		count++;
	}

	return 0;
}
int main()
{
	while(cin >> n >> k >> m && k > 1 && m)
	{
		memset(marked, 0, sizeof(marked));
		memset(anode, 0, sizeof(anode));
		result = ((n + 1) % k + k) % k;
		
		Node s;
		s.value = n;
		s.step = 0;
		s.ch = '0';
		s.parent = 0;
		
		int step = BFS(s);
		cout << step << endl;
	
		char val[6];
		for(int i = 0; i < step; i++)
		{
			val[i] = curr.ch;
			curr = anode[curr.parent];
		}
		for(int i = step - 1; i >= 0; i--)
			cout << val[i];
		
		if(step)
			cout << endl;
	 }

	return 0;
}

