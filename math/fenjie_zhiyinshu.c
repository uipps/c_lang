#include <stdio.h>
#include <math.h>

int main()
{
    int n, i; //输入正整数n
    while (scanf("%d", &n) != EOF && n != 0)
    {
        printf("%d=", n);

        // i = 2;
        // while (n > 1)
        // {
        //     if (n % i == 0)
        //     {
        //         printf("%d*", i);
        //         n /= i;
        //     }
        //     else
        //         i++;
        // }
        // printf("%d\n", n);   
        // 最终得到的是：2310=2*3*5*7*11*1   最后多了一个1


        //找出n的最小质因数，利用循环，反复求最小质因数
        for (i = 2; i <= sqrt(n); i++)
        {
            for (; n != i;)
            {
                if (n % i == 0)
                {
                    printf("%d*", i);
                    n = n / i;
                }
                if (n % i)
                    break;
            }
        }
        printf("%d\n", i);
    }
    return 0;
}