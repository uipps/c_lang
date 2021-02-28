/*
  3个水杯倒水问题(广度优先搜索) ， 参考： https://www.iteye.com/blog/iwebcode-1660775

广度优先，


依次输入：

2
6 3 1
4 1 1
9 3 2
7 1 1

输出 
3 
-1

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

void check(int queue[], int x, int &tail)
{
    for (int i = 0; i <= tail; ++i)
    {
        if (queue[i] == x)
        {
            return;
        }
    }
    ++tail;
    //printf ("%d -> ", x);
    queue[tail] = x;
    return;
}

int getans(int to[], int i)
{
    if (i == to[1] * 10000 + to[2] * 100 + to[3])
        return 1;
    return 0;
}

int daoshui(int queue[], int &a, int &b, int to, int from[])
{
    if (a)
    {
        int t = from[to] - b;
        if (t > a)
        {
            b += a;
            a = 0;
            return 1;
        }
        else if (t)
        {
            a -= t;
            b += t;
            return 1;
        }
    }
    return 0;
}

int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int from[4];
        int to[4];
        scanf("%d %d %d %d %d %d", &from[1], &from[2], &from[3], &to[1], &to[2], &to[3]);
        int head = 0;
        int tail = 0;
        int step = 0;
        int queue[100000];
        queue[0] = from[1] * 10000;
        int flag = 0;
        if (queue[0] == to[1] * 10000 + to[2] * 100 + to[3])
        {
            printf("0\n");
            continue;
        }
        while (head <= tail)
        {
            ++step;
            //printf("******************************%d************************************\n", step);
            int size = tail - head;
            for (int i = head; i <= head + size; ++i)
            {
                int a, b, c;
                //printf ("|%d|", queue[i]);
                a = queue[i] / 10000;
                b = queue[i] % 10000 / 100;
                c = queue[i] % 100;
                if (daoshui(queue, a, b, 2, from))
                {
                    //printf ("(a -> b)");
                    check(queue, a * 10000 + b * 100 + c, tail);
                }
                a = queue[i] / 10000;
                b = queue[i] % 10000 / 100;
                c = queue[i] % 100;
                if (daoshui(queue, a, c, 3, from))
                {
                    //printf ("(a -> c)");
                    check(queue, a * 10000 + b * 100 + c, tail);
                }
                a = queue[i] / 10000;
                b = queue[i] % 10000 / 100;
                c = queue[i] % 100;
                if (daoshui(queue, b, a, 1, from))
                {
                    //printf ("(b -> a)");
                    check(queue, a * 10000 + b * 100 + c, tail);
                }
                a = queue[i] / 10000;
                b = queue[i] % 10000 / 100;
                c = queue[i] % 100;
                if (daoshui(queue, b, c, 3, from))
                {
                    //printf ("(b -> c)");
                    check(queue, a * 10000 + b * 100 + c, tail);
                }
                a = queue[i] / 10000;
                b = queue[i] % 10000 / 100;
                c = queue[i] % 100;
                if (daoshui(queue, c, a, 1, from))
                {
                    //printf ("(c -> a)");
                    check(queue, a * 10000 + b * 100 + c, tail);
                }
                a = queue[i] / 10000;
                b = queue[i] % 10000 / 100;
                c = queue[i] % 100;
                if (daoshui(queue, c, b, 2, from))
                {
                    //printf ("(c -> b)");
                    check(queue, a * 10000 + b * 100 + c, tail);
                }
            }
            //printf ("\n****************************************************************");
            head += size + 1;
            for (int i = head; i <= tail; ++i)
            {
                if (getans(to, queue[i]))
                {
                    printf("%d\n", step);
                    flag = 1;
                    break;
                }
            }
            if (flag)
                break;
        }
        //printf("\n");
        if (!flag)
            printf("-1\n");
    }
    return 0;
}