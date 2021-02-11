// 级数求和：
//  已知： Sn =1+1/2+1/3+…+1/n。显然对于任意一个整数 k，当 n 足够大的时候，Sn>k。
//      现给出一个整数 k，要求计算出一个最小的 n，使得 Sn>k。


#include <stdio.h>

int main()
{
    float s = 0.0, k;
    int n;
    printf("输入数字k(1~15):");
    scanf("%f", &k);
    n = 0;
    do
    {
        n++;
        s += 1.0 / (float)n;
    } while (k >= s);
    printf("n=%d\n", n);
    //getch();
    return 0;
}