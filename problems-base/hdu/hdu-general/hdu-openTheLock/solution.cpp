#include <iostream>
#include <queue>
#include <string.h>
#include <stdio.h>

using namespace std;

struct Node{
	int level;
	int value;
};

bool marked[10000];

int combine(int a, int b, int c, int d)
{
	return a*1000 + b*100 + c*10 + d;
}

int BFS(Node &s, Node &e)
{
	queue<Node> qnode;
	qnode.push(s);

	Node curr, temp;

	while(!qnode.empty())
	{
		curr = qnode.front();
		qnode.pop();
		
		if(curr.value == e.value)
			return curr.level;
		
		int a = curr.value/1000;
		int b = (curr.value % 1000)/100;
		int c = (curr.value % 100)/10;
		int d = curr.value % 10;
	
		temp.level = curr.level + 1;
		
		temp.value = (a == 9? combine(1, b, c, d):combine(a+1, b, c, d));
		if(!marked[temp.value])	
		{
			qnode.push(temp);
			marked[temp.value] = true;
		}

		temp.value = (b == 9? combine(a, 1, c, d):combine(a, b+1, c, d));
		if(!marked[temp.value])	
		{
			qnode.push(temp);
			marked[temp.value] = true;
		}

		temp.value = (c == 9? combine(a, b, 1, d):combine(a, b, c+1, d));
		if(!marked[temp.value])	
		{
			qnode.push(temp);
			marked[temp.value] = true;
		}

		temp.value = (d == 9? combine(a, b, c, 1):combine(a, b, c, d+1));
		if(!marked[temp.value])	
		{
			qnode.push(temp);
			marked[temp.value] = true;
		}
		temp.value = (a == 1? combine(9, b, c, d):combine(a-1, b, c, d));
		if(!marked[temp.value])	
		{
			qnode.push(temp);
			marked[temp.value] = true;
		}

		temp.value = (b == 1? combine(a, 9, c, d):combine(a, b-1, c, d));
		if(!marked[temp.value])	
		{
			qnode.push(temp);
			marked[temp.value] = true;
		}

		temp.value = (c == 1? combine(a, b, 9, d):combine(a, b, c-1, d));
		if(!marked[temp.value])	
		{
			qnode.push(temp);
			marked[temp.value] = true;
		}

		temp.value = (d == 1? combine(a, b, c, 9):combine(a, b, c, d-1));
		if(!marked[temp.value])	
		{
			qnode.push(temp);
			marked[temp.value] = true;
		}
		temp.value = combine(b, a, c, d);
		if(!marked[temp.value])	
		{
			qnode.push(temp);
			marked[temp.value] = true;
		}

		temp.value = combine(a, c, b, d);
		if(!marked[temp.value])	
		{
			qnode.push(temp);
			marked[temp.value] = true;
		}

		temp.value = combine(a, b, d, c);
		if(!marked[temp.value])	
		{
			qnode.push(temp);
			marked[temp.value] = true;
		}
	
	}
	return -1;
}

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int start, end;
		cin >> start >> end;
		
		Node s, e;
		memset(marked, 0, sizeof(marked));
		s.value = start;
		e.value = end;
		s.level = 0;

		cout << BFS(s, e) << endl;
	}

	return 0;
}
