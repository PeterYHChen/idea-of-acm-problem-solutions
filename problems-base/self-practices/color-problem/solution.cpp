#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <queue>

using namespace std;

const long bitsetSize = 100000;

struct Node
{
    int color;
    unordered_set<string> adjName;
};

unordered_map<string, Node> nodeMap;

int addRelation(string a, string b)
{
    unordered_map<string, Node>::iterator it = nodeMap.find(a);
    if(it == nodeMap.end()) // not exist
    {
        Node tempNode;
        tempNode.color = 0;
        tempNode.adjName.insert(b);
        pair<string, Node> tempPair(a, tempNode);
        nodeMap.insert(tempPair);

        it = nodeMap.find(a);
    }
    else
        ((it->second).adjName).insert(b);

    return ((it->second).adjName).size();
}

int main()
{
    int n;
    cin >> n;

    string s, a, b;
    bool hasRelation;
    int pos;
    string maxDegreeString;
    int maxDegree = 0;

    while(n--)
    {
        cin >> s >> hasRelation;
        if(!hasRelation)
            continue;
        
        pos = s.find('-');
        a = s.substr(0, pos);
        b = s.substr(pos+1);

        int temp = addRelation(a, b);
        if(maxDegree < temp)
        {
            maxDegree = temp;
            maxDegreeString = a;
        }
 
        temp = addRelation(b, a);
        if(maxDegree < temp)
        {
            maxDegree = temp;
            maxDegreeString = b;
        }
    }

    string current;
    queue<string> q;
    unordered_set<string>* currentSet;
    bitset<bitsetSize> colors;

    q.push(maxDegreeString);
    while(!q.empty())
    {
        colors.reset();

        current = q.front();
        q.pop();

        currentSet = &(nodeMap[current].adjName);
        // check adjacent colors
        for(unordered_set<string>::iterator it = currentSet->begin(); it != currentSet->end(); it++)
            colors.set(nodeMap[*it].color);

        // assign color to current node
        for(unordered_set<string>::size_type i = 1; i < colors.size(); i++)
            if(!colors[i])
            {
                nodeMap[current].color = i;
                break;
            }

        // add the adjacent nodes to the queue
        for(unordered_set<string>::iterator it = currentSet->begin(); it != currentSet->end(); it++)
            // do not have color
            if(!nodeMap[*it].color)
                q.push(*it);
    }

    // output assigned color for each node
    for(unordered_map<string, Node>::iterator it = nodeMap.begin(); it != nodeMap.end(); it++)
    {
        cout << "The color of " << it->first << " is: " << (it->second).color << endl;
    }

    return 0;
}