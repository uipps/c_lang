/*
计算分数的精确值
题目：使用数组精确计算M/N的值。如果M/N是无限循环小数，则计算并输出它的第一循环节，同时要求输出 循环节的起止位置。

https://blog.csdn.net/csy981848153/article/details/7626777

--


*/

#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    int a, b;
    int t1 = 0, t2 = 0;
    int iLoca = 0;
    vector<int> iVal;
    bool tem = true;
    cout << "请输入你要求的2个数:" << endl;
    cin >> a >> b;
    cout << a << "/" << b << "结果为：" << endl;
    while (1)
    {
        t1 = a % b;
        if (tem)
            iVal.push_back(a / b);
        if (t1 == a)
        {
            a = t1 * 10;
            tem = true;
        }
        else
        {
            a = t1;
            tem = false;
        }
        if (t1 == 0)
            break;
        if (t1 == t2 && !tem)
        {
            iLoca = iVal.size() - 1;
            break;
        }
        t2 = t1;
    }
    if (iLoca == 0)
    {
        cout << "有限小数:";
        cout << iVal[0] << ".";
        for (int i = 1; i != iVal.size(); ++i)
        {
            cout << iVal[i];
        }
    }
    else
    {
        cout << "无限循环小数:";
        cout << iVal[0] << ".";
        for (int i = 1; i != iVal.size(); ++i)
        {
            cout << iVal[i];
        }
        cout << "从第" << iLoca << "位小数开始循环";
    }
    cout << endl;
    return 1;
}