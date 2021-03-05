/**
五子棋游戏：
    参考： https://www.cnblogs.com/labixiaohei/p/6360284.html

cd E:\develope\c\c_win10\game\wu_zi_qi\


*/

#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
using namespace std;

int main()
{
    int player = 1; //定义一个玩家，当1时为白方，2时为黑方

    //................................棋盘1..............................................

    int qiPan[19][19]; //1.声明一个19行19列的数组来存储棋盘 1

    for (int h = 0; h < 19; h++) //对数组进行遍历，所有元素进行初始化(赋值),默认为0值
    {
        for (int l = 0; l < 19; l++)
        {
            qiPan[h][l] = 0; //对当前元素进行初始化(赋值),默认为0值
        }
    }

    //...............................棋盘2................................................

    int qiPanTwo[19][19]; //声明一个19行19列的数组来存储棋盘  2

    for (int h = 0; h < 19; h++) //对数组进行遍历，所有元素进行初始化(赋值),默认为0值
    {
        for (int l = 0; l < 19; l++)
        {
            qiPanTwo[h][l] = 0; //对当前元素进行初始化(赋值),默认为0值
        }
    }

    //...............................光标声明.............................................

    int X = 9; //2.声明并初始化光标的横纵坐标
    int Y = 9;
    qiPan[9][9] = 8;

    //..............................显示...................................................

    for (int h = 0; h < 19; h++)
    {
        for (int l = 0; l < 19; l++)
        {

            if (qiPan[h][l] == 8)
            {
                cout << "╋";
            }
            else if (qiPanTwo[h][l] == 0)
            {
                cout << "·";
            }
            else if (qiPanTwo[h][l] == 1)
            {
                cout << "●";
            }
            else if (qiPanTwo[h][l] == 2)
            {
                cout << "○";
            }
        }
        cout << endl;
    }

    //..............................输入控制...............................................

    while (true)
    {
        char xx = getch(); //控制台从键盘获得一个字符
        switch (xx)        //控制
        {
        case 'w':                //上
            Y = Y - 1;           //使光标纵坐标-1
            qiPan[Y][X] = 8;     //讲光标写入棋盘
            qiPan[Y + 1][X] = 0; //使原本位置的值还原
            break;

        case 's': //下
            Y = Y + 1;
            qiPan[Y][X] = 8;
            qiPan[Y - 1][X] = 0;
            break;

        case 'a': //左
            X = X - 1;
            qiPan[Y][X] = 8;
            qiPan[Y][X + 1] = 0;
            break;

        case 'd': //右
            X = X + 1;
            qiPan[Y][X] = 8;
            qiPan[Y][X - 1] = 0;
            break;

        case 'j':            //落子
            if (player == 1) //如果当前玩家为白色方时
            {
                qiPanTwo[Y][X] = 1; //通过棋盘1中的光标位置更改棋盘2中对应元素的值为1，也就是白棋落子
                player = 2;         //白棋落子后更换玩家
            }
            else if (player == 2)
            {
                qiPanTwo[Y][X] = 2;
                player = 1;
            }
            break;
        }

        //................................清屏操作................................................

        system("cls");

        //...............................打印.....................................................

        for (int h = 0; h < 19; h++)
        {
            for (int l = 0; l < 19; l++)
            {

                if (qiPan[h][l] == 8)
                {
                    cout << "╋";
                }
                else if (qiPanTwo[h][l] == 0)
                {
                    cout << "·";
                }
                else if (qiPanTwo[h][l] == 1)
                {
                    cout << "●";
                }
                else if (qiPanTwo[h][l] == 2)
                {
                    cout << "○";
                }
            }
            cout << endl;
        }

        //.........................游戏规则..............................................

        int shu = 1, heng = 1, pie = 1, na = 1; //横竖撇捺
        for (int i = 1; i <= 4; i++)            //上
        {
            if (qiPanTwo[Y + i][X] == qiPanTwo[Y][X] && qiPanTwo[Y][X] != 0)
                shu++;
            else
                break;
        }
        for (int i = 1; i <= 4; i++) //下
        {
            if (qiPanTwo[Y - i][X] == qiPanTwo[Y][X] && qiPanTwo[Y][X] != 0)
                shu++;
            else
                break;
        }
        for (int i = 1; i <= 4; i++) //左
        {
            if (qiPanTwo[Y][X - i] == qiPanTwo[Y][X] && qiPanTwo[Y][X] != 0)
                heng++;
            else
                break;
        }
        for (int i = 1; i <= 4; i++) //右
        {
            if (qiPanTwo[Y][X + i] == qiPanTwo[Y][X] && qiPanTwo[Y][X] != 0)
                heng++;
            else
                break;
        }
        for (int i = 1; i <= 4; i++) //左下
        {
            if (qiPanTwo[Y + i][X - i] == qiPanTwo[Y][X] && qiPanTwo[Y][X] != 0)
                pie++;
            else
                break;
        }
        for (int i = 1; i <= 4; i++) //右上
        {
            if (qiPanTwo[Y - i][X + i] == qiPanTwo[Y][X] && qiPanTwo[Y][X] != 0)
                pie++;
            else
                break;
        }
        for (int i = 1; i <= 4; i++) //右下
        {
            if (qiPanTwo[Y + i][X + i] == qiPanTwo[Y][X] && qiPanTwo[Y][X] != 0)
                na++;
            else
                break;
        }
        for (int i = 1; i <= 4; i++) //左上
        {
            if (qiPanTwo[Y - i][X - i] == qiPanTwo[Y][X] && qiPanTwo[Y][X] != 0)
                na++;
            else
                break;
        }
        if (shu == 5 || heng == 5 || pie == 5 || na == 5)
        {
            if (qiPanTwo[Y][X] == 1)
            {
                cout << "白子获胜!";
                system("pause");
                break;
            }
            else
            {
                cout << "黑子获胜!";
                system("pause");
                break;
            }
        }
    }

    return 0;
}