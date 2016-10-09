## solution.cpp
```cpp
#include <iostream>
#include <vector>
using namespace std;


bool canPartition(vector<int>& nums) {
    int sum = 0;
    bool array[10001];

    for(int i = 0; i < nums.size(); i++)
    {
        sum += nums[i];
    }
    cout << endl;

    if(sum % 2 == 1)
        return false;
    sum /= 2;

    for(int i = sum*2; i > 0; i--)
        array[i] = false;
    array[0] = true;
    
    for(int i = 0; i < nums.size(); i++)
    {
        for(int j = sum*2; j >= nums[i]; j--)
            if(array[j-nums[i]])
                array[j] = true;
    }
    
    if(array[sum])
        return true;
    return false;
}

int main()
{
    int n;
    while(cin >> n)
    {
        vector<int> nums;
        while(n--)
        {
            int val;
            cin >> val;
            nums.push_back(val);
        }
        cout << "can partition? " << (canPartition(nums)? "Yes" : "No") << endl;
    }
    return 0;
}
```
## test.in
```cpp
4 1 5 11 5
```
