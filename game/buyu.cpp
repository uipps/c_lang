/*
题目：　A、B、C、D、E五个人在某天夜里合伙去捕鱼，到第二天凌晨时都疲惫不堪，于是各自找地方睡觉。
日上三杆，
A第一个醒来，他将鱼分为五份，把多余的一条鱼扔掉，拿走自己的一份。
B第二个醒来，也将鱼分为五份，把多余的一条鱼扔掉，保持走自己的一份。 求至少捕了多少条鱼？


*/
#include <iostream>

using namespace std;
int main(void)
{
  int n, flag, x, i, t = 1;
  for (n = 6; t; n++)
    for (i = 0; i < 5; i++)
    {
      if (i == 0)
      {
        x = n;
        flag = 0;
      }
      if ((x - 1) % 5 == 0)
      {
        x = (x - 1) * 4 / 5;
        flag++;
      }
      if (flag == 5)
      {
        cout << "总共捕了" << n << "条鱼！" << endl;
        t = 0;
      }
    }
  return 0;
}
