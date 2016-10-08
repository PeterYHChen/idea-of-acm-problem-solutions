## solution.cpp
```cpp
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>

using namespace std;

int main()
{
	int n;
	while(cin >> n && n > 0)
	{
		string s;
		getline(cin, s);
		for(int i = 0; i < n; i++)
		{
			getline(cin, s);
			
			int pos = s.find("Simon says");
			
			if(pos < 0)
				continue;

			for(int i = pos+10; i < s.size(); i++)
				cout << s[i];
			cout << endl;
		}
	}
	return 0;
}
```
## test.in
```cpp
1
Simon says smile.
3
Simon says raise your right hand.
Lower your right hand.
Simon says raise your left hand.
3
Raise your right hand.
Lower your right hand.
Simon says raise your left hand.
```
