#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define MAX 26

struct TriNode{
	int count;
	TriNode* next[MAX];
};

void insert(TriNode* root, string s)
{
	TriNode *p = root;

	for(int i = 0; i < s.size(); i++)
	{
		if(p->next[s[i] - 'a'] == NULL)
		{
			p->next[s[i] - 'a'] = (TriNode*)malloc(sizeof(TriNode));
			p = p->next[s[i] - 'a']; 

			for(int i = 0; i < MAX; i++)
				p->next[i] = NULL;
			p->count = 1;
		}
		else
		{
			p = p->next[s[i] - 'a']; 
			p->count++;	
		}
	}
}

int find(TriNode* root, string s)
{
	TriNode *p = root;

	for(int i = 0; i < s.size(); i++)
	{
		if(p->next[s[i] - 'a'] == NULL)
			return 0;

		p = p->next[s[i] - 'a'];
	}	

	return p->count;
}

void del(TriNode* root)
{
	for(int i = 0; i < MAX; i++)
	{
		if(root->next[i] != NULL)
			del(root->next[i]);
	}

	free(root);
}

int main()
{
	string s;
	TriNode* root = (TriNode*)malloc(sizeof(TriNode));
	
	for(int i = 0; i < MAX; i++)
		root->next[i] = NULL;
	root->count = 0;

	while(getline(cin, s))	
	{
		if(s == "")
			break;
	
		insert(root, s);
	}

	while(cin >> s)
	{
		printf("%d\n", find(root, s));
	}
	
	del(root);
	
	return 0;
}
