// 魔术方阵：该方法适用于奇数方阵，3，5，7等

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

int main()
{
    int n; //矩阵行、列数
    int matrix[MAXSIZE][MAXSIZE] = {0};
    int i = 1, j; //循环变量
    int k = 1;
    int tmpi = 0, tmpj = 0;

    while (1)
    {
        printf("请输入矩阵行数(奇数):");
        scanf("%d", &n);
        if ((n <= 0) || (n % 2 == 0))
        {
            printf("请输入正确的矩阵行数(正奇数):");
            scanf("%d", &n);
        }
        else
            break;
    }
    j = n / 2 + 1;
    matrix[i][j] = k;
    for (k = 2; k <= n * n; k++)
    {
        tmpi = i;
        tmpj = j;
        if (j == n)
        {
            j = 1;
        }
        else
        {
            j++;
        }
        if (i == 1)
        {
            i = n;
        }
        else
        {
            i--;
        }
        if (matrix[i][j] != 0)
        {
            i = tmpi + 1;
            j = tmpj;
        }
        matrix[i][j] = k;
    }
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            printf("%2d   ", matrix[i][j]);
        }
        printf("\n");
    }
}
