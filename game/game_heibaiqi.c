#include <stdio.h>
#include <conio.h>

//显示棋盘上棋子的状态
void Output(char chessboard[][8])
{
    int row, col;
    printf("\n   ");
    //输出列标号
    for (col = 0; col < 8; col++)
    {
        printf("  %c ", 'A' + col);
    }
    printf("\n");
    //输出项部横线
    printf("  ┌");
    //输出一行
    for (col = 0; col < 7; col++)
    {
        printf("─┬");
    }
    printf("─┐\n");
    for (row = 0; row < 8; row++)
    {
        //输出行号
        printf("%2d│", row + 1);
        //输出棋盘各单元格中棋子的状态
        for (col = 0; col < 8; col++)
        {
            if (chessboard[row][col] == 1) //白棋
            {
                printf("○│");
            }
            else if (chessboard[row][col] == -1) //黑棋
            {
                printf("●│");
            }
            else //未下子处
            {
                printf(" │");
            }
        }
        printf("\n");
        if (row < 8 - 1)
        {
            printf("  ├"); //输出交叉线
            //输出一行
            for (col = 0; col < 8 - 1; col++)
            {
                printf("─┼");
            }
            printf("─┤\n");
        }
    }
    printf("  └");
    //最后一行的横线
    for (col = 0; col < 8 - 1; col++)
    {
        printf("─┴");
    }
    printf("─┘\n");
}
//检查某一方是否还有下子的地方
int Check(char chessboard[][8], int isDown[][8], char player)
{
    int rowdelta, coldelta, row, col, x, y = 0;
    int iStep = 0;
    char opponent = (player == 1) ? -1 : 1; //对方棋子
    char myplayer = -1 * opponent;          //我方棋子
    //将isDown数组全部清0
    for (row = 0; row < 8; row++)
    {
        for (col = 0; col < 8; col++)
        {
            isDown[row][col] = 0;
        }
    }
    //循环判断棋盘中哪些单元格可以下子
    for (row = 0; row < 8; row++)
    {
        for (col = 0; col < 8; col++)
        {
            //若棋盘上对应位置不为空(表示已经有子)
            if (chessboard[row][col] != 0)
            {
                continue; //继续处理下一个单元格
            }
            //循环检查上下行
            for (rowdelta = -1; rowdelta <= 1; rowdelta++)
            {
                //循环检查左右列
                for (coldelta = -1; coldelta <= 1; coldelta++)
                {
                    //检查若坐标超过棋盘 或为当前单元格
                    if (row + rowdelta < 0 || row + rowdelta >= 8 || col + coldelta < 0 || col + coldelta >= 8 || (rowdelta == 0 && coldelta == 0))
                    {
                        continue; //继续循环
                    }
                    //若(row,col)四周有对手下的子
                    if (chessboard[row + rowdelta][col + coldelta] == opponent)
                    {
                        //以对手下子位置为坐标
                        x = row + rowdelta;
                        y = col + coldelta;
                        //对对手下子为起始点，向四周查找自己方的棋子，以攻击对方棋子
                        while (1)
                        {
                            //对手下子的四周坐标
                            x += rowdelta;
                            y += coldelta;
                            //超过棋盘
                            if (x < 0 || x >= 8 || y < 0 || y >= 8)
                            {
                                break; //退出循环
                            }
                            //若对应位置为空
                            if (chessboard[x][y] == 0)
                            {
                                break;
                            }
                            //若对应位置下的子是当前棋手的
                            if (chessboard[x][y] == myplayer)
                            {
                                //设置移动数组中对应位置为1 (该位置可下子，形成向对手进攻的棋形)
                                isDown[row][col] = 1;
                                iStep++; //累加可下子的位置数量
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    //返回可下的位置数量（若返回值为0，表示没地方可下）
    return iStep;
}
//在指定位置下子
void PlayStep(char chessboard[][8], int row, int col, char player)
{
    int rowdelta = 0;
    int coldelta = 0;
    int x = 0;
    int y = 0;
    char opponent = (player == 1) ? -1 : 1; //对方棋子
    char myplayer = -1 * opponent;          //我方棋子
    chessboard[row][col] = myplayer;        //保存所下的棋子
    //检查所下子四周的棋子
    for (rowdelta = -1; rowdelta <= 1; rowdelta++)
    {
        for (coldelta = -1; coldelta <= 1; coldelta++)
        {
            //若坐标超过棋盘界限
            if (row + rowdelta < 0 || row + rowdelta >= 8 || col + coldelta < 0 || col + coldelta >= 8 || (rowdelta == 0 && coldelta == 0))
            {
                continue; //继续下一位置
            }
            //若该位置是对手的棋子
            if (chessboard[row + rowdelta][col + coldelta] == opponent)
            {
                //以对手棋为坐标
                x = row + rowdelta;
                y = col + coldelta;
                //在对手棋子四周寻找我方棋子
                while (1)
                {
                    x += rowdelta;
                    y += coldelta;
                    //若坐标超过棋盘
                    if (x < 0 || x >= 8 || y < 0 || y >= 8)
                    {
                        break; //退出循环
                    }
                    //若对应位置为空
                    if (chessboard[x][y] == 0)
                    {
                        break; //退出循环
                    }
                    //若对应位置是我方模子
                    if (chessboard[x][y] == myplayer)
                    {
                        //循环处理
                        while (chessboard[x -= rowdelta][y -= coldelta] == opponent)
                        {
                            //将中间的棋子都变成我方棋子
                            chessboard[x][y] = myplayer;
                        }
                        break; //退出循环
                    }
                }
            }
        }
    }
}
//获取分数
int GetMaxScore(char chessboard[][8], char player)
{
    int Score, row, col;
    char opponent = (player == 1) ? -1 : 1; //对方棋子
    char myplayer = -1 * opponent;
    for (row = 0; row < 8; row++) //循环
    {
        for (col = 0; col < 8; col++)
        {
            //若棋盘对应位置是对手下的棋子，从总分中减1
            Score -= chessboard[row][col] == opponent;
            //若棋盘对应位置是我方的棋子，总分中加1分
            Score += chessboard[row][col] == myplayer;
        }
    }
    return Score; //返回分数
}
//获取最佳下子位置
int BestPlay(char chessboard[][8], int isDown[][8], char player)
{
    int row, col, i, j;
    //定义一个临时数组
    char chessboard1[8][8] = {0};
    int MaxScore = 0; //保存最高分
    int Score = 0;
    char opponent = (player == 1) ? -1 : 1; //对手下的棋子
    //循环检查每个单元格
    for (row = 0; row < 8; row++)
    {
        for (col = 0; col < 8; col++)
        {
            //若该位置不可下子
            if (!isDown[row][col])
            {
                continue; //继续
            }
            //复制棋盘各单元格下子的状态到临时数组
            for (i = 0; i < 8; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    chessboard1[i][j] = chessboard[i][j];
                }
            }
            //在临时数组中的指定行列下子
            PlayStep(chessboard1, row, col, player);
            //获取下子后可得到的分数
            Score = GetMaxScore(chessboard1, player);
            //若原方案得到的分数小于本次下子的分数
            if (MaxScore < Score)
            {
                MaxScore = Score; //保存最高分
            }
        }
    }
    return MaxScore; //返回得到的最高分
}
//AI自动下子
void AutoPlayStep(char chessboard[][8], int isDown[][8], char player)
{
    int row, col, row1, col1, i, j;
    //对方可下子提到的分数和最小分数
    int Score = 0, MinScore = 100;
    //临时数组，保存棋盘下子位置
    char chessboard1[8][8];
    //临时数组，保存可下子位置
    int isDown1[8][8];
    char opponent = (player == 1) ? -1 : 1; //对手下的棋子
    for (row = 0; row < 8; row++)           //循环检查棋盘每个单元格
    {
        for (col = 0; col < 8; col++)
        {
            //若不可下子
            if (isDown[row][col] == 0)
            {
                continue; //继续下一个位置
            }
            //将棋盘原来的棋子复制到临时数组中
            for (i = 0; i < 8; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    chessboard1[i][j] = chessboard[i][j];
                }
            }
            //试着在临时棋盘中的一个位子下子
            PlayStep(chessboard1, row, col, player);
            //检查对手是否有地方可下子
            Check(chessboard1, isDown1, opponent);
            //获得临时棋盘中对方下子的得分情况
            Score = BestPlay(chessboard1, isDown1, opponent);
            //保存对方得分最低的下法
            if (Score < MinScore)
            {
                MinScore = Score;
                row1 = row;
                col1 = col;
            }
        }
    }
    //AI按最优下法下子
    PlayStep(chessboard, row1, col1, player);
}
int main()
{
    //保存棋盘中各单元格下子的状态
    char chessboard[8][8];
    //保存棋盘中各位置是否可以下子，可下子的位置为1，其余位置为0
    int isDown[8][8] = {0};
    int row, col, x, y;
    //已下棋子数量
    int iCount = 0;
    int player = 0; //下棋方
    //跳过下子的次数，若为2，表示双方都不能下子
    int SkipPlay = 0;
    //保存AI和游戏者的得分
    int Score[2];
    char select;
    printf("黑白棋\n\n");
    printf("游戏者执黑先下，AI执白，按回车键开始:\n");
    scanf("%c", &select);
    do
    {
        //计算下棋方(0表示游戏者,1表示AI)
        if (player == 0)
        {
            player = 1;
        }
        else
        {
            player = 0;
        }
        iCount = 4; //累计下子数
        //棋盘各位置清空
        for (row = 0; row < 8; row++)
        {
            for (col = 0; col < 8; col++)
            {
                chessboard[row][col] = 0;
            }
        }
        //在棋盘中间位置放置白棋
        chessboard[3][3] = chessboard[4][4] = 1;
        //在棋盘中间位置放置黑棋
        chessboard[3][4] = chessboard[4][3] = -1;
        printf("\n棋盘初始状态:\n");
        //显示初始棋盘下子的状况
        Output(chessboard);
        do
        {
            //若是游戏者下棋(下白子)
            if (player == 1)
            {
                player = 0;
                //判断是否可下黑子
                if (Check(chessboard, isDown, 2))
                {
                    //死循环，直到用户输入正确的坐标为止
                    while (1)
                    {
                        fflush(stdin);
                        printf("输入下子的位置(行 列):");
                        scanf("%d%c", &x, &y);
                        x--; //计算行坐标位置
                        if (y >= 'a')
                        {
                            y = y - 'a' + 1;
                        }
                        else
                        {
                            y = y - 'A' + 1;
                        }
                        y--; //计算列位置
                        //若行列坐标输入有效
                        if (x >= 0 && y >= 0 && x < 8 && y < 8 && isDown[x][y])
                        {
                            //在指定坐标位置下黑子
                            PlayStep(chessboard, x, y, 2);
                            iCount++; //累加下子数
                            break;
                        }
                        else
                        {
                            printf("坐标输入错误，请重新输入。\n");
                        }
                    }
                    printf("\n你下子后的状态:\n");
                    Output(chessboard); //显示棋子状态
                    printf("按任意键AI下子。\n");
                    getch();
                }
                //若无效下子的次数小于2
                else if (++SkipPlay < 2)
                {
                    fflush(stdin); //清除输入缓冲区
                    printf("你没位置可下，按回车键让对方下子。");
                    scanf("%c", &select);
                }
                else
                {
                    printf("双方都没地方下子，游戏结束!\n");
                }
            }
            //若是AI下棋(下黑子)
            else
            {
                player = 1;
                //检查是否可下白子
                if (Check(chessboard, isDown, 1))
                {
                    SkipPlay = 0; //清除无效下子次数
                    //AI下一个白子
                    AutoPlayStep(chessboard, isDown, 1);
                    iCount++; //累加下子数
                    printf("\nAI下子后的状态:\n");
                    Output(chessboard); //显示棋子状态
                }
                else
                {
                    //若无效下子次数小于2
                    if (++SkipPlay < 2)
                    {
                        printf("我没位置可走，请你走。\n");
                    }
                    else
                    {
                        printf("双方都没地方下子，游戏结束!");
                    }
                }
            }
        }
        //下子数量小于64 且无效下子的次数小于2
        while (iCount < 64 && SkipPlay < 2);
        //显示各双方棋子的状况
        Output(chessboard);
        Score[0] = Score[1] = 0; //清空计分变量
        //循环统计各单元格黑白棋子的数量
        for (row = 0; row < 8; row++)
        {
            for (col = 0; col < 8; col++)
            {
                //统计黑子数
                Score[0] += chessboard[row][col] == -1;
                //统计白子数
                Score[1] += chessboard[row][col] == 1;
            }
        }
        printf("最终成绩:\n");
        printf("AI:%d\n游戏者:%d\n", Score[0], Score[1]);
        fflush(stdin); //清空输入缓冲区
        printf("继续下一局(y/n)？:");
        scanf("%c", &select);
    } while (select == 'y' || select == 'Y');
    printf("Game Over!\n");
    return 0;
}