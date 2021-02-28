// https://blog.csdn.net/tyro_java/article/details/107524703

#include <iostream>
#include <iomanip>
using namespace std;

struct position
{
    int x, y;
};
position dxy[] = {{1, 0}, {0, 1}, {1, 1}, {2, 0}, {0, 2}};

struct state
{
    int dir;
    position pos;
};

state start = {-1, {3, 3}}, goal = {1, {0, 0}};
state path[100];
int num;

bool IsEq(state st1, state st2)
{
    return (st1.dir == st2.dir) && (st1.pos.x == st2.pos.x) && (st1.pos.y == st2.pos.y);
}

bool IsDone(state st)
{
    return IsEq(st, goal);
}

bool IsValid(state st, int step)
{
    /// 1. 合法性检查
    if (st.pos.x < 0 || st.pos.x > 3 || st.pos.y < 0 || st.pos.y > 3)
    {
        return false;
    }
    /// 2. 安全性检查【根据游戏规则推导出来】
    if (st.pos.x != 0 && st.pos.x != 3 && st.pos.x != st.pos.y)
    {
        return false;
    }
    /// 3. 重复性检查
    for (int i = step - 2; i >= 0; i -= 2)
    {
        if (IsEq(st, path[i]))
        {
            return false;
        }
    }
    return true;
}

state GetNewState(state st, int k, int step)
{
    state next_st = {-st.dir, {st.pos.x + st.dir * dxy[k].x, st.pos.y + st.dir * dxy[k].y}};
    return next_st;
}

void LogStep(state st, int step)
{
    path[step] = st;
}

void OutStep(state st)
{
    cout << setw(2) << st.dir << " (" << st.pos.x << ", " << st.pos.y << ") ";
}

void OutAll(int step)
{
    for (int i = 0; i <= step; i++)
    {
        OutStep(path[i]);
    }
    cout << endl;
}

void Jump(state st, int step)
{
    // 是否到达目标?
    if (IsDone(st))
    {
        num++;
        cout << num << ": ";
        OutAll(step);
        return;
    }
    // 遍历N种决策
    for (int k = 0; k < sizeof(dxy) / sizeof(dxy[0]); k++)
    {
        state next_st = GetNewState(st, k, step);
        if (!IsValid(next_st, step + 1))
            continue;
        LogStep(next_st, step + 1); // 记录该决策
        Jump(next_st, step + 1);    // 转到下一状态
    }
}

int main()
{
    num = 0;           // 初始方案数置0
    LogStep(start, 0); // 记录起点
    Jump(start, 0);    // 从起点出发
    return 0;
}
