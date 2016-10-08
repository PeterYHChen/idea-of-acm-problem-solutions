## solution.cpp
```cpp
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
```
## test.in
```cpp
66
B:a-A:a 0
C:a-A:a 1
D:a-A:a 1
A:b-A:a 0
B:b-A:a 0
C:b-A:a 1
D:b-A:a 1
A:c-A:a 0
B:c-A:a 0
C:c-A:a 1
D:c-A:a 1
C:a-B:a 1
D:a-B:a 1
A:b-B:a 0
B:b-B:a 0
C:b-B:a 1
D:b-B:a 1
A:c-B:a 0
B:c-B:a 0
C:c-B:a 1
D:c-B:a 1
D:a-C:a 1
A:b-C:a 1
B:b-C:a 1
C:b-C:a 0
D:b-C:a 1
A:c-C:a 1
B:c-C:a 1
C:c-C:a 0
D:c-C:a 1
A:b-D:a 1
B:b-D:a 1
C:b-D:a 1
D:b-D:a 0
A:c-D:a 1
B:c-D:a 1
C:c-D:a 0
D:c-D:a 0
B:b-A:b 0
C:b-A:b 1
D:b-A:b 1
A:c-A:b 0
B:c-A:b 0
C:c-A:b 1
D:c-A:b 1
C:b-B:b 1
D:b-B:b 1
A:c-B:b 0
B:c-B:b 0
C:c-B:b 1
D:c-B:b 1
D:b-C:b 1
A:c-C:b 1
B:c-C:b 1
C:c-C:b 0
D:c-C:b 1
A:c-D:b 1
B:c-D:b 1
C:c-D:b 0
D:c-D:b 0
B:c-A:c 0
C:c-A:c 1
D:c-A:c 1
C:c-B:c 1
D:c-B:c 1
D:c-C:c 0
```
