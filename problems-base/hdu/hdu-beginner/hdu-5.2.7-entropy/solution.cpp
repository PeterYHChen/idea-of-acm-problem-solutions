#include <iostream>
#include <string>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int cnt[27];

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
	{
		//cout << root->symbol << " " << i << endl;

		if(root->symbol == '_')
			return i * cnt[26];
		else
			return i * cnt[root->symbol - 'A'];
	}
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

	for(int i = 0; i <= 26; i++)
		if(cnt[i] != 0)
		{
			if(i == 26)
				root->symbol = '_';
			else
				root->symbol = i + 'A';
			
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
	string s;

	while(cin >> s && s != "END")
	{
		init();
		for(int i = 0; i < s.size(); i++)
		{
			if(s[i] == '_')
				cnt[26]++;
			else
				cnt[s[i] - 'A']++;
		}
		
		int	temp = huffman();

		double ratio = (s.size()*8)/(double)temp;

		printf("%d %d %.1f\n", s.size()*8, temp, ratio);
	}

	return 0;
}
