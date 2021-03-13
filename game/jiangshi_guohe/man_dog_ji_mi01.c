/*
 人、狗、鸡、米过河问题 , 参考： https://blog.csdn.net/tengweitw/article/details/25296257

问题描述：某人带狗 、鸡、米用船来过河，只有人会划船(好像是废话，
后面问题我们还会假设动物也会划船),另外至多还能载一物，
当人不在时，狗要吃鸡(有人可能会质疑：狗吃鸡？，
但是我看到的是狗和猫都吃小鸡)，鸡吃米。问 人、狗、鸡、米怎么过河？


 我们用一个向量来表示 人、狗、鸡、米所处的状态，例如：(1 1 1 1)表示 人、狗、鸡、米都在左岸，则对应的(0 0 0 0)表示 人、狗、鸡、米都在右岸。这些向量我们称为状态向量，但是由于问题的条件限制，有些状态是允许的，而有些状态是不允许的，例如(0 1 1 1)表示人不在左岸，显然是不允许的。我们可以穷举出所有允许的状态：
         (1 1 1 1)          (0 0 0 0)     
         (1 1 1 0)          (0 0 0 1)
         (1 1 0 1)          (0 0 1 0)
         (1 0 1 1)          (0 1 0 0)
         (1 0 1 0)          (0 1 0 1)
从上面的允许状态中，我们可以发现规律如下：
     当人在时（也就是第一位为1时），不能有相邻的0，例如(1 1 0 0)是不允许的
     当人不在时(也就是第一个为0时)，不能有相邻的1 ，例如(0 1 1 0)是不允许的

     我们将船的一次运载也用向量表示，例如(1 1 0 0)表示人和狗在船上。由于只有人会划船，则允许的运算向量为：
         (1 1 0 0)          (1 0 1 0)          (1 0 0 1)          (1 0 0 0)
因此我们可以将一次过河过程看成是一个状态向量与一个运算向量的异或运算（模2加运算：1+1=0 1+0=1 0+0=0）。根据上述的向量法的描述，我们可以将问题简化成：将状态(1 1 1 1)经过奇数次与运算向量运算，变成状态为(0 0 0 0)的状态转移过程。下面是过河的图解过程：
           开始状态                   船上状态                    结果状态
 1          (1 1 1 1)     ------>      (1 0 1 0)       ------>         (0 1 0 1)
 2        (0 1 0 1)      ------>      (1 0 0 0)       ------>       (1 1 0 1)
 3        (1 1 0 1)      ------>      (1 0 0 1)        ------>       (0 1 0 0)
 4        (0 1 0 0)      ------>      (1 0 1 0)      ------>      (1 1 1 0)
 5        (1 1 1 0)      ------>      (1 1 0 0)        ------>        (0 0 1 0)
 6        (0 0 1 0)      ------>      (1 0 0 0)      ------>      (1 0 1 0)
 7        (1 0 1 0)      ------>      (1 0 1 0)        ------>        (0 0 0 0)   
————————————————





--  以下是解题程序 , (1) Dijkstra算法
cd /D E:\develope\c\c_win10\game\jiangshi_guohe\
g++ man_dog_ji_mi01.c -o man_dog_ji_mi01
man_dog_ji_mi01.exe
*/

// 1. Dijkstra算法
#include <stdio.h>
#define M 20 //边数
#define N 10 //顶点数
#define MAX 10000
void Dijkstra(int v, int dist[][N], int D[N], int p[N], int s[N]);
int flag[N] = {0};
int flag1 = 0;
int flag2 = 0;

typedef struct
{
    int startvex;
    int endvex;
    int length;
} edge; //边的结构体

edge T[M];

int main()
{
    int dist[N][N] = {{0, MAX, MAX, MAX, MAX, 1, MAX, MAX, MAX, MAX}, //图的邻接矩阵
                      {MAX, 0, MAX, MAX, MAX, MAX, 1, 1, MAX, MAX},
                      {MAX, MAX, 0, MAX, MAX, 1, 1, MAX, 1, MAX},
                      {MAX, MAX, MAX, 0, MAX, MAX, MAX, 1, 1, MAX},
                      {MAX, MAX, MAX, MAX, 0, MAX, MAX, 1, MAX, 1},
                      {1, MAX, 1, MAX, MAX, 0, MAX, MAX, MAX, MAX},
                      {MAX, 1, 1, MAX, MAX, MAX, 0, MAX, MAX, MAX},
                      {MAX, 1, MAX, 1, 1, MAX, MAX, 0, MAX, MAX},
                      {MAX, MAX, 1, 1, MAX, MAX, MAX, MAX, 0, MAX},
                      {MAX, MAX, MAX, MAX, 1, MAX, MAX, MAX, MAX, 0}};
    int D[N] = {0};
    int p[N] = {0};
    int s[N] = {0};
    int num = 0;
    Dijkstra(0, dist, D, p, s); //0表示从状态(1111)开始
    return 1;
}

void Dijkstra(int v, int dist[][N], int D[N], int p[N], int s[N])
{
    int i, j, k, v1, min, max = 10000, pre; /* Max中的值用以表示dist矩阵中的值*/
    v1 = v;
    for (i = 0; i < N; i++) /* 各数组进行初始化*/
    {
        D[i] = dist[v1][i];
        if (D[i] != MAX)
            p[i] = v1 + 1;
        else
            p[i] = 0;
        s[i] = 0;
    }
    s[v1] = 1;                  /* 将源点送U */
    for (i = 0; i < N - 1; i++) /* 求源点到其余顶点的最短距离*/
    {
        min = 10001; /* min>max, 以保证值为的的的的顶顶顶顶点点点点也也也也能能能能加加加加入入入入U */
        for (j = 0; j < N - 1; j++)
            if ((!s[j]) && (D[j] < min)) /* 找出到源点具有最短距离的边*/
            {
                min = D[j];
                k = j;
            }
        s[k] = 1; /* 将找到的顶点k送入U */
        for (j = 0; j < N; j++)
            if ((!s[j]) && (D[j] > D[k] + dist[k][j])) /* 调整V－U中各顶点的距离值*/
            {
                D[j] = D[k] + dist[k][j];
                p[j] = k + 1; /* k是j的前趋*/
            }
    } /*  所有顶点已扩充到U中*/
    for (i = 0; i < N; i++)
    {
        printf(" %d : %d ", D[i], i);
        pre = p[i];
        while ((pre != 0) && (pre != v + 1))
        {
            printf("<- %d ", pre - 1);
            pre = p[pre - 1];
        }
        printf("<-%d \n", v);
    }
}
