/**
题目：求这样的四个自然数p,q,r,s(p<=q<=r<=s)，使得以下等式成立：
1/p+1/q+1/r+1/s=1


https://blog.csdn.net/csy981848153/article/details/7625938

--
p:2 q:3 r:12 s:12
p:2 q:4 r:6 s:12
p:2 q:4 r:8 s:8
p:2 q:5 r:5 s:10
p:2 q:6 r:6 s:6
p:3 q:3 r:4 s:12
p:3 q:3 r:6 s:6
p:3 q:4 r:4 s:6
p:4 q:4 r:4 s:4

*/

#include <iostream>
using namespace std;

int main(void)
{
    for (int p = 1; p != 5; ++p)
        for (int q = p; q != 7; ++q)
            for (int r = q; r != 13; ++r)
                for (int s = r; s != 13; ++s)
                {
                    if (q * r * s + p * r * s + p * q * s + p * q * r == p * q * r * s)
                    {
                        cout << "p:" << p << " "
                             << "q:" << q << " "
                             << "r:" << r << " "
                             << "s:" << s << endl;
                    }
                }
    return 1;
}