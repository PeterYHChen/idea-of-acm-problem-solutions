#include <iostream>
#include <string>

using namespace std;

string addStrings(string num1, string num2) {
    string result = "";
    int val;
    int maxs = max(num1.size(), num2.size());
    int carry = 0;

    for(int i = 1; i <= maxs; i++)
    {
        val = 0;
        if(num1.size() >= i){
            // cout << "num1: " << num1[num1.size()-i]-'0' << " size: " << num1.size()-i << endl;
            val += num1[num1.size()-i]-'0';

        }
        if(num2.size() >= i){
            // cout << "num2: " << num2[num2.size()-i]-'0' << " size: " << num2.size() << endl;
            val += num2[num2.size()-i] - '0';
        }
        val += carry;

        carry = val/10;
        val %= 10;
        cout << val << endl;
        char c = val + '0';
        result = c+result;
    }

    if (carry)
        result = '1' + result;

    return result;
}

int main()
{
    string s1, s2;
    while(cin >> s1 >> s2)	
    {
        cout << addStrings(s1, s2) << endl;
    }
}
