/* 蛮力法求解背包问题 

please input the total number of goods ：10
please input backpack load ：60
please input weight and value of 10 goods one by one:
23 20
15 14
8 7
20 18
7 5
10 11
9 10
16 15
21 19
13 12




*/

#include <stdio.h>

int n;       //表示物品的总数
int m;       //表示背包承重
int ans = 0; //表示最优可行子集的物品数量
int r[50];   //r[]用来记录该子集的物品编号及价值
int sum_w = 0, sum_v = 0;

//定义一个结构体
struct goods //goods表示一个物品
{
    int w;    //w表示物品重量
    int v;    //v表示物品价值
    int flag; //flag表示是否选择该物品
} a[100];

// 记录当前子集,返回该子集物品数量
int record(int sum_v)
{
    int i;
    int count = 0;
    r[0] = sum_v;
    for (i = 0; i < n; ++i)
    {
        if (a[i].flag)
            r[++count] = i + 1;
    }
    return count;
}

// 计算最优解
void superb(int x)
{
    int i;
    // 超重终止条件
    if (sum_w > m)
        return;

    // 记录较优解,最终留下的为最优解
    if (sum_v > r[0])
        ans = record(sum_v);

    for (i = x; i < n; ++i)
    {
        // 加上第i件物品
        sum_v += a[i].v;
        sum_w += a[i].w;
        a[i].flag = 1;

        // 递归处理下一个物品
        superb(i + 1);

        // 减去第i件物品
        sum_v -= a[i].v;
        sum_w -= a[i].w;
        a[i].flag = 0;
    }
}

int main()
{
    int i;
    // 输入
    printf("please input the total number of goods ：");
    scanf("%d", &n);
    printf("please input backpack load ：");
    scanf("%d", &m);
    printf("please input weight and value of %d goods one by one:\n", n);
    for (i = 0; i < n; ++i)
    {
        scanf("%d%d", &a[i].w, &a[i].v);
        a[i].flag = 0;
    }

    // 计算
    superb(0);

    // 输出
    printf("when you select the ");
    for (i = 1; i <= ans; ++i)
        printf("%dth ", r[i]);
    printf("goods,you can get the maximum value %d\n", r[0]);
}