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



--  以下是解题程序 , (2) 通过每对顶点之间的最短路径算法实现
cd /D E:\develope\c\c_win10\game\jiangshi_guohe\
g++ man_dog_ji_mi02.c -o man_dog_ji_mi02
man_dog_ji_mi02.exe
*/

// 2. 通过每对顶点之间的最短路径算法实现
#include <stdio.h>
#define N 10 //顶点个数
#define MAX 10000
void Floyd(int dist[N][N], int A[N][N], int path[N][N])
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
            {
                /*if(A[i][j]>(A[i][k]+dist[k][j]))//方法一：计算每一次矩阵
                {
                    A[i][j]=(A[i][k]+dist[k][j]);
                    path[i][j]=path[k][j];
                }*/
                if (A[i][j] > (A[i][k] + A[k][j])) //方法二:计算的幂次矩阵
                {
                    A[i][j] = (A[i][k] + A[k][j]);
                    path[i][j] = path[k][j];
                }
            }
}

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
    int A[N][N];
    int path[N][N] = {0}; //给出两顶点间的路径
    int pre = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            A[i][j] = dist[i][j];
            if (dist[i][j] != MAX)
                path[i][j] = i + 1;
            else
                path[i][j] = 0;
        }

    for (int k = 0; k < 7; k++) //若用方法一，需循环N-3次，若用方法二，需要循环lg(N-1)次
        Floyd(dist, A, path);
    printf("每对顶点间的最短路径矩阵为：\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
    printf("\n每对顶点的具体最短路径为：\n");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d: %d ", A[i][j], j + 1);
            pre = path[i][j];
            while ((pre != 0) && (pre != i + 1))
            {
                printf("<- %d ", pre);
                pre = path[i][pre - 1];
            }
            printf(" <- %d\n", i + 1);
        }
    }
    return 1;
}
