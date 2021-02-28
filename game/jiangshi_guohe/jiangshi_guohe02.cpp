/*

https://blog.csdn.net/tyro_java/article/details/107524703
*/

#include <iostream>
#include <iomanip>
using namespace std;

// 定义描述渡河状态东岸人数与鬼数的结构变量。R: 状态中的人数, G: 状态中的鬼数
struct state
{
    int R, G;
};
//结构数组记录渡河时的状态转移过程
state s[20];
//记录状态转移过程的决策号，初始化都为0
int choice[20] = {0};
//状态号
int k;

// 摆渡策略(数组) 0号策略不用, 有用的只有5个, 其中从{2,0}到{0,2} 这有用的5个, 决策编号依次为：1,2,3,4,5
state d[6] = {{0, 0}, {2, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 2}};
void display();        // 输出渡河状态
void transfer_state(); // 渡河状态转移函数

int main()
{
    transfer_state();
    display();
    return 0;
}

void transfer_state()
{
    k = 1;      //初始状态设为1, 也就是第一次从东岸走，是奇数，减法操作
    s[1].R = 3; //初始状态东岸有3人
    s[1].G = 3; //初始状态东岸有3鬼

    do
    {
        int fx = 1; //摆渡方向，东向西或西向东
        if (k % 2 == 1)
        {
            fx = -1; //奇数表明摆渡要从东岸到西岸
        }
        int i; //决策号

        // 针对下一状态(次序为k+1，choice数组元素初值为0)，依次尝试所有决策(决策号从1到5)
        for (i = choice[k + 1] + 1; i <= 5; i++)
        {
            //试探采用哪个决策能安全走1步
            int r = s[k].R + fx * d[i].R; //按第i号策略走1步后，东岸的人数
            int g = s[k].G + fx * d[i].G; //按第i号策略走1步后，东岸的鬼数
            // 判断是否越界
            bool cross = r > 3 || g > 3 || r < 0 || g < 0;
            // (1) 越界，舍弃当前决策
            if (cross)
                continue;
            bool AQ = (r == 3) || (r == 0) || (r == g); //是否安全
            //(2) 不安全，舍弃当前决策
            if (!AQ)
                continue;
            bool CHF = false; //是否重复
            //查历史信息(倒序)，仅考虑摆渡方向一致的状态(增量为-2)
            for (int j = k - 1; j >= 1; j -= 2)
            {
                if (s[j].R == r && s[j].G == g)
                {
                    CHF = true; //若人鬼数一致，则是重复状态
                }
            }
            //(3) 重复，则舍弃当前决策，继续(continue)尝试下一决策
            if (CHF)
            {
                continue;
            }
            // 按策略渡河，状态号加1
            k++;
            s[k].R = r;
            s[k].G = g;
            //记录决策号
            choice[k] = i;
            //已找到一个决策，跳出(break)循环，**暂停** 尝试其他策略
            break;
        }
        // 所有摆渡决策都没成功，则需要回退
        if (i > 5)
        {
            choice[k + 1] = 0;
            k--;
        }
    } while (!(s[k].R == 0 && s[k].G == 0)); // 目标是东岸既无人又无鬼
}

void display()
{
    for (int i = 1; i <= k; i++)
    {
        cout << setw(2) << i << ": choice = " << choice[i]             // 决策号
             << " {" << d[choice[i]].R << "," << d[choice[i]].G << "}" // 决策内容
             << " (" << s[i].R << "," << s[i].G << ") "                // 状态内容
             << endl;
    }
}