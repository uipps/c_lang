/*
poj 1700（贪心——两人坐船过河） 参考： http://www.voidcn.com/article/p-fhrpimeb-bks.html , https://blog.csdn.net/weiguang_123/article/details/7686724
  http://www.voidcn.com/article/p-sfmbjibt-bps.html


题目：
  4人要过河，一个船能乘2人，船的运行速度为2人中较慢一人的速度，问把n个人运到对岸，最少需要多久。
  我们设最快的为a，次快的为b，最慢的为z，次慢的为y。
  我们先考虑如何将y,z运到对岸，可以ab,a,yz,b，也可以ay,a,az,a。
  运送z不可能影响此4人之外的人，因为船只能乘2人，z要带也是带次慢的。
  通过不等式可以证明如果单运y,z比一起运快，那么yx一起运绝对比单运y,x慢，所以不用考虑单运z必然单运y
  这样每次运最后两个可以一直让总数减少直到3个以内，直接处理即可

-- 解题思路：
道题如果理解了就不难了，可分为一步步两个永远最快的a[0],a[1]载现存的两个最慢的过河的问题，
一种是最快a[0]载现存最慢过去，0再回来，再载次慢，0再回来，时间为2*a[0]+t[p-2]+t[p-1]，或者01过去，
0回来，34过去(不可能0再载3或者4过去，那就浪费了第一次0载1过去的意义，等于在第一种方案基础上把34载过去又把2载过去2回来，
时间为a[0]+2*a[1]+t[p-1],再根据更新的数据，比较大小，继续选定方案.

--  以下是解题程序
cd /D E:\develope\c\c_win10\game\guohe_time\
g++ guohe_shijian_zuiduan01.cpp -o guohe_shijian_zuiduan01
guohe_shijian_zuiduan01.exe

（1）依次输入：
1
4
1 2 5 10
输出： 17

（2）依次输入：
1
4
2 3 8 10
输出： 21

*/


#include <iostream>
#include <algorithm>

using namespace std;

bool cmp(int a, int b)
{
    return a < b;
}

int main()
{
    int cnt, p, i, sum;
    int *a = new int[1005];
    cin >> cnt;
    while (cnt--)
    {
        sum = 0;
        cin >> p;
        for (int i = 0; i < p; i++)
            cin >> a[i];
        sort(a, a + p, cmp);
        for (i = p - 1; i > 2; i -= 2)
        {
            if (a[0] + 2 * a[1] + a[i] > 2 * a[0] + a[i - 1] + a[i]) //主要就在这两种坐船的方式，比较2a【1】和a[0]+a[i-1]的时间，由输入数据决定
                sum += 2 * a[0] + a[i - 1] + a[i];
            else
                sum += a[0] + 2 * a[1] + a[i];
        }
        if (i == 2)
            sum += a[0] + a[1] + a[2];
        else if (i == 1)
            sum += a[1];
        else
            sum += a[0];
        cout << sum << endl;
    }
    delete[] a;
    return 0;
}

/*
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

int n;
int a[1009];
int cal(int a, int b, int y, int z)
{
    return min(z + a + y + a, b + a + z + b);
}

void solve()
{
    int sum = 0;
    int i = n - 1;
    while (i > 2)
    {
        int m = cal(a[0], a[1], a[i - 1], a[i]);
        sum += m;
        i -= 2;
    }
    if (i == 2)
        sum += a[0] + a[1] + a[2];
    else
        sum += a[1];
    printf("%d\n", sum);
}
int main()
{
    int cas;
    cin >> cas;
    while (cas--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> a[i];
        sort(a, a + n);

        if (n == 1)
        {
            cout << a[0] << endl;
            continue;
        }
        else
            solve();
    }
    return 0;
}
*/