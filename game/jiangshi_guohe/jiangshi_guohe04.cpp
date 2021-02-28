#include <iostream>
using namespace std;
struct position
{
    int x, y;
}; // 不同决策对应的状态坐标变化
position dxy[] = {{1, 0}, {0, 1}, {1, 1}, {2, 0}, {0, 2}};
// 起始状态，结束状态
position start_pos = {3, 3},
         goal_pos = {0, 0};

// 决策序列的记录
position path[100];
int num; // 总的方案数
/// 记录出现次数，防止重复!!!
int pos_cnt[2][4][4] = {{{0}}};

// 坐标是否相等
bool IsEq(position pos1, position pos2)
{
    return (pos1.x == pos2.x) && (pos1.y == pos2.y);
}

// 是否完成
bool IsDone(position pos)
{
    return IsEq(pos, goal_pos);
}

// 是否有效
bool IsValid(position pos, int step)
{
    // 声明合法性，安全性，重复性
    bool v, s, r;
    // 方向：0表示从左(西)到右(东), 1表示从右到左
    int dir = step % 2;
    // 合法性检查
    v = (pos.x >= 0) && (pos.x <= 3) && (pos.y >= 0) && (pos.y <= 3);
    // 安全性检查，根据游戏规则推导出来
    s = (pos.x == pos.y || pos.x == 0 || pos.x == 3);
    // 重复性检查，根据算法特点推导出来的
    r = pos_cnt[dir][pos.x][pos.y] == 0;
    return v && s && r;
}

// 计数
void SetCount(position pos, int step, int cnt)
{
    // 获取方向：0表示从左(西)到右(东), 1表示从右到左
    int dir = step % 2;
    pos_cnt[dir][pos.x][pos.y] = cnt;
}

// 获取新的位置
position GetNewPos(position pos, int k, int step)
{
    // 次序决定方向，方向决定加减
    int dir = (step % 2 == 0) ? -1 : 1;
    //通过引入方向变量，使下面的新坐标计算公式成为通用的，对两个方向均适用
    position next_pos = {pos.x + dir * dxy[k].x, pos.y + dir * dxy[k].y};
    return next_pos;
}

void LogStep(position pos, int step)
{
    path[step] = pos;
}

void OutStep(position pos)
{
    cout << "(" << pos.x << ", " << pos.y << ") ";
}

void OutAll(int step)
{
    for (int i = 0; i <= step; i++)
    {
        OutStep(path[i]);
    }
    cout << endl;
}

void Jump(position pos, int step)
{
    if (IsDone(pos))
    {          // 是否到达目标?
        num++; // 方案数加1
        cout << num << ": ";
        OutAll(step); // 输出方案
        return;
    }

    // 遍历N种方案
    for (int k = 0; k < sizeof(dxy) / sizeof(dxy[0]); k++)
    {
        position next_pos = GetNewPos(pos, k, step);
        if (!IsValid(next_pos, step + 1))
            continue;                    // next_pos是否可行?
        SetCount(next_pos, step + 1, 1); // 设置次数!!!
        LogStep(next_pos, step + 1);     // 记录方案
        Jump(next_pos, step + 1);        // 走下一步
        SetCount(next_pos, step + 1, 0); // 清除次数!!!(回溯)
    }
}

int main()
{
    num = 0;                   // 初始方案数置0
    SetCount(start_pos, 0, 1); // 第0步在起点(第一次)!!!
    LogStep(start_pos, 0);     // 记录起点
    Jump(start_pos, 0);        // 走第一步
    return 0;
}