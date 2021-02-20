/*
回溯算法之分水问题： 好像不是想要的结果。

参考： https://blog.csdn.net/fuzekun/article/details/86693664

-- 
依次输入：
1
1 12 15 7

输出：
14 7



*/

#include <bits/stdc++.h>
using namespace std;

//回溯之倒水问题
struct Node
{             //保存状态
    int v[3]; //三个杯子中的水
    int dis;  //保存花费
    bool operator<(const Node &rhs) const
    { //使用优先队列,先取出小的
        return dis > rhs.dis;
    }
};
const int maxn = 200 + 5;
int vis[maxn][maxn], cap[3], ans[maxn];

void update_ans(const Node &u)
{ //更新答案
    for (int i = 0; i < 3; i++)
    {
        int d = u.v[i];
        if (ans[d] < 0 || u.dis < ans[d])
            ans[d] = u.dis;
    }
}
/*
1
1 12 15 7
*/
void solve(int a, int b, int c, int d)
{
    cap[0] = a, cap[1] = b, cap[2] = c; //保存水的容量
    memset(vis, 0, sizeof(vis));
    memset(ans, -1, sizeof(ans));
    priority_queue<Node> q;
    Node start;
    start.dis = 0;
    start.v[0] = 0, start.v[1] = 0, start.v[2] = c;
    q.push(start);
    vis[0][0] = 1;
    while (!q.empty())
    {
        Node u = q.top();
        q.pop();
        update_ans(u);
        if (ans[d] >= 0)
            break; //不加可以只是多扩展了很多节点
        for (int i = 0; i < 3; i++)
        { //采用bfs
            for (int j = 0; j < 3; j++)
            {
                if (i != j)
                {
                    if (u.v[i] == 0 || u.v[j] == cap[j])
                        continue; //将i中的水倒入j
                }
                int amount = min(cap[j], u.v[i] + u.v[j]) - u.v[j]; //一种是大的导入小的，小的满，倒入cap[j] - u.v[j];另一种是小的倒入大的，小的空,倒入u.v[i]
                Node u2;
                memcpy(&u2, &u, sizeof(u));
                u2.dis = u.dis + amount;
                u2.v[i] -= amount;
                u2.v[j] += amount;
                if (!vis[u2.v[0]][u2.v[1]])
                {
                    vis[u2.v[0]][u2.v[1]] = 1;
                    q.push(u2);
                }
            }
        }
    }
    while (d >= 0)
    { //输出到某个状态的最小水量
        if (ans[d] >= 0)
        {
            printf("%d %d\n", ans[d], d);
            return;
        }
        d--;
    }
}
int main()
{
    int T, a, c, b, d;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        solve(a, b, c, d);
    }
    return 0;
}