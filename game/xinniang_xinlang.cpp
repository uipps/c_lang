/*
  新娘和新郎,
题目：三对情侣参加婚礼，三个新郞为A、B、C，三个新娘为X、Y、Z。有人不知道谁和谁结婚，于是询问了六位新人中的三位，
但听到的回答是这样的：A说他将和X结婚；X说她的未婚夫是C；C说他将和Z结婚。这人听后知道他们在开玩笑，全是假话。请编程找出谁将和谁结婚。

参考： https://blog.csdn.net/csy981848153/article/details/7626779

--
新娘X和新郎B是一对情侣！
新娘Z和新郎A是一对情侣！
新娘Y和新郎C是一对情侣！

*/

#include <iostream>
using namespace std;

void outRe(int te);

int main(void)
{
    int t = 0;
    int a = 1, b = 2, c = 3;
    int x = 0, y = x, z = x;

    for (x = 1; x != 4; ++x)
    {
        if ((x != a) && (x != c))
        {
            cout << "新娘X和";
            outRe(x);
            break;
        }
    }

    for (z = 1; z != 4; ++z)
    {
        if ((z != c) && (z != x))
        {
            cout << "新娘Z和";
            outRe(z);
            break;
        }
    }

    for (y = 1; y != 4; ++y)
    {
        if ((y != x) && (y != z))
        {
            cout << "新娘Y和";
            outRe(y);
            break;
        }
    }
    return 1;
}

void outRe(int te)
{
    switch (te)
    {
    case 1:
        cout << "新郎A是一对情侣！" << endl;
        break;

    case 2:
        cout << "新郎B是一对情侣！" << endl;
        break;

    case 3:
        cout << "新郎C是一对情侣！" << endl;
        break;

    default:
        break;
    }
}
