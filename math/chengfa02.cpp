/*
乘法计算: 只适合整数，没有小数点

*/
#include <bits/stdc++.h>
using namespace std;

int a[100], b[100], c[100];

int main()
{
    string s1, s2, t;
    cin >> s1 >> s2;

    for (int i = 0; i < s1.length(); i++)
    {
        a[i] = s1[s1.length() - i - 1] - '0';
    }
    for (int i = 0; i < s2.length(); i++)
    {
        b[i] = s2[s2.length() - i - 1] - '0';
    }

    for (int i = 0; i < s1.length(); i++)
    {
        int carry = 0;
        for (int j = 0; j < s2.length(); j++)
        {
            c[i + j] += a[i] * b[j] + carry;
            carry = c[i + j] / 10;
            c[i + j] %= 10;
        }
        // 每一遍循环之后的进位
        c[i + s2.length()] += carry;
    }

    int index = s1.length() + s2.length();

    //删除前导零
    while (c[index] == 0 && index > 0)
        index--;

    for (int i = index; i >= 0; i--)
        cout << c[i];

    cout << endl;
    return 0;
}