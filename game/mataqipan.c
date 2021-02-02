// 输入坐标： 1 1 或 4 4 , 二维坐标

#include <stdio.h>
#include <stdlib.h>
typedef struct coord
{
    int x;
    int y;
} Coordinate;                                                                                  //棋盘上的坐标
int chessboard[8][8] = {0};                                                                    //初始化棋盘各单元格状态
int curstep;                                                                                   //马跳的步骤序号
Coordinate move[8] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}}; //马可走的八个方向
void display()                                                                                 //显示走法
{
    int i, j;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
            printf("%4d", chessboard[i][j]);
        printf("\n");
    }
    //getch();
    return;
}
void travel(Coordinate curpos) //向前走一步
{

    Coordinate next;
    int i;
    if (curpos.x < 0 || curpos.x > 7 || curpos.y < 0 || curpos.y > 7) //越界
        return;
    if (chessboard[curpos.x][curpos.y])       //若已经走过
        return;                               //是否遍历过
    chessboard[curpos.x][curpos.y] = curstep; //保存步骤。这一步已经走过，用第几步来标识。。
    curstep++;
    if (curstep > 64) //64个棋盘位置都已经走完额
    {
        display();
        printf("\n");
    }
    else
    {
        //在某一位置（curpos）的时候，遍历八种情况的走法。
        for (i = 0; i < 8; i++) //8个可能的方向
        {
            next.x = curpos.x + move[i].x;
            next.y = curpos.y + move[i].y; //此时next表示马将要走的格子的位置，如果不越界，则要travel（next）。
            if (next.x < 0 || next.x > 7 || next.y < 0 || next.y > 7)
                ;
            else
            {
                travel(next);
            }
        }
    }
    chessboard[curpos.x][curpos.y] = 0; //清除步数序号,为什么不影响？？？如果出掉这两句，则程序只能输出一遍。。 当执行了trace(next)的时候，此时curpos已经改变了。相当于上一局的next。 <这样理解正确吗？？？>
    curstep--;                          //减少步数
}
int main()
{
    int i, j;
    Coordinate start;
    printf("输入马的起始位置：");
    scanf("%d%d", &start.x, &start.y);
    if (start.x < 1 || start.y < 1 || start.x > 8 || start.y > 8) //越界
    {
        printf("坐标输入错误，请重新输入！\n");
        exit(0);
    }
    start.x--;
    start.y--;
    curstep = 1; //第1步
    travel(start);
    //getch();
    return 0;
}