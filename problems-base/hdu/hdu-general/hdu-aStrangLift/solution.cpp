#include <iostream>
#include <queue>
#include "string.h"

using namespace std;

struct Node
{
	int level;
	int floor;
};

bool marked[201];
int jumpSize[201];

queue<Node> qnode;

int main()
{
	int n, a, b;
	while(cin >> n && n)
	{
		cin >> a >> b;

		memset(marked, 0, sizeof(marked));
		memset(jumpSize, 0, sizeof(jumpSize));
		while(!qnode.empty())
			qnode.pop();
		
		for(int i = 1; i <= n; i++)
		{
			cin >> jumpSize[i];
		}

		Node curr, temp;
		curr.floor = a;
		curr.level = 0;

		qnode.push(curr);

		while(!qnode.empty())
		{
			curr = qnode.front();
			temp = curr;
			qnode.pop();

			temp.level += 1;
			if(temp.level > n)
				break;
			
			if(curr.floor == b)
				break;

			//press up
			temp.floor = curr.floor + jumpSize[curr.floor]; 
			if(temp.floor <= n && !marked[temp.floor])
			{
				qnode.push(temp);
				marked[temp.floor] = true;
			}

			//press down
			temp.floor = curr.floor - jumpSize[curr.floor]; 
			if(temp.floor >= 1 && !marked[temp.floor])
			{
				qnode.push(temp);
				marked[temp.floor] = true;
			}
		}
		
		if(curr.floor == b)
			cout << curr.level << endl;
		else
			cout << -1 << endl;
	}

	return 0;
}
