/*
真分数分解为埃及分数

题目：分子为1 的分数称为埃及分数，现输入一个真分数，请将该分数分解为埃及分数。
思路：用了贪婪算法+一些条件改良来求的。主要算法还是贪婪算法，所以不一定得到最优解。

参考： https://blog.csdn.net/csy981848153/article/details/7626766

--
7/13 = 1/2 + 1/26

*/

#include <iostream>

using namespace std;

int gongyueshu(int a, int b);

int main(void)
{
    int a1, b1, ra, zz, gong;
    while (true)
    {
        zz = 0;
        cout << "请输入分子：" << endl;
        cin >> a1;
        cout << "请输入分母: " << endl;
        cin >> b1;
        if (!b1)
        {
            cout << "分母不能为0！" << endl;
            continue;
        }
        cout << "结果为：" << a1 << "/" << b1 << "=";
        if (a1 >= b1)
        {
            while (a1 >= b1)
            {
                a1 -= b1;
                ++zz;
            }
        }
        while (a1 != 0)
        {
            if (a1 == 3)
            {
                cout << "1/" << b1 / 2 << "+";
                cout << "1/" << b1;
                break;
            }
            if (a1 == 1)
            {
                cout << "1/" << b1;
                break;
            }
            ra = b1 / a1 + 1;
            gong = ra * b1 / gongyueshu(b1, ra);
            a1 = (a1 * gong / b1) - (1 * gong / ra);
            b1 = gong;
            cout << "1/" << ra << "+";
        }
        while (zz--)
        {
            cout << "+1";
        }
        cout << endl;
    }
    return 1;
}

int gongyueshu(int a, int b) //最大公约数
{
    int ma, mi, t;
    ma = a > b ? a : b;
    mi = a > b ? b : a;
    while (mi)
    {
        t = ma % mi;
        ma = mi;
        if (!t)
            return mi;
        mi = t;
    }
    return 1;
}
