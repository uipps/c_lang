/*
题目：按递增顺序依次列出所有分母为40，分子小于40的最简分数

*/

#include <iostream>

using namespace std;
bool isGong(int a, int b = 40); //求最大公约数的函数

int main(void)
{
    cout << "在分母为40的真分数为：" << endl;
    for (int i = 1; i != 41; ++i)
    {
        if (isGong(i))
        {
            cout << i << "/40 ";
        }
    }
    cout << endl;
    return 1;
}

bool isGong(int a, int b)
{
    int t = 0;
    while (1)
    {
        t = b % a;
        if (a == 1)
            return true;
        if (t == 0)
            break;
        b = a;
        a = t;
    }
    return false;
}