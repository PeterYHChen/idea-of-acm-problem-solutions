            {% raw %}
            # See you~
            
            Time Limit: 5000/3000 MS (Java/Others) Memory Limit: 65535/32768 K (Java/Others)
            Total Submission(s): 200 Accepted Submission(s): 67
            
            ### Problem Description
            Now I am leaving hust acm. In the past two and half years, I learned so many knowledge about Algorithm and Programming, and I met so many good friends. I want to say sorry to Mr, Yin, I must leave now ~~>.<~~. I am very sorry, we could not advanced to the World Finals last year. 
            
            When coming into our training room, a lot of books are in my eyes. And every time the books are moving from one place to another one. Now give you the position of the books at the early of the day. And the moving information of the books the day, your work is to tell me how many books are stayed in some rectangles. 
            
            To make the problem easier, we divide the room into different grids and a book can only stayed in one grid. The length and the width of the room are less than 1000. I can move one book from one position to another position, take away one book from a position or bring in one book and put it on one position. 
            
            
            ##### Input
            In the first line of the input file there is an Integer T(1<=T<=10), which means the number of test cases in the input file. Then N test cases are followed. 
            
            For each test case, in the first line there is an Integer Q(1<Q<=100,000), means the queries of the case. Then followed by Q queries. 
            
            There are 4 kind of queries, sum, add, delete and move. 
            
            example: 
            
            S x1 y1 x2 y2 means you should tell me the total books of the rectangle used (x1,y1)-(x2,y2) as the diagonal, including the two points. 
            
            A x1 y1 n1 means I put n1 books on the position (x1,y1) 
            
            D x1 y1 n1 means I move away n1 books on the position (x1,y1), if less than n1 books at that position, move away all of them.
            
            M x1 y1 x2 y2 n1 means you move n1 books from (x1,y1) to (x2,y2), if less than n1 books at that position, move away all of them. 
            
            Make sure that at first, there is one book on every grid and 0<=x1,y1,x2,y2<=1000,1<=n1<=100. 
            
            
            ##### Output
            At the beginning of each case, output "Case X:" where X is the index of the test case, then followed by the "S" queries. 
            
            For each "S" query, just print out the total number of books in that area. 
            
            
            ##### Sample Input
            	2
            	3
            	S 1 1 1 1
            	A 1 1 2
            	S 1 1 1 1
            	3
            	S 1 1 1 1
            	A 1 1 2
            	S 1 1 1 2
            
            
            ##### Sample Output
            	Case 1:
            	1
            	3
            	Case 2:
            	1
            	4
            
            ### Explanation
            As the problem require, we need to calculate the total books of any possible retangular bookshelf.
            
            Because queries could be at most 100,000, we need to both update and get the number of books on shelf at a suitable speed.
            
            **Brute-force method**
            
            We use shelf[1002][1002] to record the number of books on position [i][j].
            
            In one way, given width w and height h, we simple traversal all elements and O(w * h) number of operations are needed to get the sum, but we can update the value of corresponding index in O(1) directly.
            
            In another way, we use shelf[i][j] to store the total books of the retangle [1][1] to [i][j]. So we get the sum with shelf[x2][y2] - shelf[x1-1][y1-1] in O(1) complexity. 
            
            However, we need to update around (1001-w)*(1001-h) elements right after [i-1][j-1].
            
            **Therefore we need to use binary indexed tree, which allows to update value and query the sum of a range in O(log(n)) respectively.**
            
            **For better understanding, we start from one-dimentional binary indexed tree.**
            
            Given an array a[1] to a[n], c[1] to c[n] and the range [i,j].
            
            Because we try to get sum(i, j) = sum(1, j) - sum(1, i-1), we turn this problem into how to calculate the sum(1, j) in O(log(n)) complexity, where n is the number of elements between i and j.
            
            From the natural properties of binary, we know any integer = the sum of a certain combination of 2^k1 + 2^k2 + ... + 2^kt. 
            For example, 88 = 2^6 + 2^4 + 2^3, and that is how binary expression comes: 88 = 01011000. 
            So we can try to get sum(1, 88) = sum(1, 64) + sum(65, 80) + sum(81, 88). 
            What enlightens us here is that we can make c[64] = sum(a[1] to a[64]) = sum(1, 64), c[64+16] = c[80] = sum(65, 80), and c[88] = sum(81, 88), so that sum(1, 88) = c[64] + c[80] + c[88]. 
            In the worst case, m = 11...111(binary), and log(m) is the number of 1s in m, we get sum(1, m) with O(log(m)) complexity.
            
            But how can we ensure that c[i] stores the correct range of data? The concept of lowbit(x) = x & (-x) is introduced. 
            The function lowbit(x) returns the value of the first rightmost bit of x that is 1, e.g., lowbit(5) = lowbit(101) = 1, lowbit(88) = lowbit(1011000) = 1000 = 8.
            
            So we get c[88] = sum(81, 88) = sum(a[88-lowbit(88)+1], a[88]) = a[81] + a[82] + ... + a[88]. 
            
            In general, c[i] = sum(a[i-lowbit(i)+1], a[i]) = a[i-lowbit(i)+1] + ... + a[i].
            
            If we want to update the value of a[i], we have to update all the c[j]s that contain a[i], e.g., if a[88] is changed, c[64+24] = c[88], c[64+32], c[128], c[256], c[512] will need to be changed. 
            
            In the worst case, with the upper bound = m, we at most update O(log(m)) values in array c[].
            
            **Therefore, we achieve to goal of both updating and getting sum in O(log(n)) complexity.**
            
            	#define lowbit(x) (x & (-x))
            
            	// initialization of c[1] to c[n] with a[1] to a[n]
            	void init()
            	{
            		c[0] = 0;
            		for(int i = 1; i <= n; i++)
            		{
            			c[i] = 0;
            			for(int j = i - lowbit(i) + 1; j <= i; j++)
            				c[i] += a[j];
            		}
            	}
            
            	// get the sum of values in [1, m]
            	int sum(int m)
            	{
            		int result = 0;
            		for(int i = m; i > 0; i -= lowbit(i))
            			result += c[i];
            
            		return result;
            	}
            
            	// update array c[] when the value of a[i] is increased or decreased
            	void update(int i, int val)
            	{
            		for(; i <= n; i += lowbit(i))
            		{
            			c[i] += val;
            		}
            	}
            
            > Here is my AC code, explaining the implementation of 2-dimentional binary indexed tree.
            
            	#include <iostream>
            	#include <stdio.h>
            	
            	using namespace std;
            	
            	#define lowbit(x) (x & (-x))
            	#define MAXN 1002
            	
            	int shelf[MAXN][MAXN];
            	int origin[MAXN][MAXN];
            	
            	int init()
            	{
            	        for(int i = 1; i < MAXN; i++)
            	                for(int j = 1; j < MAXN; j++)
            	                {
            	                        origin[i][j] = 1;                                          
            	                        shelf[i][j] = lowbit(i) * lowbit(j);                       
            	                }                                                                  
            	}                                                                                  
            	                                                                                   
            	void update(int x, int y, int n)                                                   
            	{
            	        for(int i = x; i < MAXN; i += lowbit(i))
            	                for(int j = y; j < MAXN; j += lowbit(j))
            	                {
            	                        shelf[i][j] += n; 
            	
            	                        //cout << "update: " << shelf[i][j] << endl;
            	                }
            	}
            	
            	int sum(int x, int y)
            	{
            	        int result = 0;
            	        for(int i = x; i > 0; i -= lowbit(i))
            	                for(int j = y; j > 0; j -= lowbit(j))
            	                        result += shelf[i][j];
            	
            	        return result;
            	}
            	
            	void swap(int &a, int &b)
            	{
            	        int temp = a;
            	        a = b;
            	        b = temp;
            	}
            	
            	int main()
            	{
            	        int t, testcase = 0;
            	        cin >> t;
            	
            	        int q;
            	
            	        while(t--)
            	        {
            	                init();
            	
            	                cin >> q;
            	
            	                char task;
            	                int x1, y1, x2, y2, n;
            	
            	                printf("Case %d:\n", ++testcase);
            	
            	                while(q--)
            	                {
            	                        cin >> task;
            	                        switch(task)
            	                        {
            	                        case 'S':
            	                                scanf("%d%d%d%d*c", &x1, &y1, &x2, &y2);
            	                                x1++; y1++; x2++; y2++; // start counting from index 1
            	                                
            	                                // a small trick, ensure x1 < x2, y1 < y2
            	                                if(x1 > x2)
            	                                        swap(x1, x2);
            	                                if(y1 > y2)
            	                                        swap(y1, y2);
            	
            	                                printf("%d\n", sum(x1-1, y1-1) + sum(x2, y2) - sum(x1-1, y2) - sum(x2, y1-1));
            	
            	                                break;
            	
            	                        case 'A':
            	                                scanf("%d%d%d*c", &x1, &y1, &n);
            	                                x1++; y1++;
            	                                update(x1, y1, n);
            	
            	                                origin[x1][y1] += n;
            	
            	                                break;
            	
            	                        case 'D':
            	                                scanf("%d%d%d*c", &x1, &y1, &n);
            	                                x1++; y1++;
            	
            	                                if(n > origin[x1][y1])
            	                                        n = origin[x1][y1];
            	
            	                                origin[x1][y1] -= n;
            	
            	                                update(x1, y1, -n);
            	
            	                                break;
            	
            	                        case 'M':
            	                                scanf("%d%d%d%d%d*c", &x1, &y1, &x2, &y2, &n);
            	                                x1++; y1++; x2++; y2++;
            	
            	                                if(n > origin[x1][y1])
            	                                        n = origin[x1][y1];
            	
            	                                origin[x1][y1] -= n;
            	                                update(x1, y1, -n);
            	
            	                                origin[x2][y2] += n;
            	                                update(x2, y2, n);
            	
            	                                break;
            	                        }
            	
            	                }
            	
            	        }
            	        return 0;
            	}
            {% endraw %}
        {% raw %}
        # Tarjan's off-line lowest common ancestor algorithm (hdu2586)
        
        Time Limit: 2000/10000 MS (Java/Others) Memory Limit: 32768/32768 K (Java/Others)
        Total Submission(s): 142 Accepted Submission(s): 66
        
        ### Problem Description
        There are n houses in the village and some bidirectional roads connecting them. Every day peole always like to ask like this "How far is it if I want to go from house A to house B"? Usually it hard to answer. But luckily int this village the answer is always unique, since the roads are built in the way that there is a unique simple path("simple" means you can't visit a place twice) between every two houses. Yout task is to answer all these curious people.
         
        
        ##### Input
        First line is a single integer T(T<=10), indicating the number of test cases.
        For each test case,in the first line there are two numbers n(2<=n<=40000) and m (1<=m<=200),the number of houses and the number of queries. The following n-1 lines each consisting three numbers i,j,k, separated bu a single space, meaning that there is a road connecting house i and house j,with length k(0<k<=40000).The houses are labeled from 1 to n.
        Next m lines each has distinct integers i and j, you are to answer the distance between house i and house j.
         
        
        ##### Output
        For each test case,output m lines. Each line represents the answer of the query. Output a bland line after each test case.
         
        
        ##### Sample Input
        	2
        	3 2
        	1 2 10
        	3 1 15
        	1 2
        	2 3
        
        	2 2
        	1 2 100
        	1 2
        	2 1
         
        
        ##### Sample Output
        	10
        	25
        	100
        	100
        
        ### Explanation
        
        ##### Problem Analysis
        To some degree, this problem definition is very confined. We can easily construct a graph with houses as its nodes and roads as its edges. Specially, this graph is a strongly connected graph, which means every node could be reached by the other node in the same graph. Since paths are unique, no cycles are allowed, and thus something like a spanning tree could be constructed.
        
        Because the graph could be pretty big, with 40000 nodes at most and 39999 edges accordingly, an adjacency list is a better choice than an adjacent matrix to store the edges values. The number of queries is small (m <= 200).
        
        ##### Possible Solutions
        One method is to use BFS. For each query, starting from one node, loop through all its children, accumulate the distance to its children, and push them into a queue. Do it again and again, until the function meets another node. Then the accumulated distance is the final answer. O(m*n) complexity.
        
        Aother method is the Tarjan off-line lowest common ancestor algorithm, which I use in my code. The lowest common ancestor of two nodes a and b in a rooted tree T is the node g that is an ancestor of both a and b and that has the greatest depth in T. Starting from the root of a tree, go through each child with DFS, accumulate the distance from the root, calculate the LCA of node a and b, and get the result = (distance[a] + distance[b] - 2*distance[root]).
        
        ##### Details and Code
        Tarjan off-line LCA algorithm is based on the *union-find alogrithm*, and all queries should be stored in advance. 
        > (Please check my another doc **union_find_set-hdu1829** for more information)
        
        The tarjan() function is the main function in DFS loop. Each tarjan(**curr**) excutes the following steps,
        * loop through the queries
        * set **curr**'s parent to be itself
        (views the node **curr** as the root of a new tree)
        * set **curr**ent node to be visited
        * accumulate the distance to its children
        * traverse each child of it with tarjan(child)
        * and set the parent of its children to be itself
        (merge the subtrees with its children as roots back to **curr** node)
        
        
        Based on each new tree with **curr** as the root, there are visited children and non-visited children. When tarjan() visits one of the non-visited children, node a, it is easily to know the lowest common ancestor of node a and another visited node b by doing find(b) operation, which return **curr**. So each tarjan() function would loop through the queries to check if any of them could get the result.
        
        > Noticed that once subtrees are merged back to the **curr** node, find() function would work to find the LCA bewtween an visited node and an unvisited node.
        
        
        
        Here is my code:
        
        	#include <iostream>
        	#include <string>
        	#include <cstdio>
        	#include <cstring>
        	#include <cstdlib>
        	#include <vector>
        
        	using namespace std;
        
        	#define N 40002
        	#define M 202
        
        	struct Edge{
        		int to, len;
        	};
        
        	vector<Edge> vedge[N];// adjacency list
        
        	int n, m; 
        	int x[N], y[N], z[N];
        	int parentOf[N], dist[N]; 
        	bool mark[N];
        
        	void init(int n)
        	{
        		memset(mark, 0, sizeof(mark));
        
        		for(int i = 1; i <= n; i++)
        			vedge[i].clear();
        	}
        
        	void insert(int a, int b, int len)
        	{
        		Edge temp;
        		temp.len = len;
        
        		// start node a connects to b, with length = len
        		temp.to = b;
        		vedge[a].push_back(temp);
        
        		// start node b connects to a, with length = len
        		temp.to = a;
        		vedge[b].push_back(temp);
        	}
        
        	int find(int a)
        	{
        		if(a != parentOf[a])
        			parentOf[a] = find(parentOf[a]);
        
        		return parentOf[a];
        	}
        
        	// all non-visited children will be merged to the visited group as a tree after being visited
        	void tarjan(int curr)
        	{
        		// loop through all queries. 
        		// If node a is current node, and another node b has been visited before, find(b) returns their least common ancestor
        		for(int i = 1; i <= m; i++)
        		{
        			if(x[i] == curr && mark[y[i]])
        				z[i] = find(y[i]);
        			else if(y[i] == curr && mark[x[i]])
        				z[i] = find(x[i]);
        		}
        
        		mark[curr] = true;
        
        		// when tarjan dfs its children, curr would be recognized as the least common ancestor
        		parentOf[curr] = curr; 
        
        		int child;
        
        		// loop through all children that connect to curr
        		for(int i = 0; i < vedge[curr].size(); i++)
        		{
        			child = vedge[curr][i].to;
        
        			// avoid searching up to the curr 
        			if(!mark[child])
        			{
        				// accumulate distance from the root
        				dist[child] = dist[curr] + vedge[curr][i].len;
        			
        				// DFS a child of curr, establish a tree with child as the root 
        				tarjan(child);
        			
        				// merge the child tree back to curr, and make curr is the LCA between its children
        				parentOf[child] = curr;
        			}
        	
        		}
        	}
        
        	int main()
        	{
        		int t;
        		cin >> t;
        
        		while(t--)
        		{
        			cin >> n >> m;
        
        			init(n);
        		
        			int a, b, k;
        			for(int i = 1; i <= n-1; i++)
        			{
        				scanf("%d%d%d", &a, &b, &k);
        
        				// add houses to the adjacency list
        				insert(a, b, k);
        			}
        		
        			// store the queries
        			for(int i = 1; i <= m; i++)
        				scanf("%d%d", &x[i], &y[i]);
        
        			// any value could be chosen to be the root of the tree, picking value 1 does not have special meanings.
        			// set the distance of root to be 0
        			dist[1] = 0;
        			tarjan(1);
        
        			for(int i = 1; i <= m; i++)
        				printf("%d\n", dist[x[i]] + dist[y[i]] - 2 * dist[z[i]]);
        		}
        
        		return 0;
        	}
        {% endraw %}
    {% raw %}
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
    {% endraw %}
