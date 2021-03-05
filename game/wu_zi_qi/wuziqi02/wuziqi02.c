/*
    参考： https://blog.csdn.net/sister_wang0712/article/details/79841159

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"

// begin game.c : 
void Init_board(char board[ROW][COL], int row, int col)
{
    //memset(board,' ',row*col*sizeof(board[0][0]));
    int i = 0;
    int j = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            board[i][j] = ' ';
        }
    }
}
void display_board(char board[ROW][COL], int row, int col)
{
    int i = 0;
    for (i = 0; i < row; i++)
    {
        int j = 0;
        for (j = 0; j < col; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < col - 1)
                printf("|");
        }
        printf("\n");
        if (i < row - 1)
            for (j = 0; j < col; j++)
            {
                printf("---");
                if (j < col - 1)
                    printf("|");
            }

        printf("\n");
    }
}
static int is_full(char board[ROW][COL], int row, int col)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}
char is_win(char board[ROW][COL], int row, int col)
{
    int i = 0;
    int j = 0;
    int tmp = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col - 1; j++)
        {
            if (board[i][j] == board[i][j + 1] && (board[i][j] != ' '))
            {
                tmp = 1;
            }
            else
            {
                tmp = 0;
                break;
            }
        }
        if (tmp == 1)
        {
            return board[i][j];
        }
    }

    for (j = 0; j < col; j++)
    {
        for (i = 0; i < row - 1; i++)
        {
            if (board[i][j] == board[i + 1][j] && (board[i][j] != ' '))
            {
                tmp = 1;
            }
            else
            {
                tmp = 0;
                break;
            }
        }
        if (tmp == 1)
        {
            return board[i][j];
        }
    }

    for (i = 0; i < row - 1; i++)
    {
        if (board[i][i] == board[i + 1][i + 1] && (board[i][i] != ' '))
        {
            tmp = 1;
        }
        else
        {
            tmp = 0;
            break;
        }
    }
    if (tmp == 1)
    {
        return board[i][i];
    }
    for (i = 0; i < row - 1; i++)
    {
        if (board[i][row - i - 1] == board[i + 1][row - i - 2] && (board[i][row - i - 1] != ' '))
        {
            tmp = 1;
        }
        else
        {
            tmp = 0;
            break;
        }
    }
    if (tmp == 1)
    {
        return board[i][row - i - 1];
    }
    if (is_full(board, ROW, COL) == 1)
    {
        return 'q'; //棋盘满了
    }
    return ' ';
}

void play_move(char board[ROW][COL], int row, int col)
{
    int x = 0;
    int y = 0;
    printf("玩家走，请输入坐标:>");
    while (1)
    {

        scanf("%d %d", &x, &y);
        if ((x >= 1) && (x <= row) && (y >= 1) && (y <= col))
        {
            if (board[x - 1][y - 1] == ' ')
            {
                board[x - 1][y - 1] = '#';
                break;
            }
            else
            {
                printf("坐标被占用，请重新输入：\n");
            }
        }
        printf("请重新输入>:\n");
    }
}
void computer_move(char board[ROW][COL], int row, int col)
{
    printf("电脑走\n");
    while (1)
    {
        int x = rand() % row;
        int y = rand() % col;
        if (board[x][y] == ' ')
        {
            board[x][y] = '0';
            break;
        }
    }
}
// end game.c

void menu()
{
    printf("*******************************\n");
    printf("*********  1. piay   **********\n");
    printf("*********  0. exit   **********\n");
    printf("*******************************\n");
}
void game()
{
    int win = 0;
    char board[ROW][COL] = {0};     //定义数组
    Init_board(board, ROW, COL);    //初始化棋盘
    display_board(board, ROW, COL); //打印棋盘
    while (1)
    {
        printf("playmove:\n");
        play_move(board, ROW, COL);     //玩家走
        win = is_win(board, ROW, COL);  //判断输赢
        display_board(board, ROW, COL); //打印棋盘
        if (win != ' ')
        {
            break;
        }
        printf("computer move:\n");
        computer_move(board, ROW, COL);
        win = is_win(board, ROW, COL);
        display_board(board, ROW, COL);
        if (win != ' ')
        {
            break;
        }
    }
    if (win == '#')
    {
        printf("恭喜你！玩家赢:\n");
    }
    else if (win == '0')
    {
        printf("电脑赢:\n");
    }
    else
    {
        printf("平局:\n");
    }
}
int main()
{
    int input = 0;
    srand((unsigned int)time(NULL));
    do
    {
        menu();
        printf("请选择：>");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            printf("玩游戏:\n");
            game();
            break;
        case 0:
            printf("退出游戏：\n");
            break;
        default:
            printf("退出游戏:\n");
            break;
        }

    } while (input);
    system("pause");
    return 0;
}