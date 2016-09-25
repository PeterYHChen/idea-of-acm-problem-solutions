#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>

using namespace std;
int n;

struct Node 
{
	int val;
	int cnt;
	Node* next[12];
};

int dfs(Node* parent)
{
	if (parent->val /10 == 0)
		return 0;
	int val;
	int cnt = 1;
	
	int max = 0;

	do
	{
		val = parent->val/(int)pow(10.0, cnt)*(int)pow(10.0, cnt-1) + parent->val%(int)pow(10.0, cnt-1);
		
		//cout << val << endl;
		if (parent->val % val == 0)
		{
			Node* curr = new Node;
			for(int i = 0; i < 12; i++)
				curr->next[i] = NULL;
			curr->val = val;
			parent->next[cnt-1] = curr;

			int count = dfs(curr);
			if (max < count)
				max = count;
		}
		cnt++;
	}
	while(parent->val/(int)pow(10.0, cnt-1) > 0);

	parent->cnt = max + 1;

	return parent->cnt;
}

void output(Node* root)
{
	int index = -1;
	int max = -1;
	for(int i = 0; i < 12; i++)
	{
		if (root->next[i] != NULL)
			if (max < root->next[i]->cnt)
			{
				index = i;
				max = root->next[i]->cnt;
			}
			else if (max == root->next[i]->cnt)
			{
				if (root->next[i]->val < root->next[index]->val)
					index = i;
			}
		
	}
	if (index >= 0)
	{
		cout << root->val << " ";
		output(root->next[index]);

	}
}

void freeTree(Node* root)
{
	for (int i = 0; i < 12; i++)
		if (root->next[i] != NULL)
		{
			freeTree(root->next[i]);
			delete root->next[i];
			root->next[i] = NULL;
		}
	
}

int main()
{
	while(cin >> n && n > 0)
	{
		Node* root = new Node;
		root->val = n;

		for(int i = 0; i < 12; i++)
			root->next[i] = NULL;

		dfs(root);		
		output(root);
	freeTree(root);
	}
	return 0;
}

