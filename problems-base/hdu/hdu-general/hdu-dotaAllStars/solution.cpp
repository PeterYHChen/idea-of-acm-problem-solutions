#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
#define DEBUG 0 
#define db(x) {if(DEBUG) x}

int n;
struct Weapon{
	string name;
	int value;
};

struct Bag{
	string name;
	int num;
};

struct Formula{
	string name;
	int size;
	string subitem[101];
};

Weapon weapon[101];
Bag bag[101];
Formula formula[101];
int n1, n2, n3, n4;

int BFS()
{
	cin >> n4;

	queue<string> qname;
	string temp;
	int tnum;

	for(int i = 1; i <= n4; i++)
	{
		cin >> temp >> tnum;
		while(tnum--)
			qname.push(temp);
	}
	
	string curr;
	int total = 0;
	while(!qname.empty())
	{
		curr = qname.front();
		qname.pop();

		bool flag = false;
		for(int i = 1; i <= n2; i++)
		{
			if(bag[i].name == curr && bag[i].num > 0)
			{
				bag[i].num--;
				flag = true;
				break;
			}
		}
		if(flag)
			continue;

		flag = false;
		for(int i = 1; i <= n1; i++)
		{
			if(weapon[i].name == curr)
			{
				total += weapon[i].value;	
				flag = true;
			}
		}

		if(flag)
			continue;

		for(int i = 1; i <= n3; i++)
		{
			if(formula[i].name == curr)
			{
				for(int j = 1; j <= formula[i].size; j++)
					qname.push(formula[i].subitem[j]);

				break;
			}
		}

	}
	return total;
}

int main()
{
	while(cin >> n1)
	{
		for(int i = 1; i <= n1; i++)		
			cin >> weapon[i].name >> weapon[i].value;

		cin >> n2;

		for(int i = 1; i <= n2; i++)		
			cin >>bag[i].name >>bag[i].num;
		
		cin >> n3;

		for(int i = 1; i <= n3; i++)		
		{
			int count = 0;
			char ch;
			
			cin >> formula[i].subitem[++count];
			while(cin >> ch && ch != '=')
				cin >> formula[i].subitem[++count];
			
			formula[i].size = count;
			cin >> formula[i].name;
		}

		
		cout << BFS() << endl;
	}

	return 0;
}
