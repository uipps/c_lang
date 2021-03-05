/*
五子棋
    参考： https://www.jb51.net/article/179630.htm

*/

#include <stdio.h>

int main()
{
    int w[11][11], flag = 0;
    int a, b;
    while (1)
    {
        if (flag == 0)
        {
            printf("黑色下棋\n");
            scanf("%d %d", &a, &b);
            while (a < 0 || a > 10 || b < 0 || b > 10)
            {
                printf("此位置超出范围，请重新输入：");
                scanf("%d %d", &a, &b);
            }
            while (w[a][b] == 0 || w[a][b] == 1)
            {
                printf("此位置已有棋子，请重新输入：");
                scanf("%d %d", &a, &b);
            }
            flag = 1;
            w[a][b] = 0;
        }
        else
        {
            printf("白色下棋\n");
            scanf("%d %d", &a, &b);
            while (a < 0 || a > 10 || b < 0 || b > 10)
            {
                printf("此位置超出范围，请重新输入：");
                scanf("%d %d", &a, &b);
            }
            while (w[a][b] == 0 || w[a][b] == 1)
            {
                printf("此位置已有棋子，请重新输入：");
                scanf("%d %d", &a, &b);
            }
            flag = 0;
            w[a][b] = 1;
        }

        int A = 1, B = 1, jieguo = 0, C = 1, D = 1;
        int x = 1, y = 1, m = 1, n = 1;
        if (w[a][b] == 1)
        {
            for (int i = 1; i < 5; i++)
            {
                if (w[a][b + i] == 1)
                    A++;
                else
                    break;
            }
            for (int i = 1; i < 5; i++)
            {
                if (w[a][b - i] == 1)
                    A++;
                else
                    break;
            }
            for (int i = 1; i < 5; i++)
            {
                if (w[a + i][b] == 1)
                    C++;
                else
                    break;
            }
            for (int i = 1; i < 5; i++)
            {
                if (w[a - i][b] == 1)
                    C++;
                else
                    break;
            }
            if (A > 4 || C > 4)
                jieguo = 1; //白棋胜利标志
            else
            {
                for (int i = 1; i < 5; i++)
                {
                    if (w[a + i][b + i] == 1)
                        x++;
                    else
                        break;
                }
                for (int i = 1; i < 5; i++)
                {
                    if (w[a - i][b - i] == 1)
                        x++;
                    else
                        break;
                }
                for (int i = 1; i < 5; i++)
                {
                    if (w[a + i][b - i] == 1)
                        y++;
                    else
                        break;
                }
                for (int i = 1; i < 5; i++)
                {
                    if (w[a - i][b + i] == 1)
                        y++;
                    else
                        break;
                }
                if (x > 4 || y > 4)
                    jieguo = 1;
            }
        }
        if (w[a][b] == 0)
        {
            for (int i = 1; i < 5; i++)
            {
                if (w[a][b + i] == 0)
                    B++;
                else
                    break;
            }
            for (int i = 1; i < 5; i++)
            {
                if (w[a][b - i] == 0)
                    B++;
                else
                    break;
            }
            for (int i = 1; i < 5; i++)
            {
                if (w[a + i][b] == 0)
                    D++;
                else
                    break;
            }
            for (int i = 1; i < 5; i++)
            {
                if (w[a - i][b] == 0)
                    D++;
                else
                    break;
            }
            if (B > 4 || D > 4)
                jieguo = 2; //黑棋胜利标志
            else
            {
                for (int i = 1; i < 5; i++)
                {
                    if (w[a + i][b + i] == 0)
                        m++;
                    else
                        break;
                }
                for (int i = 1; i < 5; i++)
                {
                    if (w[a - i][b - i] == 0)
                        m++;
                    else
                        break;
                }
                for (int i = 1; i < 5; i++)
                {
                    if (w[a + i][b - i] == 0)
                        n++;
                    else
                        break;
                }
                for (int i = 1; i < 5; i++)
                {
                    if (w[a - i][b + i] == 0)
                        n++;
                    else
                        break;
                }
                if (m > 4 || n > 4)
                    jieguo = 2;
            }
        }

        for (int k = 0; k < 11; k++)
            printf("第%d列\t", k);
        printf("\n");
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 11; j++)
            {
                if (w[i][j] == 0)
                    printf("黑\t");
                else if (w[i][j] == 1)
                    printf("白\t");
                else
                    printf("+\t");
            }
            printf("第%d行\n\n", i);
        }
        if (jieguo == 1)
        {
            printf("白棋胜利");
            break;
        }
        if (jieguo == 2)
        {
            printf("黑棋胜利");
            break;
        }
    }
    return 0;
}