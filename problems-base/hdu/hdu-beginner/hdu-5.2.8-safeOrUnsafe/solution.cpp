#include <iostream>
#include <string>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int cnt[26];

struct Node{
	char symbol;
	int freq;
	Node* next[2];
};

class comp{
public:
	bool operator()(Node &a, Node &b)
	{
		return a.freq > b.freq;
	}
};

void init()
{
	memset(cnt, 0, sizeof(cnt));
}

int calsize(Node* root, int i)
{
	if(root->next[0] == NULL || root->next[1] == NULL)	
			return i * cnt[root->symbol - 'a'];

	return calsize(root->next[0], i + 1) + calsize(root->next[1], i + 1); 
}

void deltree(Node* root)
{
	for(int i = 0; i < 2; i++)
		if(root->next[i] != NULL)
			deltree(root->next[i]);

	free(root);
}

int huffman()
{
	priority_queue<Node, vector<Node>, comp> qnode;

	Node* root = (Node*)malloc(sizeof(Node));

	for(int i = 0; i < 26; i++)
		if(cnt[i] != 0)
		{
			root->symbol = i + 'a';
			
			root->freq = cnt[i];
			root->next[0] = root->next[1] = NULL;

			qnode.push(*root);
		}
	
	if(qnode.size() == 1)
		return qnode.top().freq;

	while(qnode.size() > 1)
	{
		root->freq = 0;

		for(int i = 0; i < 2; i++)
		{
			root->next[i] = (Node*)malloc(sizeof(Node));
			*(root->next[i]) = qnode.top();
			qnode.pop();

			root->freq += root->next[i]->freq;
		}

		qnode.push(*root);
	}
	
	(*root) = qnode.top();
	
	int result = calsize(root, 0);

	deltree(root);

	return result;
}

int main()
{
	int testcase;
	
	cin >> testcase;

	while(testcase--)
	{
		init();
		
		int n;
		string s;
		
		cin >> n >> s;

		for(int i = 0; i < s.size(); i++)
			cnt[s[i] - 'a']++;

		int result = huffman();
		if(result < n)
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}

	return 0;
}
