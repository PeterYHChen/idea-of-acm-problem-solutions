## solution.cpp
```cpp
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
```
## test.in
```cpp
4
欢欣之刃 100
敏捷之靴 20
半兽人之斧 100
力量腰带 50
2
散华 1
力量腰带 2
3
欢欣之刃 + 敏捷之靴 = 散华
半兽人之斧 + 力量腰带 = 夜叉
散华 + 夜叉 = 散夜对剑
1
散夜对剑 2

5
鹰角弓 3200
短棍 1100
攻击之爪 950
阔剑 1200
恶魔刀锋 2600
0
3
鹰角弓 + 短棍 = 蝴蝶
攻击之爪 + 阔剑 = 水晶剑
水晶剑 + 恶魔刀锋 = 大炮
2
蝴蝶 1
大炮 1
```
