### Problem Dcription

##### Background 
Professor Hopper is researching the sexual behavior of a rare species of bugs. He assumes that they feature two different genders and that they only interact with bugs of the opposite gender. In his experiment, individual bugs and their interactions were easy to identify, because numbers were printed on their backs. 
 

##### Problem 
Given a list of bug interactions, decide whether the experiment supports his assumption of two genders with no homosexual bugs or if it contains some bug interactions that falsify it.
 

##### Input
The first line of the input contains the number of scenarios. Each scenario starts with one line giving the number of bugs (at least one, and up to 2000) and the number of interactions (up to 1000000) separated by a single space. In the following lines, each interaction is given in the form of two distinct bug numbers separated by a single space. Bugs are numbered consecutively starting from one.
 

##### Output
The output for every scenario is a line containing "Scenario #i:", where i is the number of the scenario starting at 1, followed by one line saying either "No suspicious bugs found!" if the experiment is consistent with his assumption about the bugs' sexual behavior, or "Suspicious bugs found!" if Professor Hopper's assumption is definitely wrong.


##### Sample Input
	3 3 
	1 2
	2 3
	1 3
	4 2
	1 2
	3 4
 

##### Sample Output
	Scenario #1:
	Suspicious bugs found!
	
	Scenario #2:
	No suspicious bugs found!


### Explanation

We can create a Merge-find set and apply union-find algorithm to it.

In find function, the parent index of each node is updated recursively so that all the nodes we search through will be connected to the root directly.
In union function, we find(a) and find(b), then connect the root of node a to the root of node b.

However, in this problem, we only have the inputs of 2 nodes in opposite side, so we have to record a rank value for each node telling whether they are in the same group or not.

Here, we only have two value for rank, 1 and 0, marking odd & even, and changes needed or no change needed for the rank value of each node under the tree.

Originally, rank[i] = 0 for i = 0 ~ n.
The root of each tree is always 0.

In find function, rank[x] = (rank[parentOf[x]] + rank[x]) & 1.
If parentOf[x] is 1, rank[x] will be changed from 1 to 0 or from 0 to 1. If parentOf[x] is 0, the rank[x] will not be changed.
It means that all the nodes between the target node and its root will be updated with the correct rank value and reassigned to the correct group. 

In union function, rank[root of a] = (rank[a] + rank[b] + 1) & 1. 
Because we try to connect the tree of node a to the tree of node b, the rank[root of b] remains 0 while the rank[root of a] should be decided. 
Because node a and b must be in opposite groups, we can indicate the tree of node a needs to be reset rank values by setting rank[root of a] to 1 if rank[a] == rank[b].
Here if rank[a] == rank[b], (rank[a] + rank[b] + 1) & 1 must be 1.
Also we indicate the tree of node a is remains stable(after find(each element), its rank value must be correct) by setting rank[root of a] to 0 if rank[a] != rank[b].
Here if rank[a] != rank[b], (rank[a] + rank[b] + 1) & 1 must be 1. (a and b are already in different group)

	#include <iostream>
	#include <stdio.h>
	#include <string.h>
	
	using namespace std;
	
	#define MAX 2010
	
	bool flag;
	int f[MAX], rank[MAX];
	
	int find(int x)
	{
	        if(f[x] == x)
	                return f[x];
	
	        int temp;
	
	        temp = f[x];
	        f[x] = find(f[x]);
	        rank[x] = (rank[x] + rank[temp]) & 1;
	        return f[x];
	}
	
	void myunion(int a, int b)
	{
	        int roota = find(a), rootb = find(b);
	
	        if(roota == rootb)
	        {
	                if(rank[a] == rank[b])
	                        flag = true;
	
	                return;
	        }
	
	        f[roota] = rootb;
	        rank[roota] = (rank[a] + rank[b] + 1) & 1;
	}
	
	int main()
	{
	        int t;
	        cin >> t;
	
	        int count = 1;
	        while(t--)
	        {
	                int n, inter;
	                scanf("%d%d", &n, &inter);
	
	                flag = false;
	                for(int i = 1; i <= n; i++)
	                {
	                        f[i] = i;
	                        rank[i] = 0;
	                }
	
	                int a, b;
	                for(int i = 0; i < inter; i++)
	                {
	                        scanf("%d%d", &a, &b);
	                        if(flag)
	                                continue;
	                        myunion(a, b);
	                }
	
	                printf("Scenario #%d:\n", count++);
	
	                if(flag)
	                        printf("Suspicious bugs found!\n");
	                else
	                        printf("No suspicious bugs found!\n");
	
	                        cout << endl;
	
	        }
	        return 0;
	}
