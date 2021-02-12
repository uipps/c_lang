/**
 取石子游戏 (必负局)

一、规则1 （参考： https://www.cnblogs.com/heisaijuzhen/articles/4324474.html）
有n堆石子，每堆有若干石子，数量不一定相同，两人(游戏者与计算机)轮流从任一堆中拿走任意数量的石子，拿走最后一个石子者为胜利方。
所谓“必负局”，是指把剩余的每一堆的数目都转化成二进制的数，然后把它们相加，进行不进位的加法（也就是异或运算）,
即0+0=0、1+0=1,0+1=1、1+1=0（不进位），如果所得和是0（多个0）,那么此局势称为“必负局”。
 
*/
#include <stdio.h>
#include <stdlib.h>
unsigned int *heap; //保存各堆石子的数量
int num;
void Output() //显示各堆石子的状态
{
    int i;
    printf("各堆剩下的石子数量:\n");
    for (i = 1; i <= num; i++)
        printf("第%2d堆剩下：%u \n", i, heap[i]);
}
unsigned int remain() //统计剩下的石子总数
{
    unsigned int s;
    int i;
    s = 0;
    for (i = 1; i <= num; i++)
        s += heap[i];
    return s;
}
unsigned int xorall() //按位异或的结果
{
    unsigned int s;
    int i;
    s = 0;
    for (i = 1; i <= num; i++)
        s ^= heap[i];
    return s;
}
int main()
{
    unsigned int t;
    int i, s, h;
    printf(" 游戏规则是： 有n堆石子，每堆有若干石子，数量不一定相同，两人(游戏者与计算机)轮流从任一堆中拿走任意数量的石子，拿走最后一个石子者为胜利方。\n\n");
    printf("输入石子的堆数：");
    scanf("%d", &num);
    if (num < 2)
    {
        printf("至少应该有2堆石子!\n");
        exit(0);
    }
    if (!(heap = (unsigned int *)malloc(sizeof(unsigned int) * num)))
    {
        printf("内存分配失败!\n");
        exit(0);
    }
    for (i = 1; i <= num; i++)
    {
        printf("输入第%d堆石子的数量：", i);
        scanf("%d", &heap[i]);
    }
    while (remain()) //剩余石子大于0
    {
        if (xorall() == 0)
        {
            for (i = 1; i <= num; i++) //从一堆石子中取一粒
            {
                if (heap[i] > 0)
                {
                    printf("\n计算机从第%2d堆中拿1粒。\n", i);
                    heap[i]--;
                    break;
                }
            }
        }
        else
        {
            for (i = 1; i <= num; i++)
            {
                s = heap[i] - (xorall() ^ heap[i]); //计算要取的石子数量
                if (s > 0)
                {
                    printf("\n计算机从第%2d堆中拿%u粒。\n", i, s);
                    heap[i] ^= xorall();
                    break;
                }
            }
        }
        if (remain() == 0)
        {
            printf("\n计算机胜");
            break;
        }
        Output(); //显示剩余的石堆情况
        while (1)
        {
            printf("\n输入你的选择（堆 数量）：");
            scanf("%d %u", &h, &t);
            if ((h >= 1) && (h <= num) && (heap[h] >= t))
            {
                heap[h] -= t;
                break;
            }
            else
                printf("\n输入数据出错，重新输入！\n");
        }
        if (remain() == 0)
        {
            printf("\n恭喜你获胜");
            break;
        }
    }
    //getch();
    return 0;
}