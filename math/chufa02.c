/*
判断分数m/n是有限小数还是循环小数,(0≤m<n≤1000)
题目给定了n>m，若m>n,程序可能有点问题，以后有时间再改进

参考： https://blog.csdn.net/haohao__/article/details/106234017

--
输入
1 7
回车

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f(int n) //判断是否是有限还是循环
{
    if (n == 1)
        return 1;
    else if (n % 2 == 0) {
        f(n / 2);
    }
    else if (n % 5 == 0)
    {
        f(n / 5);
    }
    return 0;
}

int gcd(int x, int y)
{
    int r;
    while (x % y)
    {
        r = x % y;
        x = y;
        y = r;
    }
    return y;
}

int find(int *yu, int y) //判断是否找到循环节
{
    int i;
    for (i = 0; i < y - 1; i++)
    {
        if (yu[y - 1] == yu[i])
        {
            return 0; //找到了，跳出循环
        }
    }
    return 1;
}

int main()
{
    int m, n;
    double d;
    int x = 0, y = 0, flag, i, gcd0;
    int zheng, xiao[10000] = {0}, yu[10000] = {0}, r, s;
    puts("请输入自然数m n（0<=m<n<=1000）");
    scanf("%d %d", &m, &n);
    gcd0 = gcd(m, n);
    m = m / gcd0;
    n = n / gcd0; //化为最简分数
    if (f(n))
    {
        d = m * 1.0 / n;
        printf("有限小数：%lf", d);
    }
    else
    {
        zheng = m / n;

        r = m;
        s = r * 10 / n; //第一组
        xiao[x++] = s;
        yu[y++] = r; //存入第一组数据

        while (find(yu, y))
        {
            r = (r * 10) % n;
            s = r * 10 / n;
            xiao[x++] = s;
            yu[y++] = r;
        }
        for (i = 0; i < y - 1; i++)
        {
            if (yu[y - 1] == yu[i])
            {
                flag = i;
            }
        }
        printf("循环小数：%d.", zheng);

        for (i = 0; i < flag; i++)
        {
            printf("%d", xiao[i]); //打印不循环小数部分
        }
        printf("(");
        for (i = flag; i < y - 1; i++)
        {
            printf("%d", xiao[i]); //打印循环小数部分
        }
        printf(")");
    }
}