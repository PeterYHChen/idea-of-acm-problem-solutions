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
