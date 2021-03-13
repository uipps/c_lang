/*
问题是这样的：  (参考： https://blog.csdn.net/bodybo/article/details/819041 )
一天夜晚，有四个人要过一条河，河上有一座只能承受两人重量的桥，而且桥面路况很差，要手持手电筒才能顺利通过。
四人单独过河的时间分别为：2分钟、3分钟、8分钟和10分钟，并且只有一个手电筒。
问：四人都过河的最短时间是多少？

大概编程思想是这样的：
（1）从四人中任挑两人过河，记录时间（两人中的慢者所需时间）
（2）让快者返回，记录时间
（3）从三人中任挑两人过河，记录时间（两人中的慢者所需时间）
（4）让快者返回，记录时间
（5）剩下两人过河，记录时间（两人中的慢者所需时间）
（6）求总时间并暂时存储，与下一个总时间比较求小值。直到试遍所有可能的组合，即得到最短时间。

-- 
以下是解题程序

cd /D E:\develope\c\c_win10\game\guohe_time\
g++ guohe_shijian_zuiduan03.cpp -o guohe_shijian_zuiduan03
guohe_shijian_zuiduan03.exe

*/

#include <iostream>

using namespace std;

static int b[4] = {2, 3, 8, 10};
static int a[4];
int num1, num2, time = 0, result = 100;

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b, int c)
{
    a = a < b ? a : b;
    return a < c ? a : c;
}

void cross(int m, int n, int k, int r)
{
    int min, x, y, time2;
    time += max(b[m], b[n]);
    num1 = k - 2;
    num2 = 4 - num1;

    if (num2 == 2)
    {
        if (b[m] < b[n])
        {
            min = b[m];
            x = m;
            y = n;
        }
        else
        {
            min = b[n];
            x = n;
            y = m;
        }
    }
    else
    {
        if (b[m] < b[n])
        {
            min = b[m];
            x = m;
            y = n;
        }
        else
        {
            min = b[n];
            x = n;
            y = m;
        }
        if (min < b[r])
        {
            a[r] = -1;
        }
        else
        {
            min = b[r];
            a[x] = -1;
            x = r;
        }
    }
    time += min;
    num1++;
    if (num1 == 3)
        time2 = time;
    a[x] = 0;
    a[y] = -1;
    if (num1 == 2)

    {
        min = 0;
        for (int k = 0; k < 4; k++)
            if (a[k] != -1)
                min = max(min, b[k]);

        time += min;
        a[y] = 0;
        return;
    }
    for (int i = 0; i < 3; i++)
        for (int j = i + 1; j < 4; j++)

        {
            if (a[i] != -1 && a[j] != -1)

            {
                cross(i, j, 3, y);
                result = result < time ? result : time; //result=min(result,time1);
                time = time2;
            }
        }
}

int main()
{
    int i, j;
    int alltime = 100;
    for (i = 0; i < 3; i++)

    {
        for (j = i + 1; j < 4; j++)

        {
            for (int k = 0; k < 4; k++)
                a[k] = 0;
            time = 0;
            cross(i, j, 4, 0);
            alltime = min(alltime, result);
        }
    }
    cout << "The least time is:" << alltime << endl;
    return 1;
}
