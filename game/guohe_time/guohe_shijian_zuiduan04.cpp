/*
问题是这样的：  (参考： https://blog.csdn.net/keepcoral/article/details/80047719 )

n个人过河，只有一条船，一条船最多装两个人，来回时间以最多那个人为标准，问过河最短时间

首先这个问题需要分类讨论假设有m个人，按时间大小排好序
m==1时，只有一个人过河 ,t+=a[1]
m==2时，两个人过河，直接t取大的,t+=a[2]
m==3时，三个人过河，先让最快的载最慢的过河，然后最快的回来，再载次快的过河,t+=a[3]+a[1]+a[2]
m>=4时，这里要用到贪心

无论m多大，我们只看4个人，最快 次最快 最慢 次最慢
一般我们能想到的就是第一种做法，让最快的载最慢的，然后最快的回来，再载次最慢的，然后最快的回来，
这里我们不需要管次最快的，这里我们就减少了两个人了，因此m-=2,在去判断，m在哪个范围再进行求解就好了。
第二种，先给个样例 1 2 1000 1000 ，这个显然用第一种做法，是行不通的，1000+1+1000=2001，
我们显然可以知道，先让最快和次快过河，然后最快回来，然后最慢和次慢过河，然后次快回来，2+1+1000=1003，贪心取时间最短，
所以这就是最短时间的做法，这里我们还是没有把最快和次最快过河，因此还是减少两人，m-=2。
用上面两种做法，一直循环到边界就可以得出答案了。

--
以下是解题程序

cd /D E:\develope\c\c_win10\game\guohe_time\
g++ guohe_shijian_zuiduan04.cpp -o guohe_shijian_zuiduan04
guohe_shijian_zuiduan04.exe

输入：
1       （表示做几次题目，这里就1吧）
4       （一共几个人, 1个、2个、3个、4个人都行，超过4个人的也行）
1 2 5 10    （每个人的过河时间）
17          (输出的答案)
一轮循环结束

也可以输入5个人
1
5
1 2 5 10 11
24          (输出的答案)

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int a[1009];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, i, j, m, ans = 0;
        scanf("%d", &n);
        for (i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
        }
        sort(a + 1, a + 1 + n);
        m = n;
        while (m > 0)
        {
            if (m >= 4)
            {
                if (a[m] + a[m - 1] + 2 * a[1] > a[2] + a[1] + a[m] + a[2])
                {
                    ans += a[2] + a[1] + a[m] + a[2];
                }
                else
                {
                    ans += a[m] + a[m - 1] + 2 * a[1];
                }
                m -= 2;
            }
            else if (m == 3)
            {
                ans += a[m] + a[1] + a[2];
                m = 0;
            }
            else if (m == 2)
            {
                ans += a[m];
                m = 0;
            }
            else if (m == 1)
            {
                ans += a[m];
                m = 0;
            }
        }
        printf("%d\n", ans);
    }
}
