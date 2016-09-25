#include <iostream>
#include <string>
#include <stdio.h>
#include <map>

using namespace std;

map<string, string> pairsa;
map<string, string> pairsb;

int main()
{
	string tmp;
	string word, meaning;
	
	while(getline(cin, tmp))
	{
		if(tmp == "@END@")
			break;

		string::size_type idx = tmp.find(']');
		word = tmp.substr(0, idx + 1);
		meaning = tmp.substr(idx + 2, tmp.size() - idx - 1);

		pairsa[word] = meaning;
		pairsb[meaning] = word.substr(1, word.size() - 2);
		//cout << word << "--" << meaning << "---" << endl;
	}
	int n;

	scanf("%d\n", &n);
	
	map<string, string> *pairs;
	while(n--)
	{
		getline(cin, tmp);

		if(tmp[0] == '[')
			pairs = &pairsa;
		else
			pairs= &pairsb;

		if(pairs->find(tmp) != pairs->end())
			cout << pairs->find(tmp)->second << endl;
		else
			cout << "whats?" << endl;
	}
	return 0;
}
