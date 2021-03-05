#ifndef __GAME_H__
#define __GAME_H__

#define ROW 5
#define COL 5

 void Init_board(char board[ROW][COL],int row,int col);//初始化棋盘
 void display_board(char board[ROW][COL],int row,int col);//打印棋盘
 void play_move(char board[ROW][COL],int row,int col);//玩家走
 void computer_move(char board[ROW][COL],int row,int col);//电脑走
 char is_win(char board[ROW][COL],int row,int col);//判断输赢函数

#endif  //__GAME_H__